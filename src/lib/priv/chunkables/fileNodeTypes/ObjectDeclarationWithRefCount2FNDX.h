#ifndef OBJECTDECLARATIONWITHREFCOUNT2FNDX_H
#define OBJECTDECLARATIONWITHREFCOUNT2FNDX_H

#include <QtCore/qglobal.h>

#include "../ObjectSpaceObjectPropSet.h"
#include "../objectTypes/ObjectDeclarationWithRefCountBody.h"
#include "IFileNodeType.h"

namespace libmson {
namespace priv {

class ObjectDeclarationWithRefCount2FNDX : public IFileNodeType {
private:
  RSChunkContainer_WPtr_t m_objectRef;
  ObjectDeclarationWithRefCountBody m_body;
  quint32 m_cRef;

  ObjectSpaceObjectPropSet m_blob;

public:
  ObjectDeclarationWithRefCount2FNDX(RSChunkContainer_WPtr_t parentFileNode);
  virtual ~ObjectDeclarationWithRefCount2FNDX() = default;

  RSChunkContainer_WPtr_t getObjectRef() const;
  void setObjectRef(const RSChunkContainer_WPtr_t& value);

  ObjectDeclarationWithRefCountBody getBody() const;
  void setBody(const ObjectDeclarationWithRefCountBody& value);

  quint32 getCRef() const;
  void setCRef(const quint32& value);

  std::shared_ptr<ObjectSpaceObjectPropSet> getPropSet() const;

  virtual quint64 getSizeInFile() const override;

  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;

  // private:
  //  virtual void deserialize(QDataStream& ds) override;
  //  virtual void serialize(QDataStream& ds) const override;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTDECLARATIONWITHREFCOUNT2FNDX_H
