#ifndef ROOTFILENODELIST_H
#define ROOTFILENODELIST_H

#include <QtCore/qglobal.h>
#include <vector>

#include "FileNode.h"
#include "FileNodeListFragment.h"
#include "ObjectSpaceManifestList.h"
#include "commonTypes/FileChunkReference64x32.h"

class RootFileNodeList {
private:
  std::vector<FileNodeListFragment *> m_fileNodeListFragments;

  FileNode m_objectSpaceManifestRoot;

  std::vector<FileNode *> m_fileNodeSequence;

  std::vector<ObjectSpaceManifestList *> m_objectSpaceManifestList;

  std::vector<FileNode *> m_fileDataStoreListReference;

  FileChunkReference64x32 m_fcrFileNodeListRoot;

public:
  RootFileNodeList(FileChunkReference64x32 &reference);

  RootFileNodeList(const RootFileNodeList &source); // copy constructor
  RootFileNodeList(RootFileNodeList &&source);      // move constructor

  RootFileNodeList &operator=(const RootFileNodeList &rhs); // copy assignment
  RootFileNodeList &operator=(RootFileNodeList &&rhs);      // move assignment

  ~RootFileNodeList();

  //
  std::vector<FileNodeListFragment *> getFileNodeListFragments() const;
  void
  setFileNodeListFragments(const std::vector<FileNodeListFragment *> &value);

  FileNode getObjectSpaceManifestRoot() const;
  void setObjectSpaceManifestRoot(const FileNode &value);

  std::vector<FileNode *> getFileNodeSequence() const;
  void setFileNodeSequence(const std::vector<FileNode *> &value);

  std::vector<ObjectSpaceManifestList *> getObjectSpaceManifestLists() const;
  void setObjectSpaceManifestLists(
      const std::vector<ObjectSpaceManifestList *> &value);

  std::vector<FileNode *> getFileDataStoreListReference() const;
  void setFileDataStoreListReference(const std::vector<FileNode *> &value);
  FileChunkReference64x32 getFcrFileNodeListRoot() const;
  void
  setFcrFileNodeListRoot(const FileChunkReference64x32 &fcrFileNodeListRoot);

  //  friend QDataStream &operator<<(QDataStream &ds,
  //                                 const RootFileNodeList &obj);
  friend QDataStream &operator>>(QDataStream &ds, RootFileNodeList &obj);
  friend QDebug operator<<(QDebug dbg, const RootFileNodeList &obj);

private:
  /**
   * @brief creates RootFileNodeList from QDataStream
   * @param ds <QDataStream> containing the deserializable RootFileNodeList
   */
  void deserialize(QDataStream &ds);
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

#endif // ROOTFILENODELIST_H
