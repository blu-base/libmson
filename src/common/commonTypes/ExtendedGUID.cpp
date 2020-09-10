#include "ExtendedGUID.h"

#include <QDataStream>
#include <QDebug>

namespace MSONcommon {

ExtendedGUID::ExtendedGUID() : m_guid(QUuid()), data_n{0} {}

ExtendedGUID::ExtendedGUID(const QUuid &guid, const quint32 &n)
    : m_guid(guid), data_n{n} {}

QUuid &ExtendedGUID::getGuid() { return this->m_guid; }

void ExtendedGUID::setGuid(const QUuid &guid) { m_guid = guid; }

quint32 ExtendedGUID::getN() const { return data_n; }

void ExtendedGUID::setN(const quint32 &n) { data_n = n; }

bool ExtendedGUID::isValid() const {
  if (m_guid.toString() == "{00000000-0000-0000-0000-000000000000}") {
    if (data_n != 0) {
      return false;
    }
  } else {
    if (data_n == 0) {
      return false;
    }
  }

  return true;
}

bool ExtendedGUID::isNull() const {
  return m_guid.toString() == "{00000000-0000-0000-0000-000000000000}";
}

QString ExtendedGUID::toString() const {
  return QString("{" + m_guid.toString() + "," + QString::number(data_n) + "}");
}

void ExtendedGUID::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ExtendedGUID");
  xmlWriter.writeCharacters(toString());
  xmlWriter.writeEndElement();
}

bool operator==(const ExtendedGUID &lhs, const ExtendedGUID &rhs) noexcept {
  return (lhs.m_guid == rhs.m_guid) && (lhs.data_n == rhs.data_n);
}

bool operator!=(const ExtendedGUID &lhs, const ExtendedGUID &rhs) noexcept {
  return !(lhs == rhs);
}

bool operator<=(const ExtendedGUID &lhs, const ExtendedGUID &rhs) noexcept {
  return (lhs.m_guid <= rhs.m_guid) && (lhs.data_n <= rhs.data_n);
}

bool operator>=(const ExtendedGUID &lhs, const ExtendedGUID &rhs) noexcept {
  return (lhs.m_guid >= rhs.m_guid) && (lhs.data_n >= rhs.data_n);
}

QDataStream &operator<<(QDataStream &ds, const ExtendedGUID &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, ExtendedGUID &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const ExtendedGUID &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

void ExtendedGUID::deserialize(QDataStream &ds) {

  // if byte order is big endian, change to little endian
  if (!ds.byteOrder()) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }
  ds >> m_guid;
  ds >> data_n;
}

void ExtendedGUID::serialize(QDataStream &ds) const {
  // if byte order is big endian, change to little endian
  if (!ds.byteOrder()) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }
  ds << m_guid;
  ds << data_n;
}

void ExtendedGUID::toDebugString(QDebug dbg) const {
  dbg.noquote() << "{" << m_guid.toString() << "," << data_n << "}";
}

} // namespace MSONcommon
