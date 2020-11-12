#include "ObjectDeclaration2LargeRefCountFND.h"

#include "../../utils/Helper.h"
#include "../FileNode.h"

namespace libmson {
namespace priv {
ObjectDeclaration2LargeRefCountFND::ObjectDeclaration2LargeRefCountFND(
    RSChunkContainer_WPtr_t parentFileNode)
    : IFileNodeType(parentFileNode)
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

std::shared_ptr<ObjectSpaceObjectPropSet>
ObjectDeclaration2LargeRefCountFND::getPropSet()
{
  return std::static_pointer_cast<ObjectSpaceObjectPropSet>(
      m_blobRef.lock()->getContent());
}

quint64 ObjectDeclaration2LargeRefCountFND::getSizeInFile() const
{
  return std::static_pointer_cast<FileNode>(m_parent.lock()->getContent())
             ->getFileNodeChunkReferenceSize() +
         ObjectDeclaration2Body::getSizeInFile() + 4;
}

RSChunkContainer_WPtr_t ObjectDeclaration2LargeRefCountFND::getBlobRef() const
{
  return m_blobRef;
}

void ObjectDeclaration2LargeRefCountFND::setBlobRef(
    const RSChunkContainer_WPtr_t& blobRef)
{
  m_blobRef = blobRef;
}

// void ObjectDeclaration2LargeRefCountFND::serialize(QDataStream& ds) const
//{
//  ds << m_blobRef;
//  ds << m_body;
//  ds << m_cRef;
//}


} // namespace priv
} // namespace libmson
