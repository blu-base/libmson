#include "ObjectSpaceManifestRootFND.h"

ObjectSpaceManifestRootFND::ObjectSpaceManifestRootFND() {}

ExtendedGUID ObjectSpaceManifestRootFND::getGosidRoot() const {
  return gosidRoot;
}

void ObjectSpaceManifestRootFND::setGosidRoot(const ExtendedGUID &value) {
  gosidRoot = value;
}

void ObjectSpaceManifestRootFND::deserialize(QDataStream &ds) {
  ds >> gosidRoot;
}

void ObjectSpaceManifestRootFND::serialize(QDataStream &ds) const {
  ds << gosidRoot;
}

void ObjectSpaceManifestRootFND::toDebugString(QDebug dbg) const {
  dbg << "ObjectSpaceManifestRootFND:\n"
      << " gosidRoot: " << gosidRoot;
}
