#include "ObjectSpaceManifestListStartFND.h"

ObjectSpaceManifestListStartFND::ObjectSpaceManifestListStartFND() {}

ExtendedGUID ObjectSpaceManifestListStartFND::getGosid() const {
  return m_gosid;
}

void ObjectSpaceManifestListStartFND::setGosid(const ExtendedGUID &value) {
  m_gosid = value;
}

void ObjectSpaceManifestListStartFND::deserialize(QDataStream &ds) {
  ds >> m_gosid;
}

void ObjectSpaceManifestListStartFND::serialize(QDataStream &ds) const {
  ds << m_gosid;
}

void ObjectSpaceManifestListStartFND::toDebugString(QDebug dbg) const {
  dbg << " ObjectSpaceManifestListStartFND: gosid: " << m_gosid << '\n';
}

void ObjectSpaceManifestListStartFND::generateXml(
    QXmlStreamWriter &xmlWriter) const {
    xmlWriter.writeStartElement("ObjectSpaceManifestListStartFND");
    m_gosid.generateXml(xmlWriter);
    xmlWriter.writeEndElement();
}
