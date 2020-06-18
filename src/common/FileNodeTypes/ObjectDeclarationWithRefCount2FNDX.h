#ifndef OBJECTDECLARATIONWITHREFCOUNT2FNDX_H
#define OBJECTDECLARATIONWITHREFCOUNT2FNDX_H

#include <QtCore/qglobal.h>

#include "../commonTypes/FileNodeChunkReference.h"
#include "../otherTypes/ObjectDeclarationWithRefCountBody.h"
#include "IFileNodeType.h"

class ObjectDeclarationWithRefCount2FNDX : public IFileNodeType {
public:
  ObjectDeclarationWithRefCount2FNDX(FNCR_STP_FORMAT stpFormat,
                                     FNCR_CB_FORMAT cbFormat);
  ObjectDeclarationWithRefCount2FNDX(quint8 stpFormat, quint8 cbFormat);
  ~ObjectDeclarationWithRefCount2FNDX();

  FileNodeChunkReference objectRef;

  ObjectDeclarationWithRefCountBody body;

  quint32 cRef;

  FileNodeChunkReference getObjectRef() const;
  void setObjectRef(const FileNodeChunkReference &value);

  ObjectDeclarationWithRefCountBody getBody() const;
  void setBody(const ObjectDeclarationWithRefCountBody &value);

  quint32 getCRef() const;
  void setCRef(const quint32 &value);

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // OBJECTDECLARATIONWITHREFCOUNT2FNDX_H
