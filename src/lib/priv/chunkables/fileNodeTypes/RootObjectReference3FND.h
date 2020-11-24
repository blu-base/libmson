#ifndef ROOTOBJECTREFERENCE3FND_H
#define ROOTOBJECTREFERENCE3FND_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"

namespace libmson {
namespace priv {

class RootObjectReference3FND
    : public IFileNodeType
    , public IStreamable {
private:
  ExtendedGUID m_oidRoot;
  quint32 m_RootRole;

public:
  RootObjectReference3FND(FileNode_SPtr_t parentFileNode);
  virtual ~RootObjectReference3FND() = default;

  // IFileNodeType interface
  ExtendedGUID getOidRoot() const;
  void setOidRoot(const ExtendedGUID& value);

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

#endif // ROOTOBJECTREFERENCE3FND_H
