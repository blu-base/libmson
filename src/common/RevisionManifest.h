#ifndef REVISIONMANIFEST_H
#define REVISIONMANIFEST_H

#include <QtCore/qglobal.h>
#include <vector>

#include "FileNode.h"

class RevisionManifest
{
public:
  std::vector<FileNode*> FileNodeSquence;

  RevisionManifest();
  ~RevisionManifest();

  std::vector<FileNode*> getFileNodeSquence() const;
  void setFileNodeSquence(const std::vector<FileNode*>& value);
};

#endif // REVISIONMANIFEST_H
