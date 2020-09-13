#include "HashedChunkDescriptor2FND.h"

namespace MSONcommon {
HashedChunkDescriptor2FND::HashedChunkDescriptor2FND(FNCR_STP_FORMAT stpFormat,
                                                     FNCR_CB_FORMAT cbFormat)
    : m_BlobRef(stpFormat, cbFormat) {}

HashedChunkDescriptor2FND::HashedChunkDescriptor2FND(quint8 stpFormat,
                                                     quint8 cbFormat)
    : m_BlobRef(stpFormat, cbFormat) {}

FileNodeChunkReference HashedChunkDescriptor2FND::BlobRef() const {
  return m_BlobRef;
}

void HashedChunkDescriptor2FND::setBlobRef(
    const FileNodeChunkReference &BlobRef) {
  m_BlobRef = BlobRef;
}

QByteArray HashedChunkDescriptor2FND::guidHash() const { return m_guidHash; }

void HashedChunkDescriptor2FND::setGuidHash(const QByteArray &guidHash) {
  m_guidHash = guidHash;
}

ObjectSpaceObjectPropSet HashedChunkDescriptor2FND::getPropSet() const {
  return m_blob;
}

void HashedChunkDescriptor2FND::setPropSet(
    const ObjectSpaceObjectPropSet &value) {
  m_blob = value;
}

void HashedChunkDescriptor2FND::deserialize(QDataStream &ds) {
  ds >> m_BlobRef;

  m_guidHash = ds.device()->read(guidHashWidth);

  // getting remote ObjectPropSet
  quint64 curLocation = ds.device()->pos();
  quint64 destLocation = m_BlobRef.stp();

  ds.device()->seek(destLocation);
  ds >> m_blob;
  ds.device()->seek(curLocation);
}

void HashedChunkDescriptor2FND::serialize(QDataStream &ds) const {
  ds << m_BlobRef;
  ds << m_guidHash;
}

void HashedChunkDescriptor2FND::toDebugString(QDebug dbg) const {
  dbg << " HashedChunkDescriptor2FND\n"
      << " m_BlobRef:" << m_BlobRef << '\n'
      << " m_guidHash: " << m_guidHash.toHex() << '\n';
}

void HashedChunkDescriptor2FND::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("HashedChunkDescriptor2FND");

  xmlWriter << m_BlobRef;

  xmlWriter.writeStartElement("guidHash");
  xmlWriter.writeCharacters(m_guidHash.toHex());
  xmlWriter.writeEndElement();

  xmlWriter << m_blob;

  xmlWriter.writeEndElement();
}
} // namespace MSONcommon
