#include "RevisionManifest.h"
namespace MSONcommon {
std::vector<std::shared_ptr<FileNode>> &RevisionManifest::fileNodeSquence() {
  return m_FileNodeSquence;
}
std::vector<std::shared_ptr<FileNode>>
RevisionManifest::getFileNodeSquence() const {
  return m_FileNodeSquence;
}

void RevisionManifest::setFileNodeSquence(
    const std::vector<std::shared_ptr<FileNode>> &value) {
  m_FileNodeSquence = value;
}

void RevisionManifest::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("RevisionManifest");

  //  xmlWriter.writeStartElement("FileNodeSquence");
  for (const auto &entry : m_FileNodeSquence) {
    xmlWriter << *entry;
  }
  //  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();
}

void RevisionManifest::serialize(QDataStream &ds) const {}
void RevisionManifest::deserialize(QDataStream &ds) {}

void RevisionManifest::toDebugString(QDebug &dbg) const {}

} // namespace MSONcommon
