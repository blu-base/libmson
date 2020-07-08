#include "RevisionManifestStart6FND.h"

RevisionManifestStart6FND::RevisionManifestStart6FND() {}

ExtendedGUID RevisionManifestStart6FND::getRid() const { return rid; }

void RevisionManifestStart6FND::setRid(const ExtendedGUID &value) {
  rid = value;
}

ExtendedGUID RevisionManifestStart6FND::getRidDependent() const {
  return ridDependent;
}

void RevisionManifestStart6FND::setRidDependent(const ExtendedGUID &value) {
  ridDependent = value;
}

qint32 RevisionManifestStart6FND::getRevisionRole() const {
  return revisionRole;
}

void RevisionManifestStart6FND::setRevisionRole(const qint32 &value) {
  revisionRole = value;
}

quint16 RevisionManifestStart6FND::getOdcsDefault() const {
  return odcsDefault;
}

void RevisionManifestStart6FND::setOdcsDefault(const quint16 &value) {
  odcsDefault = value;
}

void RevisionManifestStart6FND::deserialize(QDataStream &ds) {
  ds >> rid;
  ds >> ridDependent;
  ds >> revisionRole;
  ds >> odcsDefault;
}

void RevisionManifestStart6FND::serialize(QDataStream &ds) const {
  ds << rid;
  ds << ridDependent;
  ds << revisionRole;
  ds << odcsDefault;
}

void RevisionManifestStart6FND::toDebugString(QDebug dbg) const {
  dbg << " RevisionManifestStart6FND:\n"
      << " rid:          " << rid << '\n'
      << " ridDependent: " << ridDependent << '\n'
      << " revisionRole: " << revisionRole << '\n'
      << " odcsDefault:  " << odcsDefault << '\n';
}
