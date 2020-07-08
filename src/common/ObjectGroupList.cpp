#include "ObjectGroupList.h"
#include "commonTypes/Enums.h"

namespace MSONcommon {
ObjectGroupList::ObjectGroupList(FileNodeChunkReference ref) : m_ref{ref} {}

ObjectGroupList::~ObjectGroupList() {
  for (auto *entry : m_fileNodeSequence) {
    delete entry;
  }

  for (auto *entry : m_fileNodeListFragments) {
    delete entry;
  }
}

std::vector<FileNodeListFragment *>
ObjectGroupList::getFileNodeListFragments() {
  return m_fileNodeListFragments;
}

void ObjectGroupList::setFileNodeListFragments(
    const std::vector<FileNodeListFragment *> &value) {
  m_fileNodeListFragments = value;
}

FileNodeChunkReference ObjectGroupList::getRef() const { return m_ref; }

void ObjectGroupList::setRef(const FileNodeChunkReference &ref) { m_ref = ref; }

QDataStream &operator>>(QDataStream &ds, ObjectGroupList &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const ObjectGroupList &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

void ObjectGroupList::deserialize(QDataStream &ds) {

  FileNodeListFragment *fragment = new FileNodeListFragment(m_ref);

  ds.device()->seek(m_ref.stp());
  ds >> *fragment;

  m_fileNodeListFragments.push_back(fragment);

  for (auto *entry : fragment->rgFileNodes()) {
    if (entry->getFileNodeID() !=
            static_cast<quint16>(FileNodeTypeID::ChunkTerminatorFND) &&
        entry->getFileNodeID() != 0) {
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

  FileChunkReference64x32 nextFragmentRef = fragment->nextFragment();

  while (!nextFragmentRef.is_fcrNil() && !nextFragmentRef.is_fcrZero()) {
    FileNodeListFragment *nextFragment =
        new FileNodeListFragment(nextFragmentRef);

    ds.device()->seek(nextFragmentRef.stp());
    ds >> *nextFragment;

    nextFragmentRef = nextFragment->nextFragment();
    m_fileNodeListFragments.push_back(nextFragment);

    copy_if(nextFragment->rgFileNodes().begin(),
            nextFragment->rgFileNodes().end(),
            back_inserter(m_fileNodeSequence), [](FileNode *entry) {
              return entry->getFileNodeID() !=
                     static_cast<quint16>(FileNodeTypeID::ChunkTerminatorFND);
            });
  }
}

void ObjectGroupList::toDebugString(QDebug dbg) const {}

std::vector<FileNode *> ObjectGroupList::getFileNodeSequence() const {
  return m_fileNodeSequence;
}

void ObjectGroupList::setFileNodeSequence(
    const std::vector<FileNode *> &value) {
  m_fileNodeSequence = value;
}
} // namespace MSONcommon
