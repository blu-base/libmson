#ifndef OBJECTDECLARATIONWITHREFCOUNTFNDX_H
#define OBJECTDECLARATIONWITHREFCOUNTFNDX_H

#include <QtCore/qglobal.h>

#include "../../commonTypes/FileNodeChunkReference.h"
#include "../../objectTypes/ObjectDeclarationWithRefCountBody.h"
#include "../../objectTypes/ObjectSpaceObjectPropSet.h"

#include "IFileNodeType.h"

namespace libmson{
namespace priv{

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
  virtual ~ObjectDeclarationWithRefCountFNDX() = default;

  FileNodeChunkReference getObjectRef() const;
  void setObjectRef(const FileNodeChunkReference &value);

  ObjectDeclarationWithRefCountBody getBody() const;
  void setBody(const ObjectDeclarationWithRefCountBody &value);

  quint8 getCRef() const;
  void setCRef(const quint8 &value);

  ObjectSpaceObjectPropSet getPropSet() const;
  void setPropSet(const ObjectSpaceObjectPropSet &value);


  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;




};

} //namespace priv
} // namespace libmson

#endif // OBJECTDECLARATIONWITHREFCOUNTFNDX_H
