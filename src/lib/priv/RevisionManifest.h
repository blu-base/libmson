#ifndef REVISIONMANIFEST_H
#define REVISIONMANIFEST_H

#include <QtCore/qglobal.h>
#include <memory>
#include <vector>

#include "chunkables/FileNode.h"

class RevisionManifestList;

namespace libmson {
namespace priv {

class RevisionManifest {
private:
  std::weak_ptr<RevisionManifestList> m_parent;
  std::vector<FileNode_WPtr_t> m_FileNodeSequence;

public:
  RevisionManifest(std::shared_ptr<RevisionManifestList> parent);

  std::weak_ptr<RevisionManifestList> getParent() const;

  std::vector<FileNode_WPtr_t> getFileNodeSequence() const;
  void
  setFileNodeSequence(const std::vector<FileNode_WPtr_t>& FileNodeSequence);
};

} // namespace priv
} // namespace libmson

#endif // REVISIONMANIFEST_H
