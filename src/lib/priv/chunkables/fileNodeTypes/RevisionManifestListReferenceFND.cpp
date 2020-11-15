#include "RevisionManifestListReferenceFND.h"

#include "../FileNode.h"

namespace libmson {
namespace priv {

RevisionManifestListReferenceFND::RevisionManifestListReferenceFND(
    FileNode_WPtr_t parentFileNode)
    : IFileNodeType(parentFileNode)
{
}


FileNodeListFragment_WPtr_t RevisionManifestListReferenceFND::getRef() const
{
  return m_ref;
}

void RevisionManifestListReferenceFND::setRef(
    const FileNodeListFragment_WPtr_t value)
{
  m_ref = value;
}

quint64 RevisionManifestListReferenceFND::getSizeInFile() const
{
  return m_parent.lock()->getFileNodeChunkReferenceSize();
}

// void RevisionManifestListReferenceFND::deserialize(QDataStream &ds) {
//  ds >> m_ref;
//}

// void RevisionManifestListReferenceFND::serialize(QDataStream &ds) const {
//  ds << m_ref;
//}

// void RevisionManifestListReferenceFND::toDebugString(QDebug &dbg) const {
//  dbg << " RevisionManifestListReferenceFND:\n"
//      << " ref: " << m_ref << '\n';
//}

// void RevisionManifestListReferenceFND::writeLowLevelXml(
//    QXmlStreamWriter &xmlWriter) const {
//  xmlWriter.writeStartElement("RevisionManifestListReferenceFND");
//  xmlWriter << m_ref;
//  xmlWriter.writeEndElement();
//}

} // namespace priv
} // namespace libmson
