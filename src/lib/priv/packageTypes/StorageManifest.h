#ifndef STORAGEMANIFEST_H
#define STORAGEMANIFEST_H

#include <vector>


#include <QtCore/qglobal.h>


#include "interfaces/IDataElementBody.h"
#include "StreamObjectHeader.h"
#include "streamObjects/StorageManifestRootDeclare.h"
#include "streamObjects/StorageManifestSchema.h"


namespace libmson {
namespace packStore {

class StorageManifest
    : public DataElementBody
    , public priv::IStreamable {
private:
  streamObj::StorageManifestSchema_SPtr_t m_schema;

  std::vector<streamObj::StorageManifestRootDeclare_SPtr_t> m_rootDeclares;

public:
  StorageManifest();
  ~StorageManifest() = default;

  streamObj::StorageManifestSchema_SPtr_t getSchema() const;
  void setSchema(const streamObj::StorageManifestSchema_SPtr_t& schema);
  std::vector<streamObj::StorageManifestRootDeclare_SPtr_t>
  getRootDeclares() const;
  void setRootDeclares(
      const std::vector<streamObj::StorageManifestRootDeclare_SPtr_t>&
          rootDeclares);

  // IStreamable interface
private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;

  // DataElementBody interface
protected:
  virtual quint64 cb() const override;

public:
  virtual DataElementType getType() const override;
};

typedef std::shared_ptr<StorageManifest> StorageManifest_SPtr_t;
typedef std::weak_ptr<StorageManifest> StorageManifest_WPtr_t;

} // namespace packStore
} // namespace libmson

#endif // STORAGEMANIFEST_H
