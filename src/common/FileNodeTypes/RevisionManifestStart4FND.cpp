#include "RevisionManifestStart4FND.h"

RevisionManifestStart4FND::RevisionManifestStart4FND() {}

ExtendedGUID RevisionManifestStart4FND::getRid() const { return rid; }

void RevisionManifestStart4FND::setRid(const ExtendedGUID &value) {
  rid = value;
}

ExtendedGUID RevisionManifestStart4FND::getRidDependent() const {
  return ridDependent;
}

void RevisionManifestStart4FND::setRidDependent(const ExtendedGUID &value) {
  ridDependent = value;
}

quint64 RevisionManifestStart4FND::getTimeCreation() const {
  return timeCreation;
}

void RevisionManifestStart4FND::setTimeCreation(const quint64 &value) {
  timeCreation = value;
}

qint32 RevisionManifestStart4FND::getRevisionRole() const {
  return revisionRole;
}

void RevisionManifestStart4FND::setRevisionRole(const qint32 &value) {
  revisionRole = value;
}

quint16 RevisionManifestStart4FND::getOdcsDefault() const {
  return odcsDefault;
}

void RevisionManifestStart4FND::setOdcsDefault(const quint16 &value) {
  odcsDefault = value;
}

void RevisionManifestStart4FND::deserialize(QDataStream &ds) {
  ds >> rid;
  ds >> ridDependent;
  ds >> timeCreation;
  ds >> revisionRole;
  ds >> odcsDefault;
}

void RevisionManifestStart4FND::serialize(QDataStream &ds) const {
  ds << rid;
  ds << ridDependent;
  ds << timeCreation;
  ds << revisionRole;
  ds << odcsDefault;
}

void RevisionManifestStart4FND::toDebugString(QDebug dbg) const {
  dbg << "RevisionManifestStart4FND:\n"
      << "\trid:          " << rid << '\n'
      << "\tridDependent: " << ridDependent << '\n'
      << "\trevisionRole: " << revisionRole << '\n'
      << "\todcsDefault:  " << odcsDefault << '\n';
}
