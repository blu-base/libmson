#ifndef FILEDATASTOREOBJECTREFERENCEFND_H
#define FILEDATASTOREOBJECTREFERENCEFND_H

#include <QtCore/qglobal.h>

#include "IFileNodeType.h"
#include <QUuid>


namespace libmson {
namespace priv {

typedef std::shared_ptr<class FileDataStoreObject> FileDataStoreObject_SPtr_t;
typedef std::weak_ptr<class FileDataStoreObject> FileDataStoreObject_WPtr_t;

class FileDataStoreObjectReferenceFND : public IFileNodeType {
private:
  FileDataStoreObject_WPtr_t m_blobRef;
  QUuid m_guidReference;

  //  FileDataStoreObject m_blob;

public:
  FileDataStoreObjectReferenceFND(FileNode_SPtr_t parentFileNode);
  virtual ~FileDataStoreObjectReferenceFND() = default;

  FileDataStoreObject_WPtr_t getBlobRef() const;
  void setBlobRef(const FileDataStoreObject_SPtr_t& value);

  QUuid getGuidReference() const;
  void setGuidReference(const QUuid& value);

  virtual quint64 getSizeInFile() const override;
  virtual FileNodeTypeID getType() const override
  {
    return FileNodeTypeID::FileDataStoreObjectReferenceFND;
  };

  // private:
  //  virtual void deserialize(QDataStream& ds) override;
  //  virtual void serialize(QDataStream& ds) const override;

  friend class RevisionStoreFileParser;


  static const quint64 sizeOfGUID = 16;
};

} // namespace priv
} // namespace libmson

#endif // FILEDATASTOREOBJECTREFERENCEFND_H
