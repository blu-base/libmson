#include "RootObjectReference3FND.h"

RootObjectReference3FND::RootObjectReference3FND() {}

quint32 RootObjectReference3FND::getRootRole() const { return RootRole; }

void RootObjectReference3FND::setRootRole(const quint32 &value) {
  RootRole = value;
}

ExtendedGUID RootObjectReference3FND::getOidRoot() const { return oidRoot; }

void RootObjectReference3FND::setOidRoot(const ExtendedGUID &value) {
  oidRoot = value;
}

void RootObjectReference3FND::deserialize(QDataStream &ds) {
  ds >> oidRoot;
  ds >> RootRole;
}

void RootObjectReference3FND::serialize(QDataStream &ds) const {
  ds << oidRoot;
  ds << RootRole;
}

void RootObjectReference3FND::toDebugString(QDebug dbg) const {
  dbg << " RootObjectReference2FNDX:\n"
      << " oidRoot: " << oidRoot << '\n'
      << " RootRole: " << RootRole << '\n';
}
