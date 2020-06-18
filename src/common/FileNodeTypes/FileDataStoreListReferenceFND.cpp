#include "FileDataStoreListReferenceFND.h"

FileDataStoreListReferenceFND::FileDataStoreListReferenceFND(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : ref{FileNodeChunkReference(stpFormat, cbFormat)} {}

FileDataStoreListReferenceFND::FileDataStoreListReferenceFND(
    quint8 stpFormat, quint8 cbFormat)
    : ref{FileNodeChunkReference(stpFormat, cbFormat)} {}

FileDataStoreListReferenceFND::~FileDataStoreListReferenceFND() {}



FileNodeChunkReference FileDataStoreListReferenceFND::getRef() const {
  return ref;
}

void FileDataStoreListReferenceFND::setRef(
    const FileNodeChunkReference &value) {
  ref = value;
}


void FileDataStoreListReferenceFND::deserialize(QDataStream &ds) {
  ds >> ref;
}

void FileDataStoreListReferenceFND::serialize(QDataStream &ds) const {
  ds << ref;
}

void FileDataStoreListReferenceFND::toDebugString(QDebug dbg) const {
  dbg << "FileDataStoreObjectReferenceFND:\n"
      << "ref: " << ref << '\n';
}
