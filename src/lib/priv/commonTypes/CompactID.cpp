#include "CompactID.h"

#include <QByteArray>
#include <QString>
#include <cmath>
#include <string>


namespace libmson {
namespace priv {

quint8 CompactID::getN() const { return m_n; }

void CompactID::setN(const quint8& value) { m_n = value; }

quint32 CompactID::getGuidIndex() const { return guidIndex; }

/**
 * @brief CompactID::setGuidIndex
 * @param value
 * @return
 *
 * checks if uint32_t value
 */
bool CompactID::setGuidIndex(const quint32& value)
{
  if (value >= 0xFFFFFF) {
    return false;
  }

  guidIndex = value;
  return true;
}

// bool CompactID::isValid() const {
//  return m_n == eguid->getN() && guidIndex < 0xFFFFFF;
//}

bool CompactID::isNull() const { return (m_n == 0) && (guidIndex == 0); }

QByteArray CompactID::toByteArray() const
{
  QByteArray raw;

  raw.append(QByteArray::number(m_n, 16));

  raw.append(QByteArray::number(guidIndex, 16).right(3));

  return raw;
}

QString CompactID::toString() const
{
  return QString(QString::fromStdString(
      std::to_string(guidIndex) + ", " + std::to_string(m_n)));
}

// void CompactID::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
//  xmlWriter.writeStartElement("CompactID");
//  xmlWriter.writeAttribute("guidIndex", qStringHex(guidIndex, 12));
//  xmlWriter.writeAttribute("n", qStringHex(m_n, 2));
//  xmlWriter.writeEndElement();
//}

void CompactID::deserialize(QDataStream& ds)
{
  quint32 temp{};

  ds >> temp;

  m_n = static_cast<quint8>(temp & 0xFF);

  guidIndex = (temp >> 8);
}

void CompactID::serialize(QDataStream& ds) const
{
  quint32 raw = m_n;
  raw += guidIndex << 8;

  ds << raw;
}

bool operator==(const CompactID& lhs, const CompactID& rhs) noexcept
{
  return lhs.getN() == rhs.getN() && lhs.getGuidIndex() == rhs.getGuidIndex();
}

bool operator!=(const CompactID& lhs, const CompactID& rhs) noexcept
{
  return !(lhs == rhs);
}

CompactID::CompactID() : m_n{0}, guidIndex{0} {}

CompactID::CompactID(const quint8 n, const quint32 compactEGUID)
    : m_n{n}, guidIndex{0}
{
  setGuidIndex(compactEGUID);
}


CompactID::CompactID(const QByteArray& bytes) : m_n{0}, guidIndex{0}
{
  setN(bytes.at(0));
  setGuidIndex(bytes.right(3).toUInt());
}

} // namespace priv
} // namespace libmson
