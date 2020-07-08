#include "ObjectSpaceManifestListReferenceFND.h"
#include <QDataStream>
#include <QDebug>

#include "../commonTypes/FileNodeChunkReference.h"

ObjectSpaceManifestListReferenceFND::ObjectSpaceManifestListReferenceFND(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : ref{FileNodeChunkReference(stpFormat, cbFormat)} {}
ObjectSpaceManifestListReferenceFND::ObjectSpaceManifestListReferenceFND(
    quint8 stpFormat, quint8 cbFormat)
    : ref{FileNodeChunkReference(stpFormat, cbFormat)} {}

ObjectSpaceManifestListReferenceFND::~ObjectSpaceManifestListReferenceFND() {}

ExtendedGUID ObjectSpaceManifestListReferenceFND::getGosid() const {
  return gosid;
}

void ObjectSpaceManifestListReferenceFND::setGosid(const ExtendedGUID &value) {
  gosid = value;
}

void ObjectSpaceManifestListReferenceFND::deserialize(QDataStream &ds) {
  ds >> ref;
  ds >> gosid;
}

void ObjectSpaceManifestListReferenceFND::serialize(QDataStream &ds) const {
  ds << ref;
  ds << gosid;
}

void ObjectSpaceManifestListReferenceFND::toDebugString(QDebug dbg) const {
  dbg << " ObjectSpaceManifestListReferenceFND:\n"
      << " ref:   " << ref << '\n'
      << " gosid: " << gosid << '\n';
}

FileNodeChunkReference ObjectSpaceManifestListReferenceFND::getRef() const {
  return ref;
}

void ObjectSpaceManifestListReferenceFND::setRef(
    const FileNodeChunkReference &value) {
  ref = value;
}
