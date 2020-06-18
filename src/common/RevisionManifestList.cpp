#include "RevisionManifestList.h"

FileNodeChunkReference RevisionManifestList::getRef() const { return mRef; }

void RevisionManifestList::setRef(const FileNodeChunkReference &ref) {
  mRef = ref;
}

RevisionManifestList::RevisionManifestList(FileNodeChunkReference ref)
    : mRef{ref} {}

std::vector<FileNode *> RevisionManifestList::getFileNodeSequence() const {
  return mFileNodeSequence;
}

void RevisionManifestList::setFileNodeSequence(
    const std::vector<FileNode *> &value) {
  mFileNodeSequence = value;
}

std::vector<ObjectGroupList *>
RevisionManifestList::getObjectGroupLists() const {
  return mObjectGroupLists;
}

void RevisionManifestList::setObjectGroupLists(
    const std::vector<ObjectGroupList *> &value) {
  mObjectGroupLists = value;
}

std::vector<FileNode *>
RevisionManifestList::getRevisionRoleAndContextDeclarations() const {
  return mRevisionRoleAndContextDeclarations;
}

void RevisionManifestList::setRevisionRoleAndContextDeclarations(
    const std::vector<FileNode *> &value) {
  mRevisionRoleAndContextDeclarations = value;
}

std::vector<FileNode *>
RevisionManifestList::getRevisionRoleDeclarations() const {
  return mRevisionRoleDeclarations;
}

void RevisionManifestList::setRevisionRoleDeclarations(
    const std::vector<FileNode *> &value) {
  mRevisionRoleDeclarations = value;
}

std::vector<RevisionManifest *>
RevisionManifestList::getRevisionManifests() const {
  return mRevisionManifests;
}

void RevisionManifestList::setRevisionManifests(
    const std::vector<RevisionManifest *> &value) {
  mRevisionManifests = value;
}

std::vector<FileNodeListFragment *>
RevisionManifestList::getFileNodeListFragments() const {
  return mFileNodeListFragments;
}

void RevisionManifestList::setFileNodeListFragments(
    const std::vector<FileNodeListFragment *> &value) {
  mFileNodeListFragments = value;
}
