#ifndef REVISIONMANIFESTSTREAMOBJ_H
#define REVISIONMANIFESTSTREAMOBJ_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/CompactExtGuid.h"
#include "StreamObject.h"


namespace libmson {
namespace packStore {
namespace streamObj {


class RevisionManifest
    : public StreamObject
    , public libmson::priv::IStreamable {
private:
  CompactExtGuid m_revisionId;
  CompactExtGuid m_baseRevisionId;

public:
  RevisionManifest();
  CompactExtGuid getRevisionId() const;
  void setRevisionId(const CompactExtGuid& revisionId);
  CompactExtGuid getBaseRevisionId() const;
  void setBaseRevisionId(const CompactExtGuid& baseRevisionId);

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


typedef std::shared_ptr<RevisionManifest> RevisionManifest_SPtr_t;
typedef std::weak_ptr<RevisionManifest> RevisionManifest_WPtr_t;

} // namespace streamObj
} // namespace packStore
} // namespace libmson


#endif // REVISIONMANIFESTSTREAMOBJ_H
