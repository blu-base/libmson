#include "StringInStorageBuffer.h"


namespace libmson {
namespace priv {

StringInStorageBuffer::StringInStorageBuffer() : m_cch(0) {}

QString StringInStorageBuffer::getStringData() const {
  return QString::fromUtf16(
      reinterpret_cast<const ushort *>(m_rawstring.constData()), m_cch);
}

void StringInStorageBuffer::setStringData(const QString &value) {
  m_rawstring = QByteArray(reinterpret_cast<const char *>(value.utf16()),
                           value.size() * 2);
}

quint64 StringInStorageBuffer::getSizeInFile() const {
  return minSizeInFile + m_cch * 2;
}

/**
 * @brief StringInStorageBuffer::deserialize
 * @param ds
 *
 * \todo check which endianess to be used here
 */
void StringInStorageBuffer::deserialize(QDataStream &ds) {
  ds >> m_cch;

  m_rawstring = ds.device()->read(m_cch * 2);
}

void StringInStorageBuffer::serialize(QDataStream &ds) const {
  ds << m_cch;

  ds.device()->write(m_rawstring, m_cch * 2);

  /// \todo determine which method to use for getStringData()
  qDebug() << "StringInStorageBuffer test:\n"
           << "utf16 m_cch: "
           << QString::fromUtf16(
                  reinterpret_cast<const ushort *>(m_rawstring.constData()),
                  m_cch)
           << '\n'
           << "utf16 m_cch*2: "
           << QString::fromUtf16(
                  reinterpret_cast<const ushort *>(m_rawstring.constData()),
                  m_cch * 2)
           << '\n';
}

quint32 StringInStorageBuffer::getCch() const { return m_cch; }

void StringInStorageBuffer::setCch(const quint32 &value) { m_cch = value; }

} // namespace priv
} // namespace libmson
