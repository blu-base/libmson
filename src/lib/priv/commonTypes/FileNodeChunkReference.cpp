#include "FileNodeChunkReference.h"


namespace libmson {
namespace priv {

FileNodeChunkReference::FileNodeChunkReference(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : IFileChunkReference<quint64, quint64>(), m_stpFormat(stpFormat),
      m_cbFormat(cbFormat)
{
}

FileNodeChunkReference::FileNodeChunkReference(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat, FCR_INIT inittype)
    : IFileChunkReference<quint64, quint64>(), m_stpFormat(stpFormat),
      m_cbFormat(cbFormat)
{
  switch (inittype) {
  case FCR_INIT::NIL:
    this->set_fcrNil();
    break;
  case FCR_INIT::ZERO:
    this->set_fcrZero();
    break;
  }
}

FileNodeChunkReference::FileNodeChunkReference(
    quint8 stpFormat, quint8 cbFormat)
    : FileNodeChunkReference(
          static_cast<FNCR_STP_FORMAT>(stpFormat),
          static_cast<FNCR_CB_FORMAT>(cbFormat))
{
}

FileNodeChunkReference::FileNodeChunkReference(
    quint8 stpFormat, quint8 cbFormat, FCR_INIT inittype)
    : FileNodeChunkReference(
          static_cast<FNCR_STP_FORMAT>(stpFormat),
          static_cast<FNCR_CB_FORMAT>(cbFormat), inittype)
{
}

bool FileNodeChunkReference::is_fcrZero() const
{
  return m_stp == 0 && m_cb == 0;
}

bool FileNodeChunkReference::is_fcrNil() const
{

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

void FileNodeChunkReference::set_fcrZero()
{
  m_stp = 0;
  m_cb  = 0;
}

void FileNodeChunkReference::set_fcrNil()
{
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

quint64 FileNodeChunkReference::stp() const
{

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

void FileNodeChunkReference::setStp(const quint64& stp)
{
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

quint64 FileNodeChunkReference::cb() const
{

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

void FileNodeChunkReference::setCb(const quint64& cb)
{
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

// void FileNodeChunkReference::writeLowLevelXml(QXmlStreamWriter& xmlWriter)
// const
//{
//  xmlWriter.writeStartElement("FileNodeChunkReference");

//  switch (m_stpFormat) {
//  case FNCR_STP_FORMAT::UNCOMPRESED_8BYTE:
//    xmlWriter.writeAttribute("stpFormat", "UNCOMPRESED_8BYTE");
//    break;
//  case FNCR_STP_FORMAT::UNCOMPRESED_4BYTE:
//    xmlWriter.writeAttribute("stpFormat", "UNCOMPRESED_4BYTE");
//    break;
//  case FNCR_STP_FORMAT::COMPRESSED_4BYTE:
//    xmlWriter.writeAttribute("stpFormat", "COMPRESSED_4BYTE");
//    break;
//  case FNCR_STP_FORMAT::COMPRESSED_2BYTE:
//    xmlWriter.writeAttribute("stpFormat", "COMPRESSED_2BYTE");
//    break;
//  }

//  switch (m_cbFormat) {
//  case FNCR_CB_FORMAT::UNCOMPRESED_8BYTE:
//    xmlWriter.writeAttribute("cbFormat", "UNCOMPRESED_8BYTE");
//    break;
//  case FNCR_CB_FORMAT::UNCOMPRESED_4BYTE:
//    xmlWriter.writeAttribute("cbFormat", "UNCOMPRESED_4BYTE");
//    break;
//  case FNCR_CB_FORMAT::COMPRESSED_1BYTE:
//    xmlWriter.writeAttribute("cbFormat", "COMPRESSED_1BYTE");
//    break;
//  case FNCR_CB_FORMAT::COMPRESSED_2BYTE:
//    xmlWriter.writeAttribute("cbFormat", "COMPRESSED_2BYTE");
//    break;
//  }

//  if (this->is_fcrNil()) {
//    xmlWriter.writeAttribute("fcrNil", "true");
//  }
//  else if (this->is_fcrZero()) {
//    xmlWriter.writeAttribute("fcrZero", "true");
//  }
//  else {
//    xmlWriter.writeAttribute("stp", qStringHex(stp(), 16));
//    xmlWriter.writeAttribute("cb", qStringHex(cb(), 16));
//  }

//  xmlWriter.writeEndElement();
//}

void FileNodeChunkReference::deserialize(QDataStream& ds)
{

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

bool FileNodeChunkReference::isSTPcompressed()
{
  return m_stpFormat == FNCR_STP_FORMAT::COMPRESSED_4BYTE ||
         m_stpFormat == FNCR_STP_FORMAT::COMPRESSED_2BYTE;
}

bool FileNodeChunkReference::isCBcompressed()
{
  return m_cbFormat == FNCR_CB_FORMAT::COMPRESSED_2BYTE ||
         m_cbFormat == FNCR_CB_FORMAT::COMPRESSED_1BYTE;
}

quint64 FileNodeChunkReference::getSizeInFile() const
{
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

quint64 FileNodeChunkReference::getSizeInFile(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
{
  quint64 sizeInFile = 0;

  switch (stpFormat) {
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

  switch (cbFormat) {
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

void FileNodeChunkReference::serialize(QDataStream& ds) const
{

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

FNCR_STP_FORMAT FileNodeChunkReference::getStpFormat() const
{
  return m_stpFormat;
}

FNCR_CB_FORMAT FileNodeChunkReference::getCbFormat() const
{
  return m_cbFormat;
}

QString FileNodeChunkReference::fncrStpFormatString(const FNCR_STP_FORMAT format)
{
  switch (format) {
  case FNCR_STP_FORMAT::UNCOMPRESED_8BYTE:
    return QStringLiteral("UNCOMPRESED_8BYTE");

  case FNCR_STP_FORMAT::UNCOMPRESED_4BYTE:
    return QStringLiteral("UNCOMPRESED_4BYTE");

  case FNCR_STP_FORMAT::COMPRESSED_2BYTE:
    return QStringLiteral("COMPRESSED_2BYTE");

  case FNCR_STP_FORMAT::COMPRESSED_4BYTE:
    return QStringLiteral("COMPRESSED_4BYTE");

  }

  // should never be reached
  return QString();
}

QString FileNodeChunkReference::fncrCbFormatString(const FNCR_CB_FORMAT format)
{
  switch (format) {
  case FNCR_CB_FORMAT::UNCOMPRESED_8BYTE:
    return QStringLiteral("UNCOMPRESED_8BYTE");

  case FNCR_CB_FORMAT::UNCOMPRESED_4BYTE:
    return QStringLiteral("UNCOMPRESED_4BYTE");

  case FNCR_CB_FORMAT::COMPRESSED_1BYTE:
    return QStringLiteral("COMPRESSED_1BYTE");

  case FNCR_CB_FORMAT::COMPRESSED_2BYTE:
    return QStringLiteral("COMPRESSED_2BYTE");
  }

  // should never be reached
  return QString();
}

} // namespace priv
} // namespace libmson
