#ifndef STORAGEINDEX_H
#define STORAGEINDEX_H

#include <QtCore/qglobal.h>
#include <vector>

#include "../commonTypes/CellId.h"
#include "../commonTypes/CompactUInt64.h"
#include "../commonTypes/LongExtGuid.h"
#include "interfaces/IDataElementBody.h"
#include "StreamObjectHeader.h"
#include "streamObjects/StorageIndexCellMapping.h"
#include "streamObjects/StorageIndexManifestMapping.h"
#include "streamObjects/StorageIndexRevisionMapping.h"


namespace libmson {
namespace packStore {


class StorageIndex
    : public DataElementBody
    , public priv::IStreamable {
private:
  streamObj::StorageIndexManifestMapping_SPtr_t m_manifestMapping;

  std::vector<streamObj::StorageIndexCellMapping_SPtr_t> m_cellMappings;
  std::vector<streamObj::StorageIndexRevisionMapping_SPtr_t> m_revisionMappings;


public:
  StorageIndex();
  ~StorageIndex() = default;

  streamObj::StorageIndexManifestMapping_SPtr_t getManifestMapping() const;
  void setManifestMapping(
      const streamObj::StorageIndexManifestMapping_SPtr_t& manifestMapping);

  std::vector<streamObj::StorageIndexCellMapping_SPtr_t>
  getCellMappings() const;
  std::vector<streamObj::StorageIndexCellMapping_SPtr_t>& cellMappings();

  void
  setCellMappings(const std::vector<streamObj::StorageIndexCellMapping_SPtr_t>&
                      cellMappings);

  std::vector<streamObj::StorageIndexRevisionMapping_SPtr_t>
  getRevisionMappings() const;
  std::vector<streamObj::StorageIndexRevisionMapping_SPtr_t>&
  revisionMappings();
  void setRevisionMappings(
      const std::vector<streamObj::StorageIndexRevisionMapping_SPtr_t>&
          revisionMappings);


  friend class PackageStoreFileParser;

  // IStreamable interface
private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;

  // DataElementBody interface
public:
  virtual DataElementType getType() const override;

  // DataElementBody interface
protected:
  virtual quint64 cb() const override;
};


typedef std::shared_ptr<StorageIndex> StorageIndex_SPtr_t;
typedef std::weak_ptr<StorageIndex> StorageIndex_WPtr_t;

} // namespace packStore
} // namespace libmson

#endif // STORAGEINDEX_H
