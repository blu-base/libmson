#include "FileNodeChunkReference.h"

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

FileNodeChunkReference::~FileNodeChunkReference() {}

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

quint64 FileNodeChunkReference::stp() const { return m_stp; }

void FileNodeChunkReference::setStp(const quint64 &stp) {
  switch (m_stpFormat) {
  case FNCR_STP_FORMAT::UNCOMPRESED_8BYTE:
    m_stp = stp;
    break;
  case FNCR_STP_FORMAT::UNCOMPRESED_4BYTE:
  case FNCR_STP_FORMAT::COMPRESSED_4BYTE:
    m_stp = static_cast<quint32>(stp);
    break;
  case FNCR_STP_FORMAT::COMPRESSED_2BYTE:
    m_stp = static_cast<quint16>(stp);
    break;
  }
}

quint64 FileNodeChunkReference::cb() const { return m_cb; }

void FileNodeChunkReference::setCb(const quint64 &cb) {
  switch (m_cbFormat) {
  case FNCR_CB_FORMAT::UNCOMPRESED_8BYTE:
    m_cb = cb;
    break;
  case FNCR_CB_FORMAT::UNCOMPRESED_4BYTE:
    m_cb = static_cast<quint32>(cb);
    break;
  case FNCR_CB_FORMAT::COMPRESSED_1BYTE:
    m_cb = static_cast<quint8>(cb);
    break;
  case FNCR_CB_FORMAT::COMPRESSED_2BYTE:
    m_cb = static_cast<quint16>(cb);
    break;
  }
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

void FileNodeChunkReference::toDebugString(QDebug dbg) const {
  dbg << "FileNodeChunkReference(";
  if (is_fcrNil()) {
    dbg << "fcrNil";
  } else if (is_fcrZero()) {
    dbg << "fcrZero";
  } else {
    dbg << "stp: ";

    switch (m_stpFormat) {
    case FNCR_STP_FORMAT::UNCOMPRESED_8BYTE:
      dbg.noquote() << QString("0x%1").arg(m_stp, 16, 16, QLatin1Char('0'));
      break;

    case FNCR_STP_FORMAT::UNCOMPRESED_4BYTE:
    case FNCR_STP_FORMAT::COMPRESSED_4BYTE:
      dbg.noquote() << QString("0x%1").arg(m_stp, 8, 16, QLatin1Char('0'));
      break;

    case FNCR_STP_FORMAT::COMPRESSED_2BYTE:
      dbg.noquote() << QString("0x%1").arg(m_stp, 4, 16, QLatin1Char('0'));
      break;
    }

    dbg << ", cb: ";

    switch (m_cbFormat) {
    case FNCR_CB_FORMAT::UNCOMPRESED_8BYTE:
      dbg.noquote() << QString("0x%1").arg(m_cb, 16, 16, QLatin1Char('0'));
      break;
    case FNCR_CB_FORMAT::UNCOMPRESED_4BYTE:
      dbg.noquote() << QString("0x%1").arg(m_cb, 8, 16, QLatin1Char('0'));
      break;
    case FNCR_CB_FORMAT::COMPRESSED_1BYTE:
      dbg.noquote() << QString("0x%1").arg(m_cb, 2, 16, QLatin1Char('0'));
      break;
    case FNCR_CB_FORMAT::COMPRESSED_2BYTE:
      dbg.noquote() << QString("0x%1").arg(m_cb, 4, 16, QLatin1Char('0'));
      break;
    }
  };
  dbg << ", stp/cb format: " << static_cast<quint8>(m_stpFormat) << "/"
      << static_cast<quint8>(m_cbFormat) << ")";
}
