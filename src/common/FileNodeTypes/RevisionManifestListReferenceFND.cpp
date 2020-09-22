#include "RevisionManifestListReferenceFND.h"

namespace MSONcommon {

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

quint64 RevisionManifestListReferenceFND::getSizeInFile() const {
  return m_ref.getSizeInFile();
}

void RevisionManifestListReferenceFND::deserialize(QDataStream &ds) {
  ds >> m_ref;
}

void RevisionManifestListReferenceFND::serialize(QDataStream &ds) const {
  ds << m_ref;
}

void RevisionManifestListReferenceFND::toDebugString(QDebug &dbg) const {
  dbg << " RevisionManifestListReferenceFND:\n"
      << " ref: " << m_ref << '\n';
}

void RevisionManifestListReferenceFND::writeLowLevelXml(
    QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("RevisionManifestListReferenceFND");
  xmlWriter << m_ref;
  xmlWriter.writeEndElement();
}

} // namespace MSONcommon
