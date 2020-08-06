#ifndef REVISIONROLEANDCONTEXTDECLARATIONFND_H
#define REVISIONROLEANDCONTEXTDECLARATIONFND_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"
#include "RevisionRoleDeclarationFND.h"

class RevisionRoleAndContextDeclarationFND : public IFileNodeType {
private:
  RevisionRoleDeclarationFND m_base;

  ExtendedGUID m_gctxid;

public:
  RevisionRoleAndContextDeclarationFND();

  // IFileNodeType interface
  RevisionRoleDeclarationFND getBase() const;
  void setBase(const RevisionRoleDeclarationFND &value);

  ExtendedGUID getGctxid() const;
  void setGctxid(const ExtendedGUID &value);

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;

  // IFileNodeType interface
public:
  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;
};

#endif // REVISIONROLEANDCONTEXTDECLARATIONFND_H
