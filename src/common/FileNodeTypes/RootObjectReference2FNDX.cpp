#include "RootObjectReference2FNDX.h"

RootObjectReference2FNDX::RootObjectReference2FNDX() {}

CompactID RootObjectReference2FNDX::getOidRoot() const { return oidRoot; }

void RootObjectReference2FNDX::setOidRoot(const CompactID &value) {
  oidRoot = value;
}

quint32 RootObjectReference2FNDX::getRootRole() const { return RootRole; }

void RootObjectReference2FNDX::setRootRole(const quint32 &value) {
  RootRole = value;
}

void RootObjectReference2FNDX::deserialize(QDataStream &ds) {
  ds >> oidRoot;
  ds >> RootRole;
}

void RootObjectReference2FNDX::serialize(QDataStream &ds) const {
  ds << oidRoot;
  ds << RootRole;
}

void RootObjectReference2FNDX::toDebugString(QDebug dbg) const {
  dbg << "RootObjectReference2FNDX:\n"
      << "oidRoot: " << oidRoot << '\n'
      << "RootRole: " << RootRole << '\n';
}
