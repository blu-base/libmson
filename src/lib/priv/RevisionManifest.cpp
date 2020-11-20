#include "RevisionManifest.h"
namespace libmson {
namespace priv {

RevisionManifest::RevisionManifest(std::shared_ptr<RevisionManifestList> parent)
    : m_parent(parent)
{
}

std::weak_ptr<RevisionManifestList> RevisionManifest::getParent() const
{
  return m_parent;
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
