#include "ObjectDeclaration2LargeRefCountFND.h"

#include "../FileNode.h"

namespace libmson {
namespace priv {
ObjectDeclaration2LargeRefCountFND::ObjectDeclaration2LargeRefCountFND(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode)), m_cRef(0)
{
}

ObjectDeclaration2Body ObjectDeclaration2LargeRefCountFND::getBody() const
{
  return m_body;
}

void ObjectDeclaration2LargeRefCountFND::setBody(
    const ObjectDeclaration2Body& body)
{
  m_body = body;
}

quint32 ObjectDeclaration2LargeRefCountFND::getCRef() const { return m_cRef; }

void ObjectDeclaration2LargeRefCountFND::setCRef(const quint32& cRef)
{
  m_cRef = cRef;
}

quint64 ObjectDeclaration2LargeRefCountFND::getSizeInFile() const
{
  return m_parent.lock()->getFileNodeChunkReferenceSize() +
         ObjectDeclaration2Body::getSizeInFile() + 4;
}

ObjectSpaceObjectPropSet_WPtr_t ObjectDeclaration2LargeRefCountFND::getBlobRef()
{
  return m_blobRef;
}

void ObjectDeclaration2LargeRefCountFND::setBlobRef(
    const ObjectSpaceObjectPropSet_SPtr_t& blobRef)
{
  m_blobRef = blobRef;
}

} // namespace priv
} // namespace libmson
