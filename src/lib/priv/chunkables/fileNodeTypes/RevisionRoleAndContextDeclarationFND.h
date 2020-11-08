#ifndef REVISIONROLEANDCONTEXTDECLARATIONFND_H
#define REVISIONROLEANDCONTEXTDECLARATIONFND_H

#include <QtCore/qglobal.h>

#include "../../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"
#include "RevisionRoleDeclarationFND.h"

namespace libmson{
namespace priv{

class RevisionRoleAndContextDeclarationFND : public IFileNodeType {
private:
  RevisionRoleDeclarationFND m_base;
  ExtendedGUID m_gctxid;

public:
  RevisionRoleAndContextDeclarationFND() = default;

  RevisionRoleDeclarationFND getBase() const;
  void setBase(const RevisionRoleDeclarationFND &value);

  ExtendedGUID getGctxid() const;
  void setGctxid(const ExtendedGUID &value);

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;




};

} //namespace priv
} // namespace libmson

#endif // REVISIONROLEANDCONTEXTDECLARATIONFND_H
