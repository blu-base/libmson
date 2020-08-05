#include "ReadOnlyObjectDeclaration2RefCountFND.h"

#include "../commonTypes/FileNodeChunkReference.h"

FNCR_CB_FORMAT ReadOnlyObjectDeclaration2RefCountFND::getCbFormat() const {
  return m_cbFormat;
}

FNCR_STP_FORMAT ReadOnlyObjectDeclaration2RefCountFND::getStpFormat() const {
  return m_stpFormat;
}

ReadOnlyObjectDeclaration2RefCountFND::ReadOnlyObjectDeclaration2RefCountFND(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : m_stpFormat(stpFormat), m_cbFormat(cbFormat),
      m_base(stpFormat, cbFormat) {}

ReadOnlyObjectDeclaration2RefCountFND::ReadOnlyObjectDeclaration2RefCountFND(
    quint8 stpFormat, quint8 cbFormat)
    : m_stpFormat(static_cast<FNCR_STP_FORMAT>(stpFormat)),
      m_cbFormat(static_cast<FNCR_CB_FORMAT>(cbFormat)),
      m_base(stpFormat, cbFormat) {}

ReadOnlyObjectDeclaration2RefCountFND::
    ~ReadOnlyObjectDeclaration2RefCountFND() {}

ObjectDeclaration2RefCountFND
ReadOnlyObjectDeclaration2RefCountFND::getBase() const {
  return m_base;
}

void ReadOnlyObjectDeclaration2RefCountFND::setBase(
    const ObjectDeclaration2RefCountFND &value) {
  m_base = value;
}

QByteArray ReadOnlyObjectDeclaration2RefCountFND::getMd5hash() const {
  return md5hash;
}

void ReadOnlyObjectDeclaration2RefCountFND::setMd5hash(
    const QByteArray &value) {
  md5hash = value;
}

void ReadOnlyObjectDeclaration2RefCountFND::deserialize(QDataStream &ds) {

  m_base = ObjectDeclaration2RefCountFND(m_stpFormat, m_cbFormat);
  ds >> m_base;

  char *md5hashRaw = nullptr;
  ds.readRawData(md5hashRaw, 16);

  md5hash = QByteArray(md5hashRaw);
}

void ReadOnlyObjectDeclaration2RefCountFND::serialize(QDataStream &ds) const {

  ds << m_base;
  ds << md5hash;
}

void ReadOnlyObjectDeclaration2RefCountFND::toDebugString(QDebug dbg) const {

  dbg << " ReadOnlyObjectDeclaration2RefCountFND\n"
      << " Base:\n"
      << m_base << '\n'
      << " md5hash: " << md5hash.toHex() << '\n';
}