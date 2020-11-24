#ifndef ROOTOBJECTREFERENCE2FNDX_H
#define ROOTOBJECTREFERENCE2FNDX_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/CompactID.h"
#include "IFileNodeType.h"

namespace libmson {
namespace priv {

class RootObjectReference2FNDX
    : public IFileNodeType
    , public IStreamable {
private:
  CompactID m_oidRoot;
  quint32 m_RootRole;

public:
  RootObjectReference2FNDX(FileNode_SPtr_t parentFileNode);
  virtual ~RootObjectReference2FNDX() = default;


  CompactID getOidRoot() const;
  void setOidRoot(const CompactID& value);

  quint32 getRootRole() const;
  void setRootRole(const quint32& value);

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;


  static const quint64 sizeInFile;
};

} // namespace priv
} // namespace libmson

#endif // ROOTOBJECTREFERENCE2FNDX_H
