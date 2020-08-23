#include "ReadOnlyObjectDeclaration2LargeRefCountFND.h"
#include "../commonTypes/FileNodeChunkReference.h"

FNCR_STP_FORMAT
ReadOnlyObjectDeclaration2LargeRefCountFND::getStpFormat() const {
  return m_stpFormat;
}

FNCR_CB_FORMAT ReadOnlyObjectDeclaration2LargeRefCountFND::getCbFormat() const {
  return m_cbFormat;
}

ReadOnlyObjectDeclaration2LargeRefCountFND::
    ReadOnlyObjectDeclaration2LargeRefCountFND(FNCR_STP_FORMAT stpFormat,
                                               FNCR_CB_FORMAT cbFormat)
    : m_stpFormat(stpFormat), m_cbFormat(cbFormat),
      m_base(stpFormat, cbFormat) {}

ReadOnlyObjectDeclaration2LargeRefCountFND::
    ReadOnlyObjectDeclaration2LargeRefCountFND(quint8 stpFormat,
                                               quint8 cbFormat)
    : m_stpFormat(static_cast<FNCR_STP_FORMAT>(stpFormat)),
      m_cbFormat(static_cast<FNCR_CB_FORMAT>(cbFormat)),
      m_base(stpFormat, cbFormat) {}

ReadOnlyObjectDeclaration2LargeRefCountFND::
    ~ReadOnlyObjectDeclaration2LargeRefCountFND() {}

ObjectDeclaration2LargeRefCountFND
ReadOnlyObjectDeclaration2LargeRefCountFND::getBase() const {
  return m_base;
}

void ReadOnlyObjectDeclaration2LargeRefCountFND::setBase(
    const ObjectDeclaration2LargeRefCountFND &value) {
  m_base = value;
}

QByteArray ReadOnlyObjectDeclaration2LargeRefCountFND::getMd5hash() const {
  return m_md5hash;
}

void ReadOnlyObjectDeclaration2LargeRefCountFND::setMd5hash(
    const QByteArray &value) {
  m_md5hash = value;
}

void ReadOnlyObjectDeclaration2LargeRefCountFND::deserialize(QDataStream &ds) {

  m_base = ObjectDeclaration2LargeRefCountFND(m_stpFormat, m_cbFormat);
  ds >> m_base;

  char *md5hashRaw {};
  ds.readRawData(md5hashRaw, 16);

  m_md5hash = QByteArray(md5hashRaw,16);
}

void ReadOnlyObjectDeclaration2LargeRefCountFND::serialize(
    QDataStream &ds) const {

  ds << m_base;
  ds << m_md5hash;
}

void ReadOnlyObjectDeclaration2LargeRefCountFND::toDebugString(
    QDebug dbg) const {

  dbg << " ReadOnlyObjectDeclaration2LargeRefCountFND\n"
      << " Base:\n"
      << m_base << "\nmd5hash: " << m_md5hash.toHex() << '\n';
}

void ReadOnlyObjectDeclaration2LargeRefCountFND::generateXml(
    QXmlStreamWriter &xmlWriter) const {

    xmlWriter.writeStartElement("ReadOnlyObjectDeclaration2LargeRefCountFND");

    m_base.generateXml(xmlWriter);

    xmlWriter.writeStartElement("md5hash");
    xmlWriter.writeCharacters(m_md5hash.toHex());
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
}
