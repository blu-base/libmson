#include "ObjectDeclarationWithRefCountFNDX.h"

#include "../../utils/Helper.h"
#include "../FileNode.h"

namespace libmson {
namespace priv {

ObjectDeclarationWithRefCountFNDX::ObjectDeclarationWithRefCountFNDX(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode)), m_cRef{}
{
}


ObjectSpaceObjectPropSet_WPtr_t
ObjectDeclarationWithRefCountFNDX::getObjectRef() const
{
  return m_objectRef;
}

void ObjectDeclarationWithRefCountFNDX::setObjectRef(
    const ObjectSpaceObjectPropSet_SPtr_t& value)
{
  m_objectRef = value;
}

ObjectDeclarationWithRefCountBody
ObjectDeclarationWithRefCountFNDX::getBody() const
{
  return m_body;
}

void ObjectDeclarationWithRefCountFNDX::setBody(
    const ObjectDeclarationWithRefCountBody& value)
{
  m_body = value;
}

quint8 ObjectDeclarationWithRefCountFNDX::getCRef() const { return m_cRef; }

void ObjectDeclarationWithRefCountFNDX::setCRef(const quint8& value)
{
  m_cRef = value;
}

quint64 ObjectDeclarationWithRefCountFNDX::getSizeInFile() const
{
  return m_parent.lock()->getFileNodeChunkReferenceSize() +
         m_body.getSizeInFile() + sizeof(m_cRef);
}


} // namespace priv
} // namespace libmson
