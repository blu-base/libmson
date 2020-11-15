#ifndef OBJECTDECLARATIONWITHREFCOUNT2FNDX_H
#define OBJECTDECLARATIONWITHREFCOUNT2FNDX_H

#include <QtCore/qglobal.h>

#include "../Chunkable.h"
#include "../ObjectSpaceObjectPropSet.h"
#include "../objectTypes/ObjectDeclarationWithRefCountBody.h"
#include "IFileNodeType.h"

namespace libmson {
namespace priv {

class ObjectDeclarationWithRefCount2FNDX : public IFileNodeType {
private:
  ObjectSpaceObjectPropSet_WPtr_t m_objectRef;
  ObjectDeclarationWithRefCountBody m_body;
  quint32 m_cRef;

public:
  ObjectDeclarationWithRefCount2FNDX(FileNode_WPtr_t parentFileNode);
  virtual ~ObjectDeclarationWithRefCount2FNDX() = default;

  ObjectSpaceObjectPropSet_WPtr_t getObjectRef() const;
  void setObjectRef(const ObjectSpaceObjectPropSet_WPtr_t& value);

  ObjectDeclarationWithRefCountBody getBody() const;
  void setBody(const ObjectDeclarationWithRefCountBody& value);

  quint32 getCRef() const;
  void setCRef(const quint32& value);

  virtual quint64 getSizeInFile() const override;

  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTDECLARATIONWITHREFCOUNT2FNDX_H
