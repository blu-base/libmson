#include "BinaryItem.h"

#include <QDataStream>

namespace libmson {
namespace packStore {

BinaryItem::BinaryItem() {}

quint64 BinaryItem::getLength() const { return m_content.size(); }

void BinaryItem::setLength(const quint64& length) { m_content.resize(length); }


QByteArray BinaryItem::getContent() const { return m_content; }

void BinaryItem::setContent(const QByteArray& content) { m_content = content; }

quint64 BinaryItem::getSizeInFile() const
{
  return CompactUInt64::getSizeInFile(m_content.size()) + m_content.size();
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

} // namespace packStore
} // namespace libmson
