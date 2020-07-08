#include "FileDataStoreObjectReferenceFND.h"

FileDataStoreObjectReferenceFND::FileDataStoreObjectReferenceFND(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : ref(stpFormat, cbFormat) {}

FileDataStoreObjectReferenceFND::FileDataStoreObjectReferenceFND(
    quint8 stpFormat, quint8 cbFormat)
    : ref(stpFormat, cbFormat) {}

FileDataStoreObjectReferenceFND::~FileDataStoreObjectReferenceFND() {}

FileNodeChunkReference FileDataStoreObjectReferenceFND::getRef() const {
  return ref;
}

void FileDataStoreObjectReferenceFND::setRef(
    const FileNodeChunkReference &value) {
  ref = value;
}

QUuid FileDataStoreObjectReferenceFND::getGuidReference() const {
  return guidReference;
}

void FileDataStoreObjectReferenceFND::setGuidReference(const QUuid &value) {
  guidReference = value;
}

void FileDataStoreObjectReferenceFND::deserialize(QDataStream &ds) {
  ds >> ref;
  ds >> guidReference;
}

void FileDataStoreObjectReferenceFND::serialize(QDataStream &ds) const {
  ds << ref;
  ds << guidReference;
}

void FileDataStoreObjectReferenceFND::toDebugString(QDebug dbg) const {
  dbg << " FileDataStoreObjectReferenceFND:\n"
      << " ref: " << ref << '\n'
      << " guidReference: " << guidReference << '\n';
}
