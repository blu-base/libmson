#ifndef REVISIONMANIFESTLIST_H
#define REVISIONMANIFESTLIST_H

#include <QtCore/qglobal.h>

#include "FileNode.h"
#include "FileNodeListFragment.h"
#include "ObjectGroupList.h"
#include "RevisionManifest.h"
#include "commonTypes/FileNodeChunkReference.h"

#include <QDataStream>
#include <QDebug>
#include <vector>

class RevisionManifestList {
private:
  FileNodeChunkReference mRef;

  std::vector<FileNodeListFragment *> mFileNodeListFragments;
  std::vector<RevisionManifest *> mRevisionManifests;
  std::vector<FileNode *> mRevisionRoleDeclarations;

  std::vector<FileNode *> mRevisionRoleAndContextDeclarations;

  std::vector<ObjectGroupList *> mObjectGroupLists;

  std::vector<FileNode *> mFileNodeSequence;

public:
  RevisionManifestList(FileNodeChunkReference ref);
  ~RevisionManifestList();

  std::vector<FileNodeListFragment *> getFileNodeListFragments() const;
  void
  setFileNodeListFragments(const std::vector<FileNodeListFragment *> &value);
  std::vector<RevisionManifest *> getRevisionManifests() const;
  void setRevisionManifests(const std::vector<RevisionManifest *> &value);
  std::vector<FileNode *> getRevisionRoleDeclarations() const;
  void setRevisionRoleDeclarations(const std::vector<FileNode *> &value);
  std::vector<FileNode *> getRevisionRoleAndContextDeclarations() const;
  void
  setRevisionRoleAndContextDeclarations(const std::vector<FileNode *> &value);
  std::vector<ObjectGroupList *> getObjectGroupLists() const;
  void setObjectGroupLists(const std::vector<ObjectGroupList *> &value);
  std::vector<FileNode *> getFileNodeSequence() const;
  void setFileNodeSequence(const std::vector<FileNode *> &value);
  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &ref);
};

#endif // REVISIONMANIFESTLIST_H
