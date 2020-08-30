#include "ObjectGroupList.h"
#include "commonTypes/Enums.h"

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

  FileNodeListFragment fragment(m_ref);

  ds.device()->seek(m_ref.stp());
  ds >> fragment;

  m_fileNodeListFragments.push_back(fragment);

  for (const auto &entry : fragment.rgFileNodes()) {
    if (entry.getFileNodeID() !=
            static_cast<quint16>(FileNodeTypeID::ChunkTerminatorFND) &&
        entry.getFileNodeID() != 0) {
      m_fileNodeSequence.push_back(entry);
    }
  }
  //  std::copy_if(fragment->rgFileNodes().begin(),
  //  fragment->rgFileNodes().end(),
  //               back_inserter(m_fileNodeSequence), [](FileNode *entry) {
  //                 return entry->getFileNodeID() !=
  //                        static_cast<quint16>(
  //                            FileNodeTypeID::ChunkTerminatorFND);
  //               });

  FileChunkReference64x32 nextFragmentRef = fragment.nextFragment();

  while (!nextFragmentRef.is_fcrNil() && !nextFragmentRef.is_fcrZero()) {
    FileNodeListFragment nextFragment(nextFragmentRef);

    ds.device()->seek(nextFragmentRef.stp());
    ds >> nextFragment;

    nextFragmentRef = nextFragment.nextFragment();
    m_fileNodeListFragments.push_back(nextFragment);

    auto RgFileNodes = nextFragment.rgFileNodes();
    copy_if(RgFileNodes.begin(), RgFileNodes.end(),
            back_inserter(m_fileNodeSequence), [](FileNode entry) {
              return entry.getFileNodeID() !=
                     static_cast<quint16>(FileNodeTypeID::ChunkTerminatorFND);
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
