#ifndef OBJECTDECLARATION2REFCOUNTFND_H
#define OBJECTDECLARATION2REFCOUNTFND_H

#include <QtCore/qglobal.h>

#include "../commonTypes/FileNodeChunkReference.h"
#include "../otherTypes/ObjectDeclaration2Body.h"
#include "IFileNodeType.h"

class ObjectDeclaration2RefCountFND : public IFileNodeType {
public:
  ObjectDeclaration2RefCountFND(FNCR_STP_FORMAT stpFormat,
                                FNCR_CB_FORMAT cbFormat);
  ObjectDeclaration2RefCountFND(quint8 stpFormat, quint8 cbFormat);
  ~ObjectDeclaration2RefCountFND();

  FileNodeChunkReference blobRef;

  ObjectDeclaration2Body body;

  quint8 cRef;

  FileNodeChunkReference getBlobRef() const;
  void setBlobRef(const FileNodeChunkReference &value);

  ObjectDeclaration2Body getBody() const;
  void setBody(const ObjectDeclaration2Body &value);

  quint8 getCRef() const;
  void setCRef(const quint8 &value);

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // OBJECTDECLARATION2REFCOUNTFND_H
