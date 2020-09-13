#include "RevisionManifestStart7FND.h"

namespace MSONcommon {

ExtendedGUID RevisionManifestStart7FND::getGctxid() const { return m_gctxid; }

void RevisionManifestStart7FND::setGctxid(const ExtendedGUID &value) {
  m_gctxid = value;
}

void RevisionManifestStart7FND::deserialize(QDataStream &ds) {
  ds >> m_base;
  ds >> m_gctxid;
}

void RevisionManifestStart7FND::serialize(QDataStream &ds) const {
  ds << m_base;
  ds << m_gctxid;
}

void RevisionManifestStart7FND::toDebugString(QDebug dbg) const {
  dbg << " RevisionManifestStart7FND:\n"
      << " base: " << m_base << "\n gctxid: " << m_gctxid << '\n';
}

RevisionManifestStart6FND RevisionManifestStart7FND::getBase() const {
  return m_base;
}

void RevisionManifestStart7FND::setBase(
    const RevisionManifestStart6FND &value) {
  m_base = value;
}

void RevisionManifestStart7FND::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("RevisionManifestStart7FND");

  xmlWriter << m_base;

  xmlWriter << m_gctxid;

  xmlWriter.writeEndElement();
}

} // namespace MSONcommon
