#include "FileChunkReference64x32.h"

FileChunkReference64x32::FileChunkReference64x32()
    : IFileChunkReference<quint64, quint32>() {}

FileChunkReference64x32::FileChunkReference64x32(FCR_INITTYPE inittype)
    : IFileChunkReference<quint64, quint32>() {
  switch (inittype) {
  case FCR_INITTYPE::FCRNIL:
    this->set_fcrNil();
    break;
  case FCR_INITTYPE::FCRZERO:
    this->set_fcrZero();
    break;
  }
}

FileChunkReference64x32::~FileChunkReference64x32() {}

bool FileChunkReference64x32::is_fcrNil() const {
  return m_stp == UINT64_MAX && m_cb == 0u;
}

bool FileChunkReference64x32::is_fcrZero() const {
  return m_stp == 0u && m_cb == 0u;
}

void FileChunkReference64x32::set_fcrNil() {
  m_stp = UINT64_MAX;
  m_cb = 0u;
}

void FileChunkReference64x32::set_fcrZero() {
  m_stp = 0u;
  m_cb = 0u;
}

quint64 FileChunkReference64x32::stp() const { return m_stp; }

void FileChunkReference64x32::setStp(const quint64 &stp) { m_stp = stp; }

quint32 FileChunkReference64x32::cb() const { return m_cb; }

void FileChunkReference64x32::setCb(const quint32 &cb) { m_cb = cb; }

void FileChunkReference64x32::deserialize(QDataStream &ds) {
  ds >> m_stp;
  ds >> m_cb;
}

void FileChunkReference64x32::serialize(QDataStream &ds) const {
  ds << m_stp;
  ds << m_cb;
}

void FileChunkReference64x32::toDebugString(QDebug dbg) const {
    dbg.noquote();
  dbg << "FileChunkReference64x32(";
  if (is_fcrNil()) {
    dbg << "fcrNil";
  } else if (is_fcrZero()) {
    dbg << "fcrZero";
  } else {
    dbg << "stp: " << QString("0x%1").arg(m_stp, 16, 16, QLatin1Char('0'))

        << ", cb: " << QString("0x%1").arg(m_cb, 8, 16, QLatin1Char('0'));
  };
  dbg << ")";
}
