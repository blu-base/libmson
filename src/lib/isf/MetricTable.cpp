#include "MetricTable.h"

#include "MetricBlockEntry.h"
#include <QDataStream>

namespace libmson::isf {

MetricTable::MetricTable() {}

MetricTable::MetricTable(std::vector<MetricBlockEntry> entries)
    : m_entries(std::move(entries))
{
}

MetricTable::MetricTable(QDataStream& ds) {
  ds.setByteOrder(QDataStream::LittleEndian);
  ds.setFloatingPointPrecision(QDataStream::SinglePrecision);
  ds >> *this; }

MetricTable::MetricTable(const QByteArray& ba)
{
  QDataStream in(ba);
  in.setByteOrder(QDataStream::LittleEndian);
  in.setFloatingPointPrecision(QDataStream::SinglePrecision);

  in >> *this;
}

size_t MetricTable::size() const { return m_entries.size(); }

std::vector<MetricBlockEntry>& MetricTable::entries() { return m_entries; }

std::vector<MetricBlockEntry> MetricTable::getEntries() const
{
  return m_entries;
}

void MetricTable::setEntries(std::vector<MetricBlockEntry> entries)
{
  m_entries = std::move(entries);
}

QDataStream& operator>>(QDataStream& ds, MetricTable& obj)
{
  obj.deserialize(ds);
  return ds;
}

QDataStream& operator<<(QDataStream& ds, const MetricTable& obj)
{
  obj.serialize(ds);
  return ds;
}

void MetricTable::deserialize(QDataStream& ds)
{
  qint64 pos = ds.device()->pos();
  while (!ds.device()->atEnd()) {

    MetricBlockEntry entry;
    ds >> entry;
    pos = ds.device()->pos();
    if (entry.getType() == MetricBlockEntryType::INVALID) {
      break;
    }

    m_entries.push_back(std::move(entry));
  }
}

void MetricTable::serialize(QDataStream& ds) const
{
  for (const auto& entry : m_entries) {
    ds << entry;
  }
}

} // namespace libmson::isf
