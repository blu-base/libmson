#ifndef HASHEDCHUNKDESCRIPTOR2FND_H
#define HASHEDCHUNKDESCRIPTOR2FND_H

#include "../commonTypes/FileNodeChunkReference.h"
#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

class HashedChunkDescriptor2FND : public IFileNodeType {
private:
  FileNodeChunkReference m_BlobRef;

  QByteArray m_guidHash;

public:
  HashedChunkDescriptor2FND(FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat);
  HashedChunkDescriptor2FND(quint8 stpFormat, quint8 cbFormat);
  ~HashedChunkDescriptor2FND();

  FileNodeChunkReference BlobRef() const;
  void setBlobRef(const FileNodeChunkReference &BlobRef);

  QByteArray guidHash() const;
  void setGuidHash(const QByteArray &guidHash);

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;

  // IFileNodeType interface
public:
  virtual void generateXml(QXmlStreamWriter& xmlWriter) const override;
};

#endif // HASHEDCHUNKDESCRIPTOR2FND_H
