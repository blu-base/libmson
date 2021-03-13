#ifndef STORAGEINDEX_H
#define STORAGEINDEX_H

#include <QtCore/qglobal.h>
#include <vector>

#include "DataElement.h"

namespace libmson {
namespace fsshttpb {

class StorageIndexManifestMapping;
typedef std::shared_ptr<StorageIndexManifestMapping>
    StorageIndexManifestMapping_SPtr_t;
typedef std::weak_ptr<StorageIndexManifestMapping>
    StorageIndexManifestMapping_WPtr_t;
class StorageIndexCellMapping;
typedef std::shared_ptr<StorageIndexCellMapping> StorageIndexCellMapping_SPtr_t;
typedef std::weak_ptr<StorageIndexCellMapping> StorageIndexCellMapping_WPtr_t;
class StorageIndexRevisionMapping;
typedef std::shared_ptr<StorageIndexRevisionMapping>
    StorageIndexRevisionMapping_SPtr_t;
typedef std::weak_ptr<StorageIndexRevisionMapping>
    StorageIndexRevisionMapping_WPtr_t;


class StorageIndex : public DataElement {

public:
  StorageIndex();
  ~StorageIndex() = default;

  /**
   * @brief getManifestMapping gets the StorageIndexManifestMapping, the first if multiple are present in this StreamObject.
   * Though there really should be only one.
   * @return
   */
  StorageIndexManifestMapping_WPtr_t getManifestMapping() const;

  /**
   * @brief setManifestMapping removes the present StorageIndexManifestMapping and preprends manifestMapping
   * @param manifestMapping
   */
  void setManifestMapping(const StorageIndexManifestMapping_SPtr_t& manifestMapping);


  std::vector<StorageIndexCellMapping_WPtr_t> getCellMappings() const;
  /**
   * @brief setCellMappings removes all StorageIndexCellMapping present
   * in this object and appends the cellMappings
   * @param cellMappings
   */
  void setCellMappings(
      const std::vector<StorageIndexCellMapping_SPtr_t>& cellMappings);


  std::vector<StorageIndexRevisionMapping_WPtr_t> getRevisionMappings() const;
  /**
   * @brief setRevisionMappings removes all StorageIndexRevisionMapping present
   * in this object and appends the revisionMappings
   * @param revisionMappings
   */
  void setRevisionMappings(
      const std::vector<StorageIndexRevisionMapping_SPtr_t>& revisionMappings);


  friend class PackageStoreFileParser;
};


typedef std::shared_ptr<StorageIndex> StorageIndex_SPtr_t;
typedef std::weak_ptr<StorageIndex> StorageIndex_WPtr_t;

} // namespace fsshttpb
} // namespace libmson

#endif // STORAGEINDEX_H
