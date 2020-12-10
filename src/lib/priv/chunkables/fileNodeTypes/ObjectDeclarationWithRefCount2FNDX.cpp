#include "ObjectDeclarationWithRefCount2FNDX.h"

#include "../../utils/Helper.h"
#include "../FileNode.h"

namespace libmson {
namespace priv {

ObjectDeclarationWithRefCount2FNDX::ObjectDeclarationWithRefCount2FNDX(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode)), m_cRef()
{
}

ObjectSpaceObjectPropSet_WPtr_t
ObjectDeclarationWithRefCount2FNDX::getObjectRef() const
{
  return m_objectRef;
}

void ObjectDeclarationWithRefCount2FNDX::setObjectRef(
    const ObjectSpaceObjectPropSet_SPtr_t& value)
{
  m_objectRef = value;
}

ObjectDeclarationWithRefCountBody
ObjectDeclarationWithRefCount2FNDX::getBody() const
{
  return m_body;
}

void ObjectDeclarationWithRefCount2FNDX::setBody(
    const ObjectDeclarationWithRefCountBody& value)
{
  m_body = value;
}

quint32 ObjectDeclarationWithRefCount2FNDX::getCRef() const { return m_cRef; }

void ObjectDeclarationWithRefCount2FNDX::setCRef(const quint32& value)
{
  m_cRef = value;
}

quint64 ObjectDeclarationWithRefCount2FNDX::getSizeInFile() const
{
  return m_parent.lock()->getFileNodeChunkReferenceSize() +
         m_body.getSizeInFile() + sizeof(m_cRef);
}

} // namespace priv
} // namespace libmson
