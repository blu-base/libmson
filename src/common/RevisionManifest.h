#ifndef REVISIONMANIFEST_H
#define REVISIONMANIFEST_H

#include <QtCore/qglobal.h>
#include <vector>

#include "FileNode.h"

#include "IRevisionStoreFileToXmlable.h"

namespace MSONcommon {
class RevisionManifest : public IRevisionStoreFileObject {
private:
  std::vector<std::shared_ptr<FileNode>> m_FileNodeSquence;

public:
  RevisionManifest() = default;
  ~RevisionManifest() = default;

  std::vector<std::shared_ptr<FileNode>> &fileNodeSquence();
  std::vector<std::shared_ptr<FileNode>> getFileNodeSquence() const;
  void setFileNodeSquence(const std::vector<std::shared_ptr<FileNode>> &value);

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;
};
} // namespace MSONcommon
#endif // REVISIONMANIFEST_H
