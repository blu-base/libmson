#include "ObjectGroupList.h"
#include "commonTypes/Enums.h"

#include "helper/Helper.h"

namespace MSONcommon {
ObjectGroupList::ObjectGroupList(const FileNodeChunkReference &ref)
    : m_ref{ref} {}

std::vector<std::shared_ptr<FileNodeListFragment>>
ObjectGroupList::getFileNodeListFragments() {
  return m_fileNodeListFragments;
}

void ObjectGroupList::setFileNodeListFragments(
    const std::vector<std::shared_ptr<FileNodeListFragment>> &value) {
  m_fileNodeListFragments = value;
}

FileNodeChunkReference ObjectGroupList::getRef() const { return m_ref; }

void ObjectGroupList::setRef(const FileNodeChunkReference &ref) { m_ref = ref; }

void ObjectGroupList::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ObjectGroupList");
  xmlWriter.writeAttribute("stp", qStringHex(m_ref.stp(), 16));
  xmlWriter.writeAttribute("cb", qStringHex(m_ref.cb(), 16));
  //  xmlWriter.writeStartElement("ref");
  //  xmlWriter << m_ref;
  //  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fileNodeSequence");
  for (const auto &entry : m_fileNodeSequence) {
    xmlWriter << *entry;
  }
  xmlWriter.writeEndElement();

  //    xmlWriter.writeStartElement("fileNodeListFragments");
  //    for(const auto& entry : m_fileNodeListFragments) {
  //        xmlWriter << entry;
  //    }
  //    xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();
}

QDebug operator<<(QDebug dbg, const ObjectGroupList &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

void ObjectGroupList::deserialize(QDataStream &ds) {

  m_fileNodeListFragments = parseFileNodeListFragments(ds, m_ref);

  for (const auto &fragment : m_fileNodeListFragments) {
    const auto &rgFileNodes = fragment->rgFileNodes();
    copy_if(rgFileNodes.begin(), rgFileNodes.end(),
            back_inserter(m_fileNodeSequence),
            [](const std::shared_ptr<FileNode> &entry) {
              return entry->getFileNodeTypeID() !=
                     FileNodeTypeID::ChunkTerminatorFND;
            });
  }
}

void MSONcommon::ObjectGroupList::serialize(QDataStream &ds) const {}

void ObjectGroupList::toDebugString(QDebug dbg) const {}

std::vector<std::shared_ptr<FileNode>>
ObjectGroupList::getFileNodeSequence() const {
  return m_fileNodeSequence;
}

void ObjectGroupList::setFileNodeSequence(
    const std::vector<std::shared_ptr<FileNode>> &value) {
  m_fileNodeSequence = value;
}
} // namespace MSONcommon
