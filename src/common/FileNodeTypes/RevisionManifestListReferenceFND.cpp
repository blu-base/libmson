#include "RevisionManifestListReferenceFND.h"

RevisionManifestListReferenceFND::RevisionManifestListReferenceFND(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : ref{FileNodeChunkReference(stpFormat, cbFormat)} {}
RevisionManifestListReferenceFND::RevisionManifestListReferenceFND(
    quint8 stpFormat, quint8 cbFormat)
    : ref{FileNodeChunkReference(stpFormat, cbFormat)} {}

FileNodeChunkReference RevisionManifestListReferenceFND::getRef() const {
  return ref;
}

void RevisionManifestListReferenceFND::setRef(
    const FileNodeChunkReference &value) {
  ref = value;
}

void RevisionManifestListReferenceFND::deserialize(QDataStream &ds) {
  ds >> ref;
}

void RevisionManifestListReferenceFND::serialize(QDataStream &ds) const {
  ds << ref;
}

void RevisionManifestListReferenceFND::toDebugString(QDebug dbg) const {
  dbg << "RevisionManifestListReferenceFND:\n"
      << " ref: " << ref;
}
