#ifndef HASHEDCHUNKDESCRIPTOR2FND_H
#define HASHEDCHUNKDESCRIPTOR2FND_H

#include <QtCore/qglobal.h>

#include "../../commonTypes/FileNodeChunkReference.h"
#include "../../objectTypes/ObjectSpaceObjectPropSet.h"
#include "IFileNodeType.h"


namespace libmson {
namespace priv {

class HashedChunkDescriptor2FND : public IFileNodeType {
private:
  FileNodeChunkReference m_BlobRef;


  QByteArray m_guidHash;

  ObjectSpaceObjectPropSet m_blob;

public:
  HashedChunkDescriptor2FND(FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat);
  HashedChunkDescriptor2FND(quint8 stpFormat, quint8 cbFormat);
  virtual ~HashedChunkDescriptor2FND() = default;

  FileNodeChunkReference BlobRef() const;
  void setBlobRef(const FileNodeChunkReference& BlobRef);

  QByteArray guidHash() const;
  void setGuidHash(const QByteArray& guidHash);

  ObjectSpaceObjectPropSet getPropSet() const;
  void setPropSet(const ObjectSpaceObjectPropSet& value);

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;





  static const quint8 guidHashWidth = 16;
};

} // namespace priv
} // namespace libmson

#endif // HASHEDCHUNKDESCRIPTOR2FND_H
