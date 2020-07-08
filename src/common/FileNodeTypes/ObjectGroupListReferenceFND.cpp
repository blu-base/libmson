#include "ObjectGroupListReferenceFND.h"

ObjectGroupListReferenceFND::ObjectGroupListReferenceFND(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : mRef(stpFormat, cbFormat) {}

ObjectGroupListReferenceFND::ObjectGroupListReferenceFND(quint8 stpFormat,
                                                         quint8 cbFormat)
    : mRef(stpFormat, cbFormat) {}

ExtendedGUID ObjectGroupListReferenceFND::objectGroupID() const {
  return mObjectGroupID;
}

void ObjectGroupListReferenceFND::setObjectGroupID(
    const ExtendedGUID &objectGroupID) {
  mObjectGroupID = objectGroupID;
}

FileNodeChunkReference ObjectGroupListReferenceFND::ref() const { return mRef; }

void ObjectGroupListReferenceFND::setRef(const FileNodeChunkReference &ref) {
  mRef = ref;
}

void ObjectGroupListReferenceFND::deserialize(QDataStream &ds) {
  ds >> mRef;
  ds >> mObjectGroupID;
}

void ObjectGroupListReferenceFND::serialize(QDataStream &ds) const {
  ds << mRef;
  ds << mObjectGroupID;
}

void ObjectGroupListReferenceFND::toDebugString(QDebug dbg) const {
  dbg << " ObjectGroupListReferenceFND:\n"
      << " ref:           " << mRef << '\n'
      << " ObjectGroupID: " << mObjectGroupID << '\n';
}
