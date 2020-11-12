#ifndef FILEDATASTORELISTREFERENCEFND_H
#define FILEDATASTORELISTREFERENCEFND_H

#include <QtCore/qglobal.h>

#include "IFileNodeType.h"

#include "../FileNodeListFragment.h"
#include "../RevisionStoreChunkContainer.h"

namespace libmson {
namespace priv {

class FileDataStoreListReferenceFND : public IFileNodeType {
private:
  RSChunkContainer_WPtr_t m_ref;

  //  FileNodeListFragment m_StoreList;

public:
  FileDataStoreListReferenceFND(RSChunkContainer_WPtr_t parentFileNode);
  virtual ~FileDataStoreListReferenceFND() = default;

  RSChunkContainer_WPtr_t getRef() const;
  void setRef(const RSChunkContainer_WPtr_t& value);

  std::shared_ptr<FileNodeListFragment> getStoreList();

  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;

  virtual quint64 getSizeInFile() const override;
};

} // namespace priv
} // namespace libmson

#endif // FILEDATASTORELISTREFERENCEFND_H
