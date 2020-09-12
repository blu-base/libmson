#include "ObjectSpaceManifestRootFND.h"

namespace MSONcommon {

ExtendedGUID ObjectSpaceManifestRootFND::getGosidRoot() const {
  return m_gosidRoot;
}

void ObjectSpaceManifestRootFND::setGosidRoot(const ExtendedGUID &value) {
  m_gosidRoot = value;
}

void ObjectSpaceManifestRootFND::deserialize(QDataStream &ds) {
  ds >> m_gosidRoot;
}

void ObjectSpaceManifestRootFND::serialize(QDataStream &ds) const {
  ds << m_gosidRoot;
}

void ObjectSpaceManifestRootFND::toDebugString(QDebug dbg) const {
  dbg << " ObjectSpaceManifestRootFND:\n"
      << " gosidRoot: " << m_gosidRoot << '\n';
}


void ObjectSpaceManifestRootFND::generateXml(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("ObjectSpaceManifestRootFND");

    m_gosidRoot.generateXml(xmlWriter);

    xmlWriter.writeEndElement();
}

} // namespace MSONcommon
