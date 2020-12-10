#include "ReadOnlyObjectDeclaration2LargeRefCountFND.h"

#include "../FileNode.h"

namespace libmson {
namespace priv {


ReadOnlyObjectDeclaration2LargeRefCountFND::
    ReadOnlyObjectDeclaration2LargeRefCountFND(FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode)), m_cRef()
{
}


QByteArray ReadOnlyObjectDeclaration2LargeRefCountFND::getMd5hash() const
{
  return m_md5hash;
}

void ReadOnlyObjectDeclaration2LargeRefCountFND::setMd5hash(
    const QByteArray& value)
{
  m_md5hash = value;
}

quint64 ReadOnlyObjectDeclaration2LargeRefCountFND::getSizeInFile() const
{
  return md5HashSize + m_parent.lock()->getFileNodeChunkReferenceSize() +
         ObjectDeclaration2Body::getSizeInFile() + 4;
}

ObjectSpaceObjectPropSet_WPtr_t
ReadOnlyObjectDeclaration2LargeRefCountFND::getBlobRef()
{
  return m_blobRef;
}

void ReadOnlyObjectDeclaration2LargeRefCountFND::setBlobRef(
    const ObjectSpaceObjectPropSet_SPtr_t& blobRef)
{
  m_blobRef = blobRef;
}

ObjectDeclaration2Body
ReadOnlyObjectDeclaration2LargeRefCountFND::getBody() const
{
  return m_body;
}

void ReadOnlyObjectDeclaration2LargeRefCountFND::setBody(
    const ObjectDeclaration2Body& body)
{
  m_body = body;
}

quint32 ReadOnlyObjectDeclaration2LargeRefCountFND::getCRef() const
{
  return m_cRef;
}

void ReadOnlyObjectDeclaration2LargeRefCountFND::setCRef(const quint32& cRef)
{
  m_cRef = cRef;
}

} // namespace priv
} // namespace libmson
