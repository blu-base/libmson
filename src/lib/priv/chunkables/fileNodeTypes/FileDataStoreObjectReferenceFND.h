#ifndef FILEDATASTOREOBJECTREFERENCEFND_H
#define FILEDATASTOREOBJECTREFERENCEFND_H

#include <QtCore/qglobal.h>

#include "../FileDataStoreObject.h"
#include "../RevisionStoreChunkContainer.h"
#include "IFileNodeType.h"
#include <QUuid>


namespace libmson {
namespace priv {

class FileDataStoreObjectReferenceFND : public IFileNodeType {
private:
  RSChunkContainer_WPtr_t m_blobRef;
  QUuid m_guidReference;

  //  FileDataStoreObject m_blob;

public:
  FileDataStoreObjectReferenceFND(RSChunkContainer_WPtr_t parentFileNode);
  virtual ~FileDataStoreObjectReferenceFND() = default;

  RSChunkContainer_WPtr_t getBlobRef() const;
  void setBlobRef(const RSChunkContainer_WPtr_t& value);

  QUuid getGuidReference() const;
  void setGuidReference(const QUuid& value);

  std::shared_ptr<FileDataStoreObject> getFileDataStoreObject();


  virtual quint64 getSizeInFile() const override;

  // private:
  //  virtual void deserialize(QDataStream& ds) override;
  //  virtual void serialize(QDataStream& ds) const override;

  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;

  static const quint64 sizeOfGUID = 16;
};

} // namespace priv
} // namespace libmson

#endif // FILEDATASTOREOBJECTREFERENCEFND_H
