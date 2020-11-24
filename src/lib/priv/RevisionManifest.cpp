#include "RevisionManifest.h"


namespace libmson {
namespace priv {

RevisionManifest::RevisionManifest(RevisionManifestList_SPtr_t parent)
    : m_parent(parent)
{
}

RevisionManifestList_WPtr_t RevisionManifest::getParent() const
{
  return m_parent;
}

std::vector<ObjectGroupList_SPtr_t>
RevisionManifest::getObjectGroupLists() const
{
  return m_ObjectGroupLists;
}

void RevisionManifest::setObjectGroupLists(
    const std::vector<ObjectGroupList_SPtr_t>& ObjectGroupLists)
{
  m_ObjectGroupLists = ObjectGroupLists;
}

std::vector<FileNode_WPtr_t> RevisionManifest::getFileNodeSequence() const
{
  return m_FileNodeSequence;
}

void RevisionManifest::setFileNodeSequence(
    const std::vector<FileNode_WPtr_t>& FileNodeSequence)
{
  m_FileNodeSequence = FileNodeSequence;
}

// void RevisionManifest::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
//  xmlWriter.writeStartElement("RevisionManifest");

//  //  xmlWriter.writeStartElement("FileNodeSquence");
//  for (const auto &entry : m_FileNodeSquence) {
//    xmlWriter << *entry;
//  }
//  //  xmlWriter.writeEndElement();

//  xmlWriter.writeEndElement();
//}


} // namespace priv
} // namespace libmson
