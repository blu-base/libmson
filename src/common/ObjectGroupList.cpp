#include "ObjectGroupList.h"

ObjectGroupList::ObjectGroupList() {}

std::vector<FileNodeListFragment *>
ObjectGroupList::getFileNodeListFragments() {
  return m_fileNodeListFragments;
}

void ObjectGroupList::setFileNodeListFragments(
    const std::vector<FileNodeListFragment *> &value) {
  m_fileNodeListFragments = value;
}

std::vector<FileNode *> ObjectGroupList::getFileNodeSequence() const {
  return m_fileNodeSequence;
}

void ObjectGroupList::setFileNodeSequence(
    const std::vector<FileNode *> &value) {
  m_fileNodeSequence = value;
}
