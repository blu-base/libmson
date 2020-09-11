#include "ObjectGroupList.h"
#include "commonTypes/Enums.h"

#include "helper/Helper.h"

namespace MSONcommon {
ObjectGroupList::ObjectGroupList(FileNodeChunkReference ref) : m_ref{ref} {}

ObjectGroupList::~ObjectGroupList() {
  //  for (auto *entry : m_fileNodeSequence) {
  //    delete entry;
  //  }

  //  for (auto *entry : m_fileNodeListFragments) {
  //    delete entry;
  //  }
}

std::vector<FileNodeListFragment> ObjectGroupList::getFileNodeListFragments() {
  return m_fileNodeListFragments;
}

void ObjectGroupList::setFileNodeListFragments(
    const std::vector<FileNodeListFragment> &value) {
  m_fileNodeListFragments = value;
}

FileNodeChunkReference ObjectGroupList::getRef() const { return m_ref; }

void ObjectGroupList::setRef(const FileNodeChunkReference &ref) { m_ref = ref; }

void ObjectGroupList::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ObjectGroupList");

  xmlWriter.writeStartElement("ref");
  m_ref.generateXml(xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fileNodeSequence");
  for (const auto &entry : m_fileNodeSequence) {
    entry.generateXml(xmlWriter);
  }
  xmlWriter.writeEndElement();

  //    xmlWriter.writeStartElement("fileNodeListFragments");
  //    for(const auto& entry : m_fileNodeListFragments) {
  //        entry.generateXml(xmlWriter);
  //    }
  //    xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();
}

QDataStream &operator>>(QDataStream &ds, ObjectGroupList &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const ObjectGroupList &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

void ObjectGroupList::deserialize(QDataStream &ds) {


    m_fileNodeListFragments =
        parseFileNodeListFragments(ds, m_ref);

    for (const auto &fragment : m_fileNodeListFragments) {
      const auto &rgFileNodes = fragment.rgFileNodes();
      copy_if(rgFileNodes.begin(), rgFileNodes.end(),
              back_inserter(m_fileNodeSequence), [](const FileNode &entry) {
                return entry.getFileNodeTypeID() !=
                       FileNodeTypeID::ChunkTerminatorFND;
              });
    }

}

void ObjectGroupList::toDebugString(QDebug dbg) const {}

std::vector<FileNode> ObjectGroupList::getFileNodeSequence() const {
  return m_fileNodeSequence;
}

void ObjectGroupList::setFileNodeSequence(const std::vector<FileNode> &value) {
  m_fileNodeSequence = value;
}
} // namespace MSONcommon
