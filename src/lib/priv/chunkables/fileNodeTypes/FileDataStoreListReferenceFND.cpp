#include "FileDataStoreListReferenceFND.h"

#include "../FileNode.h"

namespace libmson {
namespace priv {

FileDataStoreListReferenceFND::FileDataStoreListReferenceFND(
    FileNode_WPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode))
{
}


FileNodeListFragment_WPtr_t FileDataStoreListReferenceFND::getRef() const
{
  return m_ref;
}

void FileDataStoreListReferenceFND::setRef(
    const FileNodeListFragment_WPtr_t value)
{
  m_ref = value;
}

// void FileDataStoreListReferenceFND::deserialize(QDataStream& ds)
//{
//  ds >> m_ref;

//  m_StoreList = FileNodeListFragment(m_ref);
//  ds >> m_StoreList;
//}

// void FileDataStoreListReferenceFND::serialize(QDataStream& ds) const { ds <<
// m_ref; }

// void FileDataStoreListReferenceFND::toDebugString(QDebug& dbg) const
//{
//  dbg << " FileDataStoreObjectReferenceFND:\n"
//      << " ref: " << m_ref << '\n';
//}

// void FileDataStoreListReferenceFND::writeLowLevelXml(QXmlStreamWriter&
// xmlWriter) const
//{
//  xmlWriter.writeStartElement("FileDataStoreListReferenceFND");
//  xmlWriter << m_ref;

//  xmlWriter << m_StoreList;
//  xmlWriter.writeEndElement();
//}

quint64 FileDataStoreListReferenceFND::getSizeInFile() const
{
  return m_parent.lock()->getFileNodeChunkReferenceSize();
}

} // namespace priv
} // namespace libmson
