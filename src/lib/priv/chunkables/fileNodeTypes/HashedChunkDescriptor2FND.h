#ifndef HASHEDCHUNKDESCRIPTOR2FND_H
#define HASHEDCHUNKDESCRIPTOR2FND_H

#include <QtCore/qglobal.h>

#include "IFileNodeType.h"

#include "../ObjectSpaceObjectPropSet.h"
#include "../RevisionStoreChunkContainer.h"

namespace libmson {
namespace priv {

class HashedChunkDescriptor2FND : public IFileNodeType {
private:
  RSChunkContainer_WPtr_t m_blobRef;

  QByteArray m_guidHash;


public:
  HashedChunkDescriptor2FND(RSChunkContainer_WPtr_t parentFileNode);
  virtual ~HashedChunkDescriptor2FND() = default;

  RSChunkContainer_WPtr_t BlobRef() const;
  void setBlobRef(const RSChunkContainer_WPtr_t BlobRef);

  QByteArray guidHash() const;
  void setGuidHash(const QByteArray& guidHash);

  std::shared_ptr<ObjectSpaceObjectPropSet> getPropSet();

  virtual quint64 getSizeInFile() const override;

  // private:
  //  virtual void deserialize(QDataStream& ds) override;
  //  virtual void serialize(QDataStream& ds) const override;


  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;

  static const quint8 guidHashWidth = 16;
};

} // namespace priv
} // namespace libmson

#endif // HASHEDCHUNKDESCRIPTOR2FND_H
