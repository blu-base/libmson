#ifndef OBJECTDECLARATION2LARGEREFCOUNTFND_H
#define OBJECTDECLARATION2LARGEREFCOUNTFND_H

#include "../commonTypes/FileNodeChunkReference.h"
#include "../otherTypes/ObjectDeclaration2Body.h"
#include "../otherTypes/ObjectSpaceObjectPropSet.h"
#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace MSONcommon {

class ObjectDeclaration2LargeRefCountFND : public IFileNodeType {
private:
  FileNodeChunkReference m_blobRef;
  ObjectDeclaration2Body m_body;
  quint32 m_cRef;

  ObjectSpaceObjectPropSet m_blob;

public:
  ObjectDeclaration2LargeRefCountFND(FNCR_STP_FORMAT stpFormat,
                                     FNCR_CB_FORMAT cbFormat);

  ObjectDeclaration2LargeRefCountFND(quint8 stpFormat, quint8 cbFormat);
  virtual ~ObjectDeclaration2LargeRefCountFND() = default;

  FileNodeChunkReference blobRef() const;
  void setBlobRef(const FileNodeChunkReference &blobRef);

  ObjectDeclaration2Body body() const;
  void setBody(const ObjectDeclaration2Body &body);

  quint32 cRef() const;
  void setCRef(const quint32 &cRef);

  ObjectSpaceObjectPropSet getPropSet() const;
  void setPropSet(const ObjectSpaceObjectPropSet &value);

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // OBJECTDECLARATION2LARGEREFCOUNTFND_H
