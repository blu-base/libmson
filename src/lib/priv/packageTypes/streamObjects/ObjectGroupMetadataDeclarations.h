#ifndef OBJECTGROUPMETADATADECLARATIONS_H
#define OBJECTGROUPMETADATADECLARATIONS_H

#include <vector>

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "ObjectGroupMetadata.h"
#include "StreamObject.h"

namespace libmson {
namespace packStore {
namespace streamObj {
class ObjectGroupMetadataDeclarations
    : public StreamObject
    , public libmson::priv::IStreamable {
private:
  std::vector<ObjectGroupMetadata_SPtr_t> m_metaData;

public:
  ObjectGroupMetadataDeclarations();
  std::vector<ObjectGroupMetadata_SPtr_t> getMetaData() const;
  void setMetaData(const std::vector<ObjectGroupMetadata_SPtr_t>& metaData);

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

typedef std::shared_ptr<ObjectGroupMetadataDeclarations>
    ObjectGroupMetadataDeclarations_SPtr_t;
typedef std::weak_ptr<ObjectGroupMetadataDeclarations>
    ObjectGroupMetadataDeclarations_WPtr_t;

} // namespace streamObj
} // namespace packStore
} // namespace libmson
#endif // OBJECTGROUPMETADATADECLARATIONS_H
