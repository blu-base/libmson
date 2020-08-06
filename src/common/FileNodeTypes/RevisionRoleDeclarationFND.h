#ifndef REVISIONROLEDECLARATIONFND_H
#define REVISIONROLEDECLARATIONFND_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"

class RevisionRoleDeclarationFND : public IFileNodeType {
private:
  ExtendedGUID m_rid;
  quint32 m_RevisionRole;

public:
  RevisionRoleDeclarationFND();

  ExtendedGUID getRid() const;
  void setRid(const ExtendedGUID &value);

  quint32 getRevisionRole() const;
  void setRevisionRole(const quint32 &value);

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;

  // IFileNodeType interface
public:
  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;
};

#endif // REVISIONROLEDECLARATIONFND_H
