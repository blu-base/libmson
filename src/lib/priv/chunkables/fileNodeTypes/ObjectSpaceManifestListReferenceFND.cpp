#include "ObjectSpaceManifestListReferenceFND.h"

#include "../FileNode.h"

namespace libmson {
namespace priv {

ObjectSpaceManifestListReferenceFND::ObjectSpaceManifestListReferenceFND(
    RSChunkContainer_WPtr_t parentFileNode)
    : IFileNodeType(parentFileNode)
{
}


ExtendedGUID ObjectSpaceManifestListReferenceFND::getGosid() const
{
  return m_gosid;
}

void ObjectSpaceManifestListReferenceFND::setGosid(const ExtendedGUID& value)
{
  m_gosid = value;
}

quint64 ObjectSpaceManifestListReferenceFND::getSizeInFile() const
{
  return std::static_pointer_cast<FileNode>(m_parent.lock()->getContent())
             ->getFileNodeChunkReferenceSize() +
         ExtendedGUID::getSizeInFile();
}

// void ObjectSpaceManifestListReferenceFND::deserialize(QDataStream& ds)
//{
//  ds >> m_ref;
//  ds >> m_gosid;
//}

// void ObjectSpaceManifestListReferenceFND::serialize(QDataStream& ds) const
//{
//  ds << m_ref;
//  ds << m_gosid;
//}

// void ObjectSpaceManifestListReferenceFND::toDebugString(QDebug& dbg) const
//{
//  dbg << " ObjectSpaceManifestListReferenceFND:\n"
//      << " ref:   " << m_ref << '\n'
//      << " gosid: " << m_gosid << '\n';
//}

RSChunkContainer_WPtr_t ObjectSpaceManifestListReferenceFND::getRef() const
{
  return m_ref;
}

void ObjectSpaceManifestListReferenceFND::setRef(
    const RSChunkContainer_WPtr_t value)
{
  m_ref = value;
}

// void ObjectSpaceManifestListReferenceFND::writeLowLevelXml(
//    QXmlStreamWriter &xmlWriter) const {
//  xmlWriter.writeStartElement("ObjectSpaceManifestListReferenceFND");
//  xmlWriter << m_ref;

//  xmlWriter << m_gosid;

//  xmlWriter.writeEndElement();
//}

} // namespace priv
} // namespace libmson
