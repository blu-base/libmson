#include "LongExtGuid.h"

#include <QDebug>

namespace libmson {
namespace fsshttpb {


LongExtGuid::LongExtGuid() : m_guid(), m_serialNumber() {}

LongExtGuid::LongExtGuid(const QUuid& guid, const quint64& serialNumber)
    : m_guid(guid), m_serialNumber(serialNumber)
{
}

QUuid LongExtGuid::getGuid() const { return m_guid; }

void LongExtGuid::setGuid(const QUuid& guid) { m_guid = guid; }

quint64 LongExtGuid::getSerialNumber() const { return m_serialNumber; }

void LongExtGuid::setSerialNumber(const quint64& serialNumber)
{
  m_serialNumber = serialNumber;
}

quint64 LongExtGuid::getSizeInFile() const
{
  if (m_guid == QUuid() && m_serialNumber == 0) {
    return 1;
  }
  else {
    return 25;
  }
}

QString LongExtGuid::toString() const
{
 return QString("{" + m_guid.toString() + "," + QString::number(m_serialNumber) + "}");
}


void LongExtGuid::deserialize(QDataStream& ds)
{
  quint8 typeByte;
  ds >> typeByte;

  if (typeByte == 0) {
    m_serialNumber = 0;
    m_guid         = QUuid();
  }
  else if (typeByte == 128u) {
    ds >> m_guid;
    if (m_guid == QUuid()) {
      qWarning("LongExtGuid (SerialNumber) likely formatted incorrectly. Guid "
               "is zero, while type indicates non-zero. ");
    }
    ds >> m_serialNumber;
  }
  else {
    qWarning() << "Error: LongExtGuid (SerialNumber) is formatted incorrectly";
  }
}

void LongExtGuid::serialize(QDataStream& ds) const
{
  quint8 typeByte = 0;
  if (m_guid == QUuid() && m_serialNumber == 0) {

    ds << typeByte;
  }
  else {
    typeByte = 128;
    ds << typeByte;
    ds << m_guid;
    ds << m_serialNumber;
  }
}

} // namespace fsshttpb
} // namespace libmson
