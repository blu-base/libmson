#ifndef OBJECTSPACEMANIFESTLIST_H
#define OBJECTSPACEMANIFESTLIST_H

#include <QXmlStreamWriter>
#include <QtCore/qglobal.h>
#include <vector>

#include "IRevisionStoreFileObject.h"

#include "FileNode.h"
#include "FileNodeListFragment.h"
#include "commonTypes/FileNodeChunkReference.h"

#include "RevisionManifestList.h"

namespace MSONcommon {

class ObjectSpaceManifestList : public IRevisionStoreFileObject {
private:
  FileNodeChunkReference m_ref;

  std::vector<std::shared_ptr<FileNodeListFragment>> m_fileNodeListFragments;

  std::shared_ptr<FileNode> m_objectSpaceManifestListStart;

  std::vector<std::shared_ptr<RevisionManifestList>> m_revisionManifestLists;

  std::vector<std::shared_ptr<FileNode>> m_fileNodeSequence;

public:
  ObjectSpaceManifestList(const FileNodeChunkReference &ref);
  ~ObjectSpaceManifestList() = default;

  std::vector<std::shared_ptr<FileNodeListFragment>>
  getFileNodeListFragments() const;
  void setFileNodeListFragments(
      const std::vector<std::shared_ptr<FileNodeListFragment>> &value);

  std::shared_ptr<FileNode> getObjectSpaceManifestListStart() const;
  void setObjectSpaceManifestListStart(const std::shared_ptr<FileNode> &value);

  std::vector<std::shared_ptr<RevisionManifestList>> getRevisionManifestLists();
  void setRevisionManifestLists(
      const std::vector<std::shared_ptr<RevisionManifestList>> &value);

  std::vector<std::shared_ptr<FileNode>> getFileNodeSequence() const;
  void setFileNodeSequence(const std::vector<std::shared_ptr<FileNode>> &value);

  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &ref);

private:
  /**
   * @brief creates ObjectSpaceManifestList from QDataStream
   * @param ds <QDataStream> containing the deserializable
   * ObjectSpaceManifestList
   */
  virtual void deserialize(QDataStream &ds) override;
  /**
   * @brief creates byte stream from ObjectSpaceManifestList object
   * @param ds <QDataStream> is the output stream to which the serialized
   * ObjectSpaceManifestList is send
   */
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  /**
   * @brief prints the ObjectSpaceManifestList to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  virtual void toDebugString(QDebug &dbg) const override;
};

} // namespace MSONcommon

#endif // OBJECTSPACEMANIFESTLIST_H
