#include "RevisionRoleDeclarationFND.h"

RevisionRoleDeclarationFND::RevisionRoleDeclarationFND() {}

quint32 RevisionRoleDeclarationFND::getRevisionRole() const {
  return RevisionRole;
}

void RevisionRoleDeclarationFND::setRevisionRole(const quint32 &value) {
  RevisionRole = value;
}

ExtendedGUID RevisionRoleDeclarationFND::getRid() const { return rid; }

void RevisionRoleDeclarationFND::setRid(const ExtendedGUID &value) {
  rid = value;
}

void RevisionRoleDeclarationFND::deserialize(QDataStream &ds) {
  ds >> rid;
  ds >> RevisionRole;
}

void RevisionRoleDeclarationFND::serialize(QDataStream &ds) const {
  ds << rid;
  ds << RevisionRole;
}

void RevisionRoleDeclarationFND::toDebugString(QDebug dbg) const {
  dbg << " RevisionRoleDeclarationFND:\n"
      << " Rid: " << rid << '\n'
      << " RevisionRole: " << RevisionRole << '\n';
}
