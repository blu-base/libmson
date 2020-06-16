#ifndef REVISIONROLEDECLARATIONFND_H
#define REVISIONROLEDECLARATIONFND_H

#include <QtCore/qglobal.h>

#include "IFileNodeType.h"
#include "../commonTypes/ExtendedGUID.h"

class RevisionRoleDeclarationFND : public IFileNodeType
{
public:
  RevisionRoleDeclarationFND();

  ExtendedGUID rid;
  quint32 RevisionRole;


  ExtendedGUID getRid() const;
  void setRid(const ExtendedGUID& value);

  quint32 getRevisionRole() const;
  void setRevisionRole(const quint32& value);

private:
  void deserialize(QDataStream& ds) override;
  void serialize(QDataStream& ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // REVISIONROLEDECLARATIONFND_H
