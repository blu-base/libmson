#include "RevisionManifestListReferenceFND.h"

RevisionManifestListReferenceFND::RevisionManifestListReferenceFND(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : m_ref{FileNodeChunkReference(stpFormat, cbFormat)} {}
RevisionManifestListReferenceFND::RevisionManifestListReferenceFND(
    quint8 stpFormat, quint8 cbFormat)
    : m_ref{FileNodeChunkReference(stpFormat, cbFormat)} {}

FileNodeChunkReference RevisionManifestListReferenceFND::getRef() const {
  return m_ref;
}

void RevisionManifestListReferenceFND::setRef(
    const FileNodeChunkReference &value) {
  m_ref = value;
}

void RevisionManifestListReferenceFND::deserialize(QDataStream &ds) {
  ds >> m_ref;
}

void RevisionManifestListReferenceFND::serialize(QDataStream &ds) const {
  ds << m_ref;
}

void RevisionManifestListReferenceFND::toDebugString(QDebug dbg) const {
  dbg << " RevisionManifestListReferenceFND:\n"
      << " ref: " << m_ref << '\n';
}


void RevisionManifestListReferenceFND::generateXml(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("RevisionManifestListReferenceFND");
    m_ref.generateXml(xmlWriter);
    xmlWriter.writeEndElement();
}
