#include "FileChunkReference32.h"

#include "../helper/Helper.h"

namespace MSONcommon {

FileChunkReference32::FileChunkReference32(FCR_INITTYPE inittype) {
  switch (inittype) {
  case FCR_INITTYPE::FCRNIL:
    m_stp = UINT32_MAX;
    m_cb = 0;
    break;
  case FCR_INITTYPE::FCRZERO:
    m_stp = 0;
    m_cb = 0;
    break;
  }
}

bool FileChunkReference32::is_fcrNil() const {
  return m_stp == UINT32_MAX && m_cb == 0;
}

bool FileChunkReference32::is_fcrZero() const {
  return m_stp == 0 && m_cb == 0;
}

void FileChunkReference32::set_fcrNil() {
  m_stp = UINT32_MAX;
  m_cb = 0;
}

void FileChunkReference32::set_fcrZero() {
  m_stp = 0;
  m_cb = 0;
}

quint32 FileChunkReference32::stp() const { return m_stp; }

void FileChunkReference32::setStp(const quint32 &stp) { m_stp = stp; }

quint32 FileChunkReference32::cb() const { return m_cb; }

void FileChunkReference32::setCb(const quint32 &cb) { m_cb = cb; }

void FileChunkReference32::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("FileChunkReference32");

  if (this->is_fcrNil()) {
    xmlWriter.writeAttribute("fcrNil", "true");
  } else if (this->is_fcrZero()) {
    xmlWriter.writeAttribute("fcrZero", "true");
  } else {
    xmlWriter.writeAttribute("stp", qStringHex(m_stp, 8));
    xmlWriter.writeAttribute("cb", qStringHex(m_cb, 8));
  }

  xmlWriter.writeEndElement();
}

void FileChunkReference32::deserialize(QDataStream &ds) {
  ds >> m_stp;
  ds >> m_cb;
}

void FileChunkReference32::serialize(QDataStream &ds) const {
  ds << m_stp;
  ds << m_cb;
}

void FileChunkReference32::toDebugString(QDebug &dbg) const {
  dbg.noquote();
  dbg << "FileChunkReference32(";
  if (is_fcrNil()) {
    dbg << "fcrNil";
  } else if (is_fcrZero()) {
    dbg << "fcrZero";
  } else {
    dbg << "stp: " << QString("0x%1").arg(m_stp, 8, 16, QLatin1Char('0'))

        << ", cb: " << QString("0x%1").arg(m_cb, 8, 16, QLatin1Char('0'));
  };
  dbg << ")";
}

} // namespace MSONcommon
