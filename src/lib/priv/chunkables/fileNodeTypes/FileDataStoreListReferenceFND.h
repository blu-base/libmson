#ifndef FILEDATASTORELISTREFERENCEFND_H
#define FILEDATASTORELISTREFERENCEFND_H

#include <QtCore/qglobal.h>

#include "../FileNodeListFragment.h"
#include "IFileNodeType.h"


namespace libmson {
namespace priv {

class FileDataStoreListReferenceFND : public IFileNodeType {
private:
  FileNodeListFragment_WPtr_t m_ref;

  //  FileNodeListFragment m_StoreList;

public:
  FileDataStoreListReferenceFND(FileNode_WPtr_t parentFileNode);
  virtual ~FileDataStoreListReferenceFND() = default;

  FileNodeListFragment_WPtr_t getRef() const;
  void setRef(const FileNodeListFragment_WPtr_t value);

  std::shared_ptr<FileNodeListFragment> getStoreList();

  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;

  virtual quint64 getSizeInFile() const override;
};

} // namespace priv
} // namespace libmson

#endif // FILEDATASTORELISTREFERENCEFND_H
