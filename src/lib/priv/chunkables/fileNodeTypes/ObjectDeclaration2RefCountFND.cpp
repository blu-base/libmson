#include "ObjectDeclaration2RefCountFND.h"

#include "../../utils/Helper.h"
#include "../FileNode.h"


namespace libmson {
namespace priv {

ObjectDeclaration2RefCountFND::ObjectDeclaration2RefCountFND(
    RSChunkContainer_WPtr_t parentFileNode)
    : IFileNodeType(parentFileNode), m_cRef(0)
{
}

quint8 ObjectDeclaration2RefCountFND::getCRef() const { return m_cRef; }

void ObjectDeclaration2RefCountFND::setCRef(const quint8& value)
{
  m_cRef = value;
}

ObjectDeclaration2Body ObjectDeclaration2RefCountFND::getBody() const
{
  return m_body;
}

void ObjectDeclaration2RefCountFND::setBody(const ObjectDeclaration2Body& value)
{
  m_body = value;
}

std::shared_ptr<ObjectSpaceObjectPropSet>
ObjectDeclaration2RefCountFND::getPropSet()
{
  return std::static_pointer_cast<ObjectSpaceObjectPropSet>(
      m_blobRef.lock()->getContent());
}


RSChunkContainer_WPtr_t ObjectDeclaration2RefCountFND::getBlobRef() const
{
  return m_blobRef;
}

void ObjectDeclaration2RefCountFND::setBlobRef(
    const RSChunkContainer_WPtr_t& value)
{
  m_blobRef = value;
}

quint64 ObjectDeclaration2RefCountFND::getSizeInFile() const
{
  return std::static_pointer_cast<FileNode>(m_parent.lock()->getContent())
             ->getFileNodeChunkReferenceSize() +
         ObjectDeclaration2Body::getSizeInFile() + sizeof(m_cRef);
}

// void ObjectDeclaration2RefCountFND::serialize(QDataStream& ds) const
//{
//  ds << m_blobRef;
//  ds << m_body;
//  ds << m_cRef;
//}

} // namespace priv
} // namespace libmson
