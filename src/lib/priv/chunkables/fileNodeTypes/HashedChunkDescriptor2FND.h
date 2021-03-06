#ifndef HASHEDCHUNKDESCRIPTOR2FND_H
#define HASHEDCHUNKDESCRIPTOR2FND_H

#include <QtCore/qglobal.h>

#include "IFileNodeType.h"
#include <QByteArray>

namespace libmson {
namespace priv {

typedef std::shared_ptr<class ObjectSpaceObjectPropSet>
    ObjectSpaceObjectPropSet_SPtr_t;
typedef std::weak_ptr<class ObjectSpaceObjectPropSet>
    ObjectSpaceObjectPropSet_WPtr_t;


class HashedChunkDescriptor2FND : public IFileNodeType {
private:
  ObjectSpaceObjectPropSet_WPtr_t m_blobRef;

  QByteArray m_guidHash;


public:
  HashedChunkDescriptor2FND(FileNode_SPtr_t parentFileNode);
  virtual ~HashedChunkDescriptor2FND() = default;

  ObjectSpaceObjectPropSet_WPtr_t getBlobRef() const;
  void setBlobRef(const ObjectSpaceObjectPropSet_SPtr_t BlobRef);

  QByteArray getGuidHash() const;
  void setGuidHash(const QByteArray& guidHash);

  virtual quint64 getSizeInFile() const override;
  virtual FileNodeTypeID getType() const override
  {
    return FileNodeTypeID::HashedChunkDescriptor2FND;
  };

  friend class RevisionStoreFileParser;

  static const quint8 guidHashWidth = 16;
};

} // namespace priv
} // namespace libmson

#endif // HASHEDCHUNKDESCRIPTOR2FND_H
