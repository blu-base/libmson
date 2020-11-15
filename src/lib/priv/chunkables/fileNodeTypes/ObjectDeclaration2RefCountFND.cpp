#include "ObjectDeclaration2RefCountFND.h"

#include "../../utils/Helper.h"
#include "../FileNode.h"


namespace libmson {
namespace priv {

ObjectDeclaration2RefCountFND::ObjectDeclaration2RefCountFND(
    FileNode_WPtr_t parentFileNode)
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


ObjectSpaceObjectPropSet_WPtr_t
ObjectDeclaration2RefCountFND::getBlobRef() const
{
  return m_blobRef;
}

void ObjectDeclaration2RefCountFND::setBlobRef(
    const ObjectSpaceObjectPropSet_WPtr_t& value)
{
  m_blobRef = value;
}

quint64 ObjectDeclaration2RefCountFND::getSizeInFile() const
{
  return m_parent.lock()->getFileNodeChunkReferenceSize() +
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
