#include "BinaryItem.h"


#include "CompactUInt64.h"

#include <QDataStream>

namespace libmson {
namespace fsshttpb {

BinaryItem::BinaryItem() {}

quint64 BinaryItem::getLength() const { return m_content.size(); }

void BinaryItem::setLength(const quint64& length) { m_content.resize(length); }


QByteArray BinaryItem::getContent() const { return m_content; }

void BinaryItem::setContent(const QByteArray& content) { m_content = content; }

quint64 BinaryItem::getSizeInFile() const
{
  return getSizeInFile(m_content.size());
}

quint64 BinaryItem::getSizeInFile(quint64 size)
{
  return CompactUInt64::getSizeInFile(size) + size;
}

void BinaryItem::deserialize(QDataStream& ds)
{
  CompactUInt64 length;
  ds >> length;

  m_content = ds.device()->read(length.getValue());
}

void BinaryItem::serialize(QDataStream& ds) const
{
  CompactUInt64 length(m_content.size());

  ds << length;
  ds.writeRawData(m_content.data(), m_content.size());
}

} // namespace fsshttpb
} // namespace libmson
