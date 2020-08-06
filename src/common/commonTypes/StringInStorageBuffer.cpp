#include "StringInStorageBuffer.h"

StringInStorageBuffer::StringInStorageBuffer() : m_cch(0) {}

void StringInStorageBuffer::generateXml(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("StringInStorageBuffer");
    xmlWriter.writeAttribute("cch", QString::number(m_cch));

    xmlWriter.writeCharacters(m_StringData);
    xmlWriter.writeEndElement();
}

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

QString StringInStorageBuffer::getStringData() const { return m_StringData; }

void StringInStorageBuffer::setStringData(const QString &value) {
  m_StringData = value;
}

/**
 * @brief StringInStorageBuffer::deserialize
 * @param ds
 *
 * \todo check which endianess to be used here
 */
void StringInStorageBuffer::deserialize(QDataStream &ds) {
  ds >> m_cch;

  QByteArray rawstring = QByteArray(m_cch * 2, Qt::Uninitialized);

  ds.readRawData(rawstring.data(), m_cch * 2);

  m_StringData = QString(rawstring);
}

void StringInStorageBuffer::serialize(QDataStream &ds) const {}

void StringInStorageBuffer::toDebugString(QDebug dbg) const {
  dbg << " StringInStorageBuffer:\n length: " << m_cch << '\n'
      << "/* " << m_StringData << " */\n";
}

quint32 StringInStorageBuffer::getCch() const { return m_cch; }

void StringInStorageBuffer::setCch(const quint32 &value) { m_cch = value; }
