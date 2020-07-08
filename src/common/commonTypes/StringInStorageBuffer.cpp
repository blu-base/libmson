#include "StringInStorageBuffer.h"

StringInStorageBuffer::StringInStorageBuffer() : cch() {}

QDataStream &operator<<(QDataStream &ds, const StringInStorageBuffer &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, StringInStorageBuffer &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const StringInStorageBuffer &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

QString StringInStorageBuffer::getStringData() const { return StringData; }

void StringInStorageBuffer::setStringData(const QString &value) {
  StringData = value;
}

/**
 * @brief StringInStorageBuffer::deserialize
 * @param ds
 *
 * \todo check which endianess to be used here
 */
void StringInStorageBuffer::deserialize(QDataStream &ds) {
  ds >> cch;

  QByteArray rawstring = QByteArray(cch * 2, Qt::Uninitialized);

  ds.readRawData(rawstring.data(), cch * 2);

  StringData = QString(rawstring);
}

void StringInStorageBuffer::serialize(QDataStream &ds) const {}

void StringInStorageBuffer::toDebugString(QDebug dbg) const {
  dbg << " StringInStorageBuffer:\n length: " << cch << '\n'
      << "/* " << StringData << " */\n";
}

quint32 StringInStorageBuffer::getCch() const { return cch; }

void StringInStorageBuffer::setCch(const quint32 &value) { cch = value; }
