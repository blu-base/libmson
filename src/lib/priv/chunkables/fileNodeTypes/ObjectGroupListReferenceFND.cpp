#include "ObjectGroupListReferenceFND.h"

#include "../FileNode.h"

namespace libmson {
namespace priv {

ObjectGroupListReferenceFND::ObjectGroupListReferenceFND(
    FileNode_WPtr_t parentFileNode)
    : IFileNodeType(parentFileNode)
{
}


ExtendedGUID ObjectGroupListReferenceFND::getObjectGroupID() const
{
  return m_ObjectGroupID;
}

void ObjectGroupListReferenceFND::setObjectGroupID(
    const ExtendedGUID& objectGroupID)
{
  m_ObjectGroupID = objectGroupID;
}

quint64 ObjectGroupListReferenceFND::getSizeInFile() const
{
  return m_parent.lock()->getFileNodeChunkReferenceSize() +
         ExtendedGUID::getSizeInFile();
}

FileNodeListFragment_WPtr_t ObjectGroupListReferenceFND::getRef() const
{
  return m_ref;
}

void ObjectGroupListReferenceFND::setRef(const FileNodeListFragment_WPtr_t& ref)
{
  m_ref = ref;
}

// void ObjectGroupListReferenceFND::deserialize(QDataStream &ds) {
//  ds >> m_ref;
//  ds >> m_ObjectGroupID;
//}

// void ObjectGroupListReferenceFND::serialize(QDataStream &ds) const {
//  ds << m_ref;
//  ds << m_ObjectGroupID;
//}

// void ObjectGroupListReferenceFND::toDebugString(QDebug &dbg) const {
//  dbg << " ObjectGroupListReferenceFND:\n"
//      << " ref:           " << m_ref << '\n'
//      << " ObjectGroupID: " << m_ObjectGroupID << '\n';
//}

// void ObjectGroupListReferenceFND::writeLowLevelXml(
//    QXmlStreamWriter &xmlWriter) const {
//  xmlWriter.writeStartElement("ObjectGroupListReferenceFND");

//  xmlWriter << m_ref;

//  xmlWriter << m_ObjectGroupID;

//  xmlWriter.writeEndElement();
//}

} // namespace priv
} // namespace libmson
