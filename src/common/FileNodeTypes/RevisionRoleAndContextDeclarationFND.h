#ifndef REVISIONROLEANDCONTEXTDECLARATIONFND_H
#define REVISIONROLEANDCONTEXTDECLARATIONFND_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"
#include "RevisionRoleDeclarationFND.h"

class RevisionRoleAndContextDeclarationFND : public IFileNodeType {
public:
  RevisionRoleAndContextDeclarationFND();

  RevisionRoleDeclarationFND base;

  ExtendedGUID gctxid;

  // IFileNodeType interface
  RevisionRoleDeclarationFND getBase() const;
  void setBase(const RevisionRoleDeclarationFND &value);

  ExtendedGUID getGctxid() const;
  void setGctxid(const ExtendedGUID &value);

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // REVISIONROLEANDCONTEXTDECLARATIONFND_H
