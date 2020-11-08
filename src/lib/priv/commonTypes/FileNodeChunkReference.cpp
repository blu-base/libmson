#include "FileNodeChunkReference.h"
#include "../helper/Helper.h"


namespace libmson {
namespace priv {

FileNodeChunkReference::FileNodeChunkReference(FNCR_STP_FORMAT stpFormat,
                                               FNCR_CB_FORMAT cbFormat)
    : IFileChunkReference<quint64, quint64>() {

  m_stpFormat = stpFormat;
  m_cbFormat = cbFormat;
}

FileNodeChunkReference::FileNodeChunkReference(quint8 stpFormat,
                                               quint8 cbFormat)
    : FileNodeChunkReference(static_cast<FNCR_STP_FORMAT>(stpFormat),
                             static_cast<FNCR_CB_FORMAT>(cbFormat)) {}

bool FileNodeChunkReference::is_fcrZero() const {
  return m_stp == 0 && m_cb == 0;
}

bool FileNodeChunkReference::is_fcrNil() const {

  bool m_stp_nil = false;

  switch (m_stpFormat) {
  case FNCR_STP_FORMAT::UNCOMPRESED_8BYTE:
    m_stp_nil = (m_stp == UINT64_MAX);
    break;
  case FNCR_STP_FORMAT::UNCOMPRESED_4BYTE:
  case FNCR_STP_FORMAT::COMPRESSED_4BYTE:
    m_stp_nil = (m_stp == UINT32_MAX);
    break;
  case FNCR_STP_FORMAT::COMPRESSED_2BYTE:
    m_stp_nil = (m_stp == UINT16_MAX);
    break;
  }

  return m_stp_nil && m_cb == 0;
}

void FileNodeChunkReference::set_fcrZero() {
  m_stp = 0;
  m_cb = 0;
}

void FileNodeChunkReference::set_fcrNil() {
  switch (m_stpFormat) {
  case FNCR_STP_FORMAT::UNCOMPRESED_8BYTE:
    m_stp = UINT64_MAX;
    break;
  case FNCR_STP_FORMAT::UNCOMPRESED_4BYTE:
  case FNCR_STP_FORMAT::COMPRESSED_4BYTE:
    m_stp = UINT32_MAX;
    break;
  case FNCR_STP_FORMAT::COMPRESSED_2BYTE:
    m_stp = UINT16_MAX;
    break;
  }

  m_cb = 0;
}

quint64 FileNodeChunkReference::stp() const {

  switch (m_stpFormat) {
  case FNCR_STP_FORMAT::UNCOMPRESED_8BYTE:
  case FNCR_STP_FORMAT::UNCOMPRESED_4BYTE:
    return m_stp;
    break;
  case FNCR_STP_FORMAT::COMPRESSED_4BYTE:
  case FNCR_STP_FORMAT::COMPRESSED_2BYTE:
    return (quint64)m_stp * 8u;
    break;
  default:
    return m_stp;
  }
}

void FileNodeChunkReference::setStp(const quint64 &stp) {
  switch (m_stpFormat) {
  case FNCR_STP_FORMAT::UNCOMPRESED_8BYTE:
    m_stp = stp;
    break;
  case FNCR_STP_FORMAT::UNCOMPRESED_4BYTE:
    m_stp = static_cast<quint32>(stp);
    break;
  case FNCR_STP_FORMAT::COMPRESSED_4BYTE:
    m_stp = static_cast<quint32>(stp / 8u);
    break;
  case FNCR_STP_FORMAT::COMPRESSED_2BYTE:
    m_stp = static_cast<quint16>(stp / 8u);
    break;
  }
}

quint64 FileNodeChunkReference::cb() const {

  switch (m_cbFormat) {
  case FNCR_CB_FORMAT::UNCOMPRESED_8BYTE:
  case FNCR_CB_FORMAT::UNCOMPRESED_4BYTE:
    return m_cb;
    break;
  case FNCR_CB_FORMAT::COMPRESSED_1BYTE:
  case FNCR_CB_FORMAT::COMPRESSED_2BYTE:
    return m_cb * 8u;
    break;
  default:
    return m_cb;
  }
}

void FileNodeChunkReference::setCb(const quint64 &cb) {
  switch (m_cbFormat) {
  case FNCR_CB_FORMAT::UNCOMPRESED_8BYTE:
    m_cb = cb;
    break;
  case FNCR_CB_FORMAT::UNCOMPRESED_4BYTE:
    m_cb = static_cast<quint32>(cb);
    break;
  case FNCR_CB_FORMAT::COMPRESSED_1BYTE:
    m_cb = static_cast<quint8>(cb / 8u);
    break;
  case FNCR_CB_FORMAT::COMPRESSED_2BYTE:
    m_cb = static_cast<quint16>(cb / 8u);
    break;
  }
}

void FileNodeChunkReference::writeLowLevelXml(
    QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("FileNodeChunkReference");

  switch (m_stpFormat) {
  case FNCR_STP_FORMAT::UNCOMPRESED_8BYTE:
    xmlWriter.writeAttribute("stpFormat", "UNCOMPRESED_8BYTE");
    break;
  case FNCR_STP_FORMAT::UNCOMPRESED_4BYTE:
    xmlWriter.writeAttribute("stpFormat", "UNCOMPRESED_4BYTE");
    break;
  case FNCR_STP_FORMAT::COMPRESSED_4BYTE:
    xmlWriter.writeAttribute("stpFormat", "COMPRESSED_4BYTE");
    break;
  case FNCR_STP_FORMAT::COMPRESSED_2BYTE:
    xmlWriter.writeAttribute("stpFormat", "COMPRESSED_2BYTE");
    break;
  }

  switch (m_cbFormat) {
  case FNCR_CB_FORMAT::UNCOMPRESED_8BYTE:
    xmlWriter.writeAttribute("cbFormat", "UNCOMPRESED_8BYTE");
    break;
  case FNCR_CB_FORMAT::UNCOMPRESED_4BYTE:
    xmlWriter.writeAttribute("cbFormat", "UNCOMPRESED_4BYTE");
    break;
  case FNCR_CB_FORMAT::COMPRESSED_1BYTE:
    xmlWriter.writeAttribute("cbFormat", "COMPRESSED_1BYTE");
    break;
  case FNCR_CB_FORMAT::COMPRESSED_2BYTE:
    xmlWriter.writeAttribute("cbFormat", "COMPRESSED_2BYTE");
    break;
  }

  if (this->is_fcrNil()) {
    xmlWriter.writeAttribute("fcrNil", "true");
  } else if (this->is_fcrZero()) {
    xmlWriter.writeAttribute("fcrZero", "true");
  } else {
    xmlWriter.writeAttribute("stp", qStringHex(stp(), 16));
    xmlWriter.writeAttribute("cb", qStringHex(cb(), 16));
  }

  xmlWriter.writeEndElement();
}

void FileNodeChunkReference::deserialize(QDataStream &ds) {

  switch (m_stpFormat) {
  case FNCR_STP_FORMAT::UNCOMPRESED_8BYTE: {
    ds >> m_stp;
    break;
  }
  case FNCR_STP_FORMAT::UNCOMPRESED_4BYTE:
  case FNCR_STP_FORMAT::COMPRESSED_4BYTE: {
    quint32 temp;
    ds >> temp;
    m_stp = temp;
    break;
  }
  case FNCR_STP_FORMAT::COMPRESSED_2BYTE: {
    quint16 temp;
    ds >> temp;
    m_stp = temp;
    break;
  }
  }

  switch (m_cbFormat) {
  case FNCR_CB_FORMAT::UNCOMPRESED_8BYTE:
    ds >> m_cb;
    break;
  case FNCR_CB_FORMAT::UNCOMPRESED_4BYTE: {
    quint32 temp;
    ds >> temp;
    m_cb = temp;
    break;
  }
  case FNCR_CB_FORMAT::COMPRESSED_1BYTE: {
    quint8 temp;
    ds >> temp;
    m_cb = temp;
    break;
  }
  case FNCR_CB_FORMAT::COMPRESSED_2BYTE: {
    quint16 temp;
    ds >> temp;
    m_cb = temp;
    break;
  }
  }
}

bool FileNodeChunkReference::isSTPcompressed() {
  return m_stpFormat == FNCR_STP_FORMAT::COMPRESSED_4BYTE ||
         m_stpFormat == FNCR_STP_FORMAT::COMPRESSED_2BYTE;
}

bool FileNodeChunkReference::isCBcompressed() {
  return m_cbFormat == FNCR_CB_FORMAT::COMPRESSED_2BYTE ||
         m_cbFormat == FNCR_CB_FORMAT::COMPRESSED_1BYTE;
}

quint64 FileNodeChunkReference::getSizeInFile() const {
  quint64 sizeInFile = 0;

  switch (m_stpFormat) {
  case FNCR_STP_FORMAT::UNCOMPRESED_8BYTE:
    sizeInFile += 8;
    break;

  case FNCR_STP_FORMAT::UNCOMPRESED_4BYTE:
  case FNCR_STP_FORMAT::COMPRESSED_4BYTE:
    sizeInFile += 4;
    break;

  case FNCR_STP_FORMAT::COMPRESSED_2BYTE:
    sizeInFile += 2;
    break;
  }

  switch (m_cbFormat) {
  case FNCR_CB_FORMAT::UNCOMPRESED_8BYTE:
    sizeInFile += 8;
    break;
  case FNCR_CB_FORMAT::UNCOMPRESED_4BYTE:
    sizeInFile += 4;
    break;
  case FNCR_CB_FORMAT::COMPRESSED_1BYTE:
    sizeInFile += 1;
    break;
  case FNCR_CB_FORMAT::COMPRESSED_2BYTE:
    sizeInFile += 2;
    break;
  }

  return sizeInFile;
}

void FileNodeChunkReference::serialize(QDataStream &ds) const {

  switch (m_stpFormat) {
  case FNCR_STP_FORMAT::UNCOMPRESED_8BYTE:
    ds << m_stp;
    break;

  case FNCR_STP_FORMAT::UNCOMPRESED_4BYTE:
  case FNCR_STP_FORMAT::COMPRESSED_4BYTE:
    ds << static_cast<quint32>(m_stp);
    break;

  case FNCR_STP_FORMAT::COMPRESSED_2BYTE:
    ds << static_cast<quint16>(m_stp);
    break;
  }

  switch (m_cbFormat) {
  case FNCR_CB_FORMAT::UNCOMPRESED_8BYTE:
    ds << m_cb;
    break;
  case FNCR_CB_FORMAT::UNCOMPRESED_4BYTE:
    ds << static_cast<quint32>(m_cb);
    break;
  case FNCR_CB_FORMAT::COMPRESSED_1BYTE:
    ds << static_cast<quint8>(m_cb);
    break;
  case FNCR_CB_FORMAT::COMPRESSED_2BYTE:
    ds << static_cast<quint16>(m_cb);
    break;
  }
}

void FileNodeChunkReference::toDebugString(QDebug &dbg) const {
  dbg.noquote();
  dbg << "FileNodeChunkReference(";
  if (is_fcrNil()) {
    dbg << "fcrNil";
  } else if (is_fcrZero()) {
    dbg << "fcrZero";
  } else {
    dbg << "stp: " << qStringHex(stp(), 16) << ", cb: " << qStringHex(cb(), 16);
  };

  dbg << ", stp/cb format: " << static_cast<quint8>(m_stpFormat) << "/"
      << static_cast<quint8>(m_cbFormat) << ")";
}

} // namespace priv
} // namespace libmson
