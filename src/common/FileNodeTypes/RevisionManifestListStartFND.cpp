#include "RevisionManifestListStartFND.h"

RevisionManifestListStartFND::RevisionManifestListStartFND() {}

ExtendedGUID RevisionManifestListStartFND::getGosid() const { return gosid; }

void RevisionManifestListStartFND::setGosid(const ExtendedGUID &value) {
  gosid = value;
}

quint32 RevisionManifestListStartFND::getNInstance() const { return nInstance; }

void RevisionManifestListStartFND::setNInstance(const quint32 &value) {
  nInstance = value;
}

void RevisionManifestListStartFND::deserialize(QDataStream &ds) {
  ds >> gosid;
  ds >> nInstance;
}

void RevisionManifestListStartFND::serialize(QDataStream &ds) const {
  ds << gosid;
  ds << nInstance;
}

void RevisionManifestListStartFND::toDebugString(QDebug dbg) const {
  dbg << " RevisionManifestListStartFND: gosid: " << gosid << " nInstance: " << nInstance << '\n';
}
