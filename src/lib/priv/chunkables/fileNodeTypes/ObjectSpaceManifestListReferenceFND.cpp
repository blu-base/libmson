#include "ObjectSpaceManifestListReferenceFND.h"

#include "../FileNode.h"

namespace libmson {
namespace priv {

ObjectSpaceManifestListReferenceFND::ObjectSpaceManifestListReferenceFND(
    FileNode_WPtr_t parentFileNode)
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
  return m_parent.lock()->getFileNodeChunkReferenceSize() +
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

FileNodeListFragment_WPtr_t ObjectSpaceManifestListReferenceFND::getRef() const
{
  return m_ref;
}

void ObjectSpaceManifestListReferenceFND::setRef(
    const FileNodeListFragment_WPtr_t value)
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
