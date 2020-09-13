#ifndef HASHEDCHUNKDESCRIPTOR2FND_H
#define HASHEDCHUNKDESCRIPTOR2FND_H

#include "../commonTypes/FileNodeChunkReference.h"
#include "../otherTypes/ObjectSpaceObjectPropSet.h"
#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace MSONcommon {

class HashedChunkDescriptor2FND : public IFileNodeType {
private:
  FileNodeChunkReference m_BlobRef;

  static const quint8 guidHashWidth = 16;
  QByteArray m_guidHash;

  ObjectSpaceObjectPropSet m_blob;

public:
  HashedChunkDescriptor2FND(FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat);
  HashedChunkDescriptor2FND(quint8 stpFormat, quint8 cbFormat);
  virtual ~HashedChunkDescriptor2FND() = default;

  FileNodeChunkReference BlobRef() const;
  void setBlobRef(const FileNodeChunkReference &BlobRef);

  QByteArray guidHash() const;
  void setGuidHash(const QByteArray &guidHash);

  ObjectSpaceObjectPropSet getPropSet() const;
  void setPropSet(const ObjectSpaceObjectPropSet &value);

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;
};

} // namespace MSONcommon

#endif // HASHEDCHUNKDESCRIPTOR2FND_H
