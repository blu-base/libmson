#include "ObjectSpaceManifestListReferenceFND.h"
#include <QDataStream>
#include <QDebug>

#include "../commonTypes/FileNodeChunkReference.h"

namespace MSONcommon {

ObjectSpaceManifestListReferenceFND::ObjectSpaceManifestListReferenceFND(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : m_ref{FileNodeChunkReference(stpFormat, cbFormat)} {}
ObjectSpaceManifestListReferenceFND::ObjectSpaceManifestListReferenceFND(
    quint8 stpFormat, quint8 cbFormat)
    : m_ref{FileNodeChunkReference(stpFormat, cbFormat)} {}

ObjectSpaceManifestListReferenceFND::~ObjectSpaceManifestListReferenceFND() {}

ExtendedGUID ObjectSpaceManifestListReferenceFND::getGosid() const {
  return m_gosid;
}

void ObjectSpaceManifestListReferenceFND::setGosid(const ExtendedGUID &value) {
  m_gosid = value;
}

void ObjectSpaceManifestListReferenceFND::deserialize(QDataStream &ds) {
  ds >> m_ref;
  ds >> m_gosid;
}

void ObjectSpaceManifestListReferenceFND::serialize(QDataStream &ds) const {
  ds << m_ref;
  ds << m_gosid;
}

void ObjectSpaceManifestListReferenceFND::toDebugString(QDebug dbg) const {
  dbg << " ObjectSpaceManifestListReferenceFND:\n"
      << " ref:   " << m_ref << '\n'
      << " gosid: " << m_gosid << '\n';
}

FileNodeChunkReference ObjectSpaceManifestListReferenceFND::getRef() const {
  return m_ref;
}

void ObjectSpaceManifestListReferenceFND::setRef(
    const FileNodeChunkReference &value) {
  m_ref = value;
}

void ObjectSpaceManifestListReferenceFND::generateXml(
    QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ObjectSpaceManifestListReferenceFND");
  m_ref.generateXml(xmlWriter);

  m_gosid.generateXml(xmlWriter);

  xmlWriter.writeEndElement();
}

} // namespace MSONcommon
