#ifndef REVISIONMANIFESTROOTDECLARE_H
#define REVISIONMANIFESTROOTDECLARE_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/CompactExtGuid.h"
#include "StreamObject.h"

namespace libmson {
namespace packStore {
namespace streamObj {

class RevisionManifestRootDeclare
    : public StreamObject
    , public libmson::priv::IStreamable {
private:
  CompactExtGuid m_root;
  CompactExtGuid m_object;

public:
  RevisionManifestRootDeclare();

  CompactExtGuid getRoot() const;
  void setRoot(const CompactExtGuid& root);
  CompactExtGuid getObject() const;
  void setObject(const CompactExtGuid& object);

  // IStreamable interface
private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;

  // StreamObject interface
protected:
  virtual quint64 body_cb() const override;

public:
  virtual StreamObjectType getType() const override;
};

typedef std::shared_ptr<RevisionManifestRootDeclare> RevisionManifestRootDeclare_SPtr_t;
typedef std::weak_ptr<RevisionManifestRootDeclare> RevisionManifestRootDeclare_WPtr_t;

} // namespace streamObj
} // namespace packStore
} // namespace libmson
#endif // REVISIONMANIFESTROOTDECLARE_H
