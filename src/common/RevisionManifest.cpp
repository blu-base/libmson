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

void RevisionManifest::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("RevisionManifest");

  //  xmlWriter.writeStartElement("FileNodeSquence");
  for (const auto &entry : m_FileNodeSquence) {
    entry->generateXml(xmlWriter);
  }
  //  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();
}

QDebug operator<<(QDebug dbg, const RevisionManifest &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

void RevisionManifest::toDebugString(QDebug dbg) const {}

} // namespace MSONcommon
