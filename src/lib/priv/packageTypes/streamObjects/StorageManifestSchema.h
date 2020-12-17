#ifndef StorageManifestSchema_H
#define StorageManifestSchema_H

#include <QUuid>
#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "StreamObject.h"

namespace libmson {
namespace packStore {
namespace streamObj {
class StorageManifestSchema
    : public StreamObject
    , public libmson::priv::IStreamable {
private:
  QUuid m_guid;

public:
  StorageManifestSchema();

  QUuid getGuid() const;
  void setGuid(const QUuid& guid);

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

typedef std::shared_ptr<StorageManifestSchema> StorageManifestSchema_SPtr_t;
typedef std::weak_ptr<StorageManifestSchema> StorageManifestSchema_WPtr_t;

} // namespace streamObj
} // namespace packStore
} // namespace libmson

#endif // StorageManifestSchema_H
