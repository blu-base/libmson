#ifndef OBJECTGROUPLIST_H
#define OBJECTGROUPLIST_H

#include <QtCore/qglobal.h>
#include <vector>

#include <QDataStream>
#include <QDebug>

#include "FileNode.h"
#include "FileNodeListFragment.h"

class ObjectGroupList {
private:
  std::vector<FileNode *> m_fileNodeSequence;

  std::vector<FileNodeListFragment *> m_fileNodeListFragments;

public:
  ObjectGroupList();

  std::vector<FileNode *> getFileNodeSequence() const;
  void setFileNodeSequence(const std::vector<FileNode *> &value);

  std::vector<FileNodeListFragment *> getFileNodeListFragments();

  void
  setFileNodeListFragments(const std::vector<FileNodeListFragment *> &value);
};

#endif // OBJECTGROUPLIST_H
