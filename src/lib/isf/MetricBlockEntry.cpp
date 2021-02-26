#include "MetricBlockEntry.h"

#include <QDataStream>


namespace libmson::isf {

MetricBlockEntry::MetricBlockEntry()
    : m_type(MetricBlockEntryType::INVALID), m_min(INT32_MIN), m_max(INT32_MAX),
      m_unit(MetricUnit::DEFAULT), m_resolution(1000.0)
{
}


MetricBlockEntry::MetricBlockEntry(MetricBlockEntryType type)
    : m_type(type), m_min(INT32_MIN), m_max(INT32_MAX), m_unit(MetricUnit::DEFAULT),
      m_resolution(1000.0)
{
}

MetricBlockEntry::MetricBlockEntry(
    MetricBlockEntryType type, const qint32 min, const qint32 max,
    MetricUnit unit, float resolution)
    : m_type(type), m_min(min), m_max(max), m_unit(unit),
      m_resolution(resolution)
{
}

MetricBlockEntry::MetricBlockEntry(const QByteArray& ba)
    : m_type(MetricBlockEntryType::INVALID), m_min(INT32_MIN), m_max(INT32_MAX),
      m_unit(MetricUnit::DEFAULT), m_resolution(1000.0)
{
  QDataStream in(ba);
  in.setByteOrder(QDataStream::LittleEndian);
  in.setFloatingPointPrecision(QDataStream::SinglePrecision);
  in >> *this;
}

MetricBlockEntry::MetricBlockEntry(QDataStream& ds)
    : m_type(MetricBlockEntryType::INVALID), m_min(INT32_MIN), m_max(INT32_MAX),
      m_unit(MetricUnit::DEFAULT), m_resolution(1000.0)
{
  ds.setByteOrder(QDataStream::LittleEndian);
  ds.setFloatingPointPrecision(QDataStream::SinglePrecision);
  ds >> *this;
}

MetricBlockEntryType MetricBlockEntry::getType() const { return m_type; }

void MetricBlockEntry::setType(const MetricBlockEntryType& type)
{
  m_type = type;
}

QString MetricBlockEntry::getTypeString() const
{
  return MetricBlockEntryTypeString.at(m_type);
}

qint32 MetricBlockEntry::getMin() const { return m_min; }

qint32 MetricBlockEntry::getMax() const { return m_max; }

void MetricBlockEntry::setMinMax(qint32 min, qint32 max)
{

  if (min >= max) {
    min = 0;
  }

  if (max == 0) {
    max = UINT32_MAX;
  }

  m_min = std::move(min);
  m_max = std::move(max);
}

MetricUnit MetricBlockEntry::getUnit() const { return m_unit; }

void MetricBlockEntry::setUnit(const MetricUnit& unit) { m_unit = unit; }

QString MetricBlockEntry::getUnitString() const
{
  return MetricUnitString.at(m_unit);
}

float MetricBlockEntry::getResolution() const { return m_resolution; }

void MetricBlockEntry::setResolution(float resolution)
{
  if (resolution <= 0) {
    resolution = 1000;
  }

  m_resolution = resolution;
}

QDataStream& operator>>(QDataStream& ds, MetricBlockEntry& obj)
{
  obj.deserialize(ds);
  return ds;
}

QDataStream& operator<<(QDataStream& ds, const MetricBlockEntry& obj)
{
  obj.serialize(ds);
  return ds;
}

void MetricBlockEntry::deserialize(QDataStream& ds)
{
  if (ds.device()->peek(32).size() < 32) {
    return;
  }

  QUuid tag_guid;
  ds >> tag_guid;

  auto tagresult = std::find_if(
      MetricBlockEntryTypeGuid.cbegin(), MetricBlockEntryTypeGuid.cend(),
      [&](auto kvpair) { return kvpair.second == tag_guid; });

  if (tagresult == std::cend(MetricBlockEntryTypeGuid)) {
    m_type = MetricBlockEntryType::INVALID;
  }
  else {
    m_type = tagresult->first;
  }


  qint32 min;
  qint32 max;

  ds >> min;
  ds >> max;

  if (min >= max) {
    min = 0;
  }

  if (max == 0) {
    max = UINT32_MAX;
  }

  m_min = min;
  m_max = max;

  quint32 unit;
  ds >> unit;

  auto unitresult = std::find_if(
      MetricUnitMap.cbegin(), MetricUnitMap.cend(),
      [&](auto kvpair) { return kvpair.second == unit; });

  if (unitresult == std::cend(MetricUnitMap)) {
    m_unit = MetricUnit::DEFAULT;
  }
  else {
    m_unit = unitresult->first;
  }

  float resol;
  ds >> resol;

  if (resol <= 0) {
    resol = 1000;
  }

  m_resolution = resol;
}

void MetricBlockEntry::serialize(QDataStream& ds) const
{
  ds << MetricBlockEntryTypeGuid.at(m_type);
  ds << m_min;
  ds << m_max;
  ds << MetricUnitMap.at(m_unit);
  ds << m_resolution;
}


} // namespace libmson::isf
