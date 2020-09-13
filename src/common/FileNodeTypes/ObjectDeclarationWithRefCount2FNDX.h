#ifndef OBJECTDECLARATIONWITHREFCOUNT2FNDX_H
#define OBJECTDECLARATIONWITHREFCOUNT2FNDX_H

#include <QtCore/qglobal.h>

#include "../commonTypes/FileNodeChunkReference.h"
#include "../otherTypes/ObjectDeclarationWithRefCountBody.h"
#include "../otherTypes/ObjectSpaceObjectPropSet.h"
#include "IFileNodeType.h"

namespace MSONcommon {

class ObjectDeclarationWithRefCount2FNDX : public IFileNodeType {
private:
  FileNodeChunkReference m_objectRef;
  ObjectDeclarationWithRefCountBody m_body;
  quint32 m_cRef;

  ObjectSpaceObjectPropSet m_blob;

public:
  ObjectDeclarationWithRefCount2FNDX(FNCR_STP_FORMAT stpFormat,
                                     FNCR_CB_FORMAT cbFormat);
  ObjectDeclarationWithRefCount2FNDX(quint8 stpFormat, quint8 cbFormat);
  virtual ~ObjectDeclarationWithRefCount2FNDX() = default;

  FileNodeChunkReference getObjectRef() const;
  void setObjectRef(const FileNodeChunkReference &value);

  ObjectDeclarationWithRefCountBody getBody() const;
  void setBody(const ObjectDeclarationWithRefCountBody &value);

  quint32 getCRef() const;
  void setCRef(const quint32 &value);

  ObjectSpaceObjectPropSet getPropSet() const;
  void setPropSet(const ObjectSpaceObjectPropSet &value);

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;
};

} // namespace MSONcommon

#endif // OBJECTDECLARATIONWITHREFCOUNT2FNDX_H
