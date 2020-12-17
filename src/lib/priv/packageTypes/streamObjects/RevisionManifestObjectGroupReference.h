#ifndef REVISIONMANIFESTOBJECTGROUPREFERENCE_H
#define REVISIONMANIFESTOBJECTGROUPREFERENCE_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/CompactExtGuid.h"
#include "StreamObject.h"

namespace libmson {
namespace packStore {
namespace streamObj {
class RevisionManifestObjectGroupReference
    : public StreamObject
    , public libmson::priv::IStreamable {
private:
  CompactExtGuid m_objectGroup;

public:
  RevisionManifestObjectGroupReference();

  CompactExtGuid getObjectGroup() const;
  void setObjectGroup(const CompactExtGuid& objectGroup);

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

typedef std::shared_ptr<RevisionManifestObjectGroupReference>
    RevisionManifestObjectGroupReference_SPtr_t;
typedef std::weak_ptr<RevisionManifestObjectGroupReference>
    RevisionManifestObjectGroupReference_WPtr_t;


} // namespace streamObj
} // namespace packStore
} // namespace libmson
#endif // REVISIONMANIFESTOBJECTGROUPREFERENCE_H
