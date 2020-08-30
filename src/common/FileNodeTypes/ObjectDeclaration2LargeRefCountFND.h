#ifndef OBJECTDECLARATION2LARGEREFCOUNTFND_H
#define OBJECTDECLARATION2LARGEREFCOUNTFND_H

#include "../commonTypes/FileNodeChunkReference.h"
#include "../otherTypes/ObjectDeclaration2Body.h"
#include "../otherTypes/ObjectSpaceObjectPropSet.h"
#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

class ObjectDeclaration2LargeRefCountFND : public IFileNodeType {
private:
  FileNodeChunkReference m_BlobRef;
  ObjectDeclaration2Body m_body;
  quint32 m_cRef;

  ObjectSpaceObjectPropSet m_blob;

public:
  ObjectDeclaration2LargeRefCountFND(FNCR_STP_FORMAT stpFormat,
                                     FNCR_CB_FORMAT cbFormat);

  ObjectDeclaration2LargeRefCountFND(quint8 stpFormat, quint8 cbFormat);
  ~ObjectDeclaration2LargeRefCountFND();

  FileNodeChunkReference BlobRef() const;
  void setBlobRef(const FileNodeChunkReference &BlobRef);

  ObjectDeclaration2Body body() const;
  void setBody(const ObjectDeclaration2Body &body);

  quint32 cRef() const;
  void setCRef(const quint32 &cRef);

  ObjectSpaceObjectPropSet getPropSet() const;
  void setPropSet(const ObjectSpaceObjectPropSet &value);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // OBJECTDECLARATION2LARGEREFCOUNTFND_H
