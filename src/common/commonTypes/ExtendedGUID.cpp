

#include "ExtendedGUID.h"

//#include <string>

//#include <QByteArray>
#include <QDataStream>
#include <QDebug>
//#include <QUuid>
//#include <QtEndian>

// enum { MaxStringEUuidLength = 49 };

// QUuid ExtendedGUID::getGuid() const {

//  return QUuid(data1, data2, data3, data4[0], data4[1], data4[2], data4[3],
//               data4[4], data4[5], data4[6], data4[7]);
//}

// void ExtendedGUID::setGuid(const QUuid &guid) {
//  data1 = guid.data1;
//  data2 = guid.data2;
//  data3 = guid.data3;
//  memcpy(data4, guid.data4, 8);
//}

// void ExtendedGUID::setN(const uint32_t &n) { data_n = n; }

// uint32_t ExtendedGUID::getN() const { return data_n; }

// QDataStream &operator<<(QDataStream &s, const ExtendedGUID &obj) {
//  QByteArray bytes = obj.toByteArray();
//  bytes.resize(20);
//  uint8_t *data = reinterpret_cast<uint8_t *>(bytes.data());

//  // jump to end of QUuid
//  data += 16;

//  // then write data_n to output
//  qToLittleEndian(obj.data_n, data);

//  if (s.writeRawData(bytes.data(), 20) != 20) {
//    s.setStatus(QDataStream::WriteFailed);
//  }
//  return s;
//}

// QDataStream &operator>>(QDataStream &s, ExtendedGUID &obj) {
//  QByteArray bytes(20, Qt::Uninitialized);
//  if (s.readRawData(bytes.data(), 20) != 20) {
//    s.setStatus(QDataStream::ReadPastEnd);
//    return s;
//  }

//  if (s.byteOrder() == QDataStream::BigEndian) {
//    obj = ExtendedGUID::fromRfc4122(bytes);
//  } else {
//    const uint8_t *data = reinterpret_cast<const uint8_t
//    *>(bytes.constData());

//    obj.data1 = qFromLittleEndian<uint32_t>(data);
//    data += sizeof(uint32_t);
//    obj.data2 = qFromLittleEndian<uint32_t>(data);
//    data += sizeof(uint32_t);
//    obj.data3 = qFromLittleEndian<uint32_t>(data);
//    data += sizeof(uint32_t);

//    for (int i = 0; i < 8; ++i) {
//      obj.data4[i] = *(data);
//      data++;
//    }
//    obj.data_n = qFromLittleEndian<uint32_t>(data);
//    data += sizeof(uint32_t);
//  }

//  return s;
//}

// QDebug operator<<(QDebug dbg, const ExtendedGUID &obj) {
//  QDebugStateSaver saver(dbg);
//  dbg.nospace() << "ExtendedGUID(" << obj.toString() << ')';
//  return dbg;
//}

// bool operator<=(const ExtendedGUID &lhs, const ExtendedGUID &rhs) noexcept {
//  return !(rhs < lhs);
//}

// bool operator>=(const ExtendedGUID &lhs, const ExtendedGUID &rhs) noexcept {
//  return !(lhs < rhs);
//}

// bool operator==(const ExtendedGUID &lhs, const ExtendedGUID &rhs) noexcept {
//  if (lhs.data1 != rhs.data1 || lhs.data2 != rhs.data2 ||
//      lhs.data3 != rhs.data3 || lhs.data_n != rhs.data_n)
//    return false;

//  for (uint32_t i = 0; i < 8; i++)
//    if (lhs.data4[i] != rhs.data4[i])
//      return false;

//  return true;
//}

// bool operator!=(const ExtendedGUID &lhs, const ExtendedGUID &rhs) noexcept {
//  return !(lhs == rhs);
//}

// ExtendedGUID::ExtendedGUID() {}

// ExtendedGUID::ExtendedGUID(const QUuid &guid, const ulong &n)
//    : QUuid(guid), data_n(n) {}

// ExtendedGUID::ExtendedGUID(const QByteArray &text)
//    : ExtendedGUID(fromString(QLatin1String(text.data(), text.size()))) {}

// ExtendedGUID::ExtendedGUID(const QString &text, const ulong &n)
//    : QUuid(fromString(text)), data_n(n) {}

// ExtendedGUID::ExtendedGUID(const char *&text, ulong n)
//    : QUuid(text), data_n(n) {}

// ExtendedGUID::ExtendedGUID(uint32_t l, uint16_t w1, uint16_t w2, uint8_t b[],
//                           uint32_t n)
//    : QUuid(l, w1, w2, b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]),
//      data_n(n) {}

// ExtendedGUID::ExtendedGUID(uint32_t l, uint16_t w1, uint16_t w2, uint8_t b1,
//                           uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5,
//                           uint8_t b6, uint8_t b7, uint8_t b8, uint32_t n)
//    : QUuid(l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8), data_n(n) {}

// bool ExtendedGUID::isValid() const {
//  if (getGuid().toString() == "{00000000-0000-0000-0000-000000000000}") {
//    if (data_n != 0) {
//      return false;
//    }
//  } else {
//    if (data_n == 0) {
//      return false;
//    }
//  }

//  return true;
//}

// bool ExtendedGUID::isNull() const {
//  return getGuid().toString() == "{00000000-0000-0000-0000-000000000000}";
//}

// QByteArray ExtendedGUID::toByteArray() const {
//  QByteArray result = getGuid().toRfc4122();
//  result.append(QByteArray::number(data_n, 10));

//  return result;
//}

///**
// * @brief ExtendedGUID::toByteArray
// * @param mode
// * @return
// *
// * returns an ExtendedGUID of type
// *
// * {00000000-0000-0000-0000-000000000000}-{00000000}
// *
// * \todo is data_n formated in the right endian?
// */
// QByteArray ExtendedGUID::toByteArray(QUuid::StringFormat mode) const {
//  QByteArray result = getGuid().toByteArray(mode);

//  std::string *str{};
//  if ((mode & QUuid::Id128) != QUuid::Id128)
//    *str += '-';
//  if ((mode & QUuid::WithoutBraces) == 0)
//    *str += '{';
//  *str += QByteArray::number(data_n, 16).toStdString();
//  if ((mode & QUuid::WithoutBraces) == 0)
//    *str += '}';

//  result.append(QByteArray::fromStdString(*str));

//  return result;
//}

// QByteArray ExtendedGUID::toRfc4122() const {
//  QByteArray result = getGuid().toRfc4122();
//  result.append(QByteArray::number(data_n, 16));
//  return result;
//}

// ExtendedGUID ExtendedGUID::fromString(QStringView text) noexcept {
//  if (text.size() > MaxStringEUuidLength) 
//    text =
//        text.left(MaxStringEUuidLength); //
//        text.truncate(MaxStringUuidLength);

//  char latin1[MaxStringEUuidLength + 1];
//  QByteArray data = QByteArray(latin1);

//  uint32_t d1, n;
//  uint16_t d2, d3;
//  uint8_t d4[8];

//  size_t i{0};

//  data.at(i) == '{' ? i++ : 0;
//  d1 = data.mid(i + 8).toUInt();
//  i += 8;
//  data.at(i) == '-' ? i++ : 0;
//  d2 = data.mid(i + 4).toUShort();
//  i += 4;
//  data.at(i) == '-' ? i++ : 0;
//  d3 = data.mid(i + 4).toUShort();
//  i += 4;
//  data.at(i) == '-' ? i++ : 0;
//  d4[0] = data.at(i);
//  i++;
//  d4[1] = data.at(i);
//  i++;
//  data.at(i) == '-' ? i++ : 0;
//  d4[2] = data.at(i);
//  i++;
//  d4[3] = data.at(i);
//  i++;
//  d4[4] = data.at(i);
//  i++;
//  d4[5] = data.at(i);
//  i++;
//  d4[6] = data.at(i);
//  i++;
//  d4[7] = data.at(i);
//  i++;
//  data.at(i) == '}' ? i++ : 0;
//  data.at(i) == '-' ? i++ : 0;
//  data.at(i) == '{' ? i++ : 0;
//  n = data.mid(i + 8).toUInt();
//  i += 8;
//  data.at(i) == '}' ? i++ : 0;

//  return ExtendedGUID(d1, d2, d3, d4, n);
//}

// ExtendedGUID ExtendedGUID::fromString(QLatin1String string) noexcept {
//  return ExtendedGUID(string.data());
//}

// ExtendedGUID ExtendedGUID::fromRfc4122(const QByteArray &bytes) {
//  if (bytes.isEmpty() || bytes.length() != 20)
//    return ExtendedGUID();

//  uint32_t d1, n;
//  uint16_t d2, d3;
//  uint8_t d4[8];

//  const uint8_t *data = reinterpret_cast<const uint8_t *>(bytes.constData());

//  d1 = qFromBigEndian<uint32_t>(data);
//  data += sizeof(uint32_t);
//  d2 = qFromBigEndian<uint32_t>(data);
//  data += sizeof(uint32_t);
//  d3 = qFromBigEndian<uint32_t>(data);
//  data += sizeof(uint32_t);

//  for (int i = 0; i < 8; ++i) {
//    d4[i] = *(data);
//    data++;
//  }
//  n = qFromBigEndian<uint32_t>(data);
//  data += sizeof(uint32_t);

//  return ExtendedGUID(d1, d2, d3, d4, n);
//}

// QString ExtendedGUID::toString() const {
//  QString str;
//  str += QUuid::toString();
//  str += "-{";
//  str += QByteArray(data_n, 16);
//  str += '}';
//  return str;
//}

// QString ExtendedGUID::toString(QUuid::StringFormat mode) const {
//  QString str;
//  str += QUuid::toString();
//  if ((mode & QUuid::Id128) != QUuid::Id128)
//    str = '-';
//  if ((mode & QUuid::WithoutBraces) == 0)
//    str = '{';
//  str += QByteArray(data_n, 16);
//  if ((mode & QUuid::WithoutBraces) == 0)
//    str = '}';
//  return str;
//}

// bool ExtendedGUID::operator>(const ExtendedGUID &other) const noexcept {
//  return QUuid::operator>(other) && data_n >= other.data_n;
//}

// bool ExtendedGUID::operator<(const ExtendedGUID &other) const noexcept {
//  return QUuid::operator<(other) && data_n <= other.data_n;
//}

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

QString ExtendedGUID::toString() const
{
  return QString("{" + m_guid.toString() + "," + QString::number(data_n) + "}");
}

void ExtendedGUID::generateXml(QXmlStreamWriter& xmlWriter) const
{
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
