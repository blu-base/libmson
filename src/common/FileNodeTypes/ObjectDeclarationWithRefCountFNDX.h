#ifndef OBJECTDECLARATIONWITHREFCOUNTFNDX_H
#define OBJECTDECLARATIONWITHREFCOUNTFNDX_H

#include <QtCore/qglobal.h>


#include "../commonTypes/FileNodeChunkReference.h"
#include "../otherTypes/ObjectDeclarationWithRefCountBody.h"
#include "../otherTypes/ObjectSpaceObjectPropSet.h"
#include "IFileNodeType.h"

class ObjectDeclarationWithRefCountFNDX : public IFileNodeType {
private:

    FileNodeChunkReference m_objectRef;

    ObjectDeclarationWithRefCountBody m_body;

    quint8 m_cRef;

    ObjectSpaceObjectPropSet m_blob;
public:
  ObjectDeclarationWithRefCountFNDX(FNCR_STP_FORMAT stpFormat,
                                    FNCR_CB_FORMAT cbFormat);
  ObjectDeclarationWithRefCountFNDX(quint8 stpFormat, quint8 cbFormat);
  ~ObjectDeclarationWithRefCountFNDX();



  FileNodeChunkReference getObjectRef() const;
  void setObjectRef(const FileNodeChunkReference &value);

  ObjectDeclarationWithRefCountBody getBody() const;
  void setBody(const ObjectDeclarationWithRefCountBody &value);

  quint8 getCRef() const;
  void setCRef(const quint8 &value);

  ObjectSpaceObjectPropSet getPropSet() const;
  void setPropSet(const ObjectSpaceObjectPropSet &value);

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;

  // IFileNodeType interface
public:
  virtual void generateXml(QXmlStreamWriter& xmlWriter) const override;
};

#endif // OBJECTDECLARATIONWITHREFCOUNTFNDX_H
