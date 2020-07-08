#include "ObjectSpaceManifestListStartFND.h"

ObjectSpaceManifestListStartFND::ObjectSpaceManifestListStartFND() {}

ExtendedGUID ObjectSpaceManifestListStartFND::getGosid() const { return gosid; }

void ObjectSpaceManifestListStartFND::setGosid(const ExtendedGUID &value) {
  gosid = value;
}

void ObjectSpaceManifestListStartFND::deserialize(QDataStream &ds) {
  ds >> gosid;
}

void ObjectSpaceManifestListStartFND::serialize(QDataStream &ds) const {
  ds << gosid;
}

void ObjectSpaceManifestListStartFND::toDebugString(QDebug dbg) const {
  dbg << " ObjectSpaceManifestListStartFND: gosid: " << gosid << '\n';
}
