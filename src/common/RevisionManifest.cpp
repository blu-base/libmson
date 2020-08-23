#include "RevisionManifest.h"
namespace MSONcommon {
std::vector<FileNode> &RevisionManifest::getFileNodeSquence()  {
  return m_FileNodeSquence;
}

void RevisionManifest::setFileNodeSquence(
    const std::vector<FileNode> &value) {
    m_FileNodeSquence = value;
}

void RevisionManifest::generateXml(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("RevisionManifest");

    xmlWriter.writeStartElement("FileNodeSquence");
    for(const auto& entry: m_FileNodeSquence) {
        entry.generateXml(xmlWriter);
    }
    xmlWriter.writeEndElement();


    xmlWriter.writeEndElement();
}

QDataStream &operator<<(QDataStream &ds, const RevisionManifest &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, RevisionManifest &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const RevisionManifest &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

void RevisionManifest::deserialize(QDataStream &ds) {
}

void RevisionManifest::serialize(QDataStream &ds) const {}

void RevisionManifest::toDebugString(QDebug dbg) const {}

RevisionManifest::RevisionManifest() : m_FileNodeSquence{} {}

RevisionManifest::~RevisionManifest() {
}
} // namespace MSONcommon
