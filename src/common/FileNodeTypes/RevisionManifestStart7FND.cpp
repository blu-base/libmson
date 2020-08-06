#include "RevisionManifestStart7FND.h"

RevisionManifestStart7FND::RevisionManifestStart7FND() {}

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


void RevisionManifestStart7FND::generateXml(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("RevisionManifestStart7FND");

    m_base.generateXml(xmlWriter);

    m_gctxid.generateXml(xmlWriter);

    xmlWriter.writeEndElement();
}
