#ifndef REVISIONROLEDECLARATIONFND_H
#define REVISIONROLEDECLARATIONFND_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"

namespace MSONcommon {

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

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;

  static const quint64 sizeInFile;
};

} // namespace MSONcommon

#endif // REVISIONROLEDECLARATIONFND_H
