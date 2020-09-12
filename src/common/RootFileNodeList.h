#ifndef ROOTFILENODELIST_H
#define ROOTFILENODELIST_H

#include <QXmlStreamWriter>
#include <QtCore/qglobal.h>
#include <vector>

#include "FileNode.h"
#include "FileNodeListFragment.h"
#include "ObjectSpaceManifestList.h"
#include "commonTypes/FileChunkReference64x32.h"

#include "IDeserializable.h"
#include "ISerializable.h"

namespace MSONcommon {

class RootFileNodeList: public IDeserializable {
private:
  /** raw, fragmented FileNode list, can be ignored after defragmenting into
   * m_fileNodeSequence */
  std::vector<std::shared_ptr<FileNodeListFragment>> m_fileNodeListFragments;

  std::shared_ptr<FileNode> m_objectSpaceManifestRoot;

  /** Unfragmented FileNode list */
  std::vector<std::shared_ptr<FileNode>> m_fileNodeSequence;

  std::vector<std::shared_ptr<ObjectSpaceManifestList>> m_objectSpaceManifestList;

  std::vector<std::shared_ptr<FileNode>> m_fileDataStoreListReference;

  FileChunkReference64x32 m_fcrFileNodeListRoot;

public:
  RootFileNodeList(FileChunkReference64x32 &reference);

  //  RootFileNodeList(const RootFileNodeList &source); // copy constructor
  //  RootFileNodeList(RootFileNodeList &&source);      // move constructor

  //  RootFileNodeList &operator=(const RootFileNodeList &rhs); // copy
  //  assignment RootFileNodeList &operator=(RootFileNodeList &&rhs);      //
  //  move assignment

  ~RootFileNodeList() = default;

  //
  std::vector<std::shared_ptr<FileNodeListFragment>> getFileNodeListFragments() const;
  void setFileNodeListFragments(const std::vector<std::shared_ptr<FileNodeListFragment>> &value);

  std::shared_ptr<FileNode> getObjectSpaceManifestRoot();
  void setObjectSpaceManifestRoot(const std::shared_ptr<FileNode> &value);

  std::vector<std::shared_ptr<FileNode>> getFileNodeSequence() const;
  void setFileNodeSequence(const std::vector<std::shared_ptr<FileNode>> &value);

  std::vector<std::shared_ptr<ObjectSpaceManifestList>> getObjectSpaceManifestLists() const;
  void setObjectSpaceManifestLists(
      const std::vector<std::shared_ptr<ObjectSpaceManifestList>> &value);

  std::vector<std::shared_ptr<FileNode>> getFileDataStoreListReference() const;
  void setFileDataStoreListReference(const std::vector<std::shared_ptr<FileNode>> &value);
  FileChunkReference64x32 getFcrFileNodeListRoot() const;
  void
  setFcrFileNodeListRoot(const FileChunkReference64x32 &fcrFileNodeListRoot);

  friend QDebug operator<<(QDebug dbg, const RootFileNodeList &obj);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

private:
  /**
   * @brief creates RootFileNodeList from QDataStream
   * @param ds <QDataStream> containing the deserializable RootFileNodeList
   */
  virtual void deserialize(QDataStream &ds) override;
  //  /**
  //   * @brief creates byte stream from RootFileNodeList object
  //   * @param ds <QDataStream> is the output stream to which the serialized
  //   * RootFileNodeList is send
  //   */
  //  void serialize(QDataStream &ds) const;

  /**
   * @brief prints the RootFileNodeList to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  void toDebugString(QDebug dbg) const;
};

} // namespace MSONcommon

#endif // ROOTFILENODELIST_H
