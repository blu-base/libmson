#ifndef OBJECTGROUPMETADATA_H
#define OBJECTGROUPMETADATA_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/CompactUInt64.h"
#include "StreamObject.h"

namespace libmson {
namespace packStore {
namespace streamObj {


class ObjectGroupMetadata
    : public StreamObject
    , public libmson::priv::IStreamable {
private:
  quint64 m_objectChangeFrequency;

public:
  ObjectGroupMetadata();
  quint64 getObjectChangeFrequency() const;
  void setObjectChangeFrequency(const quint64& objectChangeFrequency);

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
typedef std::shared_ptr<ObjectGroupMetadata> ObjectGroupMetadata_SPtr_t;
typedef std::weak_ptr<ObjectGroupMetadata> ObjectGroupMetadata_WPtr_t;

} // namespace streamObj
} // namespace packStore
} // namespace libmson

#endif // OBJECTGROUPMETADATA_H
