#ifndef REVISIONROLEDECLARATIONFND_H
#define REVISIONROLEDECLARATIONFND_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"

namespace libmson {
namespace priv {

class RevisionRoleDeclarationFND
    : public IFileNodeType
    , public IStreamable {
private:
  ExtendedGUID m_rid;
  quint32 m_RevisionRole;

public:
  RevisionRoleDeclarationFND(FileNode_WPtr_t parentFileNode);
  virtual ~RevisionRoleDeclarationFND() = default;

  ExtendedGUID getRid() const;
  void setRid(const ExtendedGUID& value);

  quint32 getRevisionRole() const;
  void setRevisionRole(const quint32& value);

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;


  static const quint64 sizeInFile;
};

} // namespace priv
} // namespace libmson

#endif // REVISIONROLEDECLARATIONFND_H
