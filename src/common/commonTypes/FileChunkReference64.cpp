#include "FileChunkReference64.h"

#include "../helper/Helper.h"

namespace MSONcommon {

FileChunkReference64::FileChunkReference64(FCR_INITTYPE inittype) {
  switch (inittype) {
  case FCR_INITTYPE::FCRNIL:
    this->set_fcrNil();
    break;
  case FCR_INITTYPE::FCRZERO:
    this->set_fcrZero();
    break;
  }
}

bool FileChunkReference64::is_fcrNil() const {
  return m_stp == UINT64_MAX && m_cb == 0;
}

bool FileChunkReference64::is_fcrZero() const {
  return m_stp == 0 && m_cb == 0;
}

void FileChunkReference64::set_fcrNil() {
  m_stp = UINT64_MAX;
  m_cb = 0;
}

void FileChunkReference64::set_fcrZero() {
  m_stp = 0;
  m_cb = 0;
}

quint64 FileChunkReference64::stp() const { return m_stp; }

void FileChunkReference64::setStp(const quint64 &stp) { m_stp = stp; }

quint64 FileChunkReference64::cb() const { return m_cb; }

void FileChunkReference64::setCb(const quint64 &cb) { m_cb = cb; }

quint64 FileChunkReference64::getSizeInFile() { return sizeInFile; }

void FileChunkReference64::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("FileChunkReference64");

  if (this->is_fcrNil()) {
    xmlWriter.writeAttribute("fcrNil", "true");
  } else if (this->is_fcrZero()) {
    xmlWriter.writeAttribute("fcrZero", "true");
  } else {
    xmlWriter.writeAttribute("stp", qStringHex(m_stp, 16));
    xmlWriter.writeAttribute("cb", qStringHex(m_cb, 16));
  }

  xmlWriter.writeEndElement();
}

void FileChunkReference64::deserialize(QDataStream &ds) {
  ds >> m_stp;
  ds >> m_cb;
}

void FileChunkReference64::serialize(QDataStream &ds) const {
  ds << m_stp;
  ds << m_cb;
}

void FileChunkReference64::toDebugString(QDebug &dbg) const {
  dbg.noquote();
  dbg << "FileChunkReference64(";
  if (is_fcrNil()) {
    dbg << "fcrNil";
  } else if (is_fcrZero()) {
    dbg << "fcrZero";
  } else {
    dbg << "stp: " << QString("0x%1").arg(m_stp, 16, 16, QLatin1Char('0'))

        << ", cb: " << QString("0x%1").arg(m_cb, 16, 16, QLatin1Char('0'));
  };
  dbg << ")";
}

} // namespace MSONcommon
