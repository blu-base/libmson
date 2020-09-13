#ifndef REVISIONMANIFEST_H
#define REVISIONMANIFEST_H

#include <QtCore/qglobal.h>
#include <vector>

#include "FileNode.h"

#include "IRevisionStoreFileToXmlable.h"

namespace MSONcommon {
class RevisionManifest : public IRevisionStoreFileToXmlable {
private:
  std::vector<std::shared_ptr<FileNode>> m_FileNodeSquence;

public:
  RevisionManifest() = default;
  ~RevisionManifest() = default;

  std::vector<std::shared_ptr<FileNode>> &fileNodeSquence();
  std::vector<std::shared_ptr<FileNode>> getFileNodeSquence() const;
  void setFileNodeSquence(const std::vector<std::shared_ptr<FileNode>> &value);

  friend QDebug operator<<(QDebug dbg, const RevisionManifest &obj);

private:
 virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;
  /**
   * @brief prints the RevisionManifest to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  void toDebugString(QDebug dbg) const;
};
} // namespace MSONcommon
#endif // REVISIONMANIFEST_H
