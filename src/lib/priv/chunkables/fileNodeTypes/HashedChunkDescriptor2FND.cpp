#include "HashedChunkDescriptor2FND.h"

#include "../FileNode.h"

namespace libmson {
namespace priv {
HashedChunkDescriptor2FND::HashedChunkDescriptor2FND(
    RSChunkContainer_WPtr_t parentFileNode)
    : IFileNodeType(parentFileNode)
{
}


RSChunkContainer_WPtr_t HashedChunkDescriptor2FND::BlobRef() const
{
  return m_blobRef;
}

void HashedChunkDescriptor2FND::setBlobRef(
    const RSChunkContainer_WPtr_t BlobRef)
{
  m_blobRef = BlobRef;
}

QByteArray HashedChunkDescriptor2FND::guidHash() const { return m_guidHash; }

void HashedChunkDescriptor2FND::setGuidHash(const QByteArray& guidHash)
{
  m_guidHash = guidHash;
}

std::shared_ptr<ObjectSpaceObjectPropSet>
HashedChunkDescriptor2FND::getPropSet()
{
  return std::static_pointer_cast<ObjectSpaceObjectPropSet>(
      m_blobRef.lock()->getContent());
}

// void HashedChunkDescriptor2FND::deserialize(QDataStream &ds) {
//  ds >> m_BlobRef;

//  m_guidHash = ds.device()->read(guidHashWidth);

//  m_blob = ObjectSpaceObjectPropSet(ds, m_BlobRef);
//}

// void HashedChunkDescriptor2FND::serialize(QDataStream &ds) const {
//  ds << m_BlobRef;
//  ds << m_guidHash;
//}

// void HashedChunkDescriptor2FND::toDebugString(QDebug &dbg) const {
//  dbg << " HashedChunkDescriptor2FND\n"
//      << " m_BlobRef:" << m_BlobRef << '\n'
//      << " m_guidHash: " << m_guidHash.toHex() << '\n';
//}

// void HashedChunkDescriptor2FND::writeLowLevelXml(QXmlStreamWriter &xmlWriter)
// const {
//  xmlWriter.writeStartElement("HashedChunkDescriptor2FND");

//  xmlWriter << m_BlobRef;

//  xmlWriter.writeStartElement("guidHash");
//  xmlWriter.writeCharacters(m_guidHash.toHex());
//  xmlWriter.writeEndElement();

//  xmlWriter << m_blob;

//  xmlWriter.writeEndElement();
//}

quint64 HashedChunkDescriptor2FND::getSizeInFile() const
{
  return std::static_pointer_cast<FileNode>(m_parent.lock()->getContent())
             ->getFileNodeChunkReferenceSize() +
         guidHashWidth;
}

} // namespace priv
} // namespace libmson
