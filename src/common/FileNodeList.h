#ifndef FILENODELIST_H
#define FILENODELIST_H

#include <QtCore/qglobal.h>
#include <vector>

#include "FileNode.h"
#include "FileNodeListHeader.h"
#include "commonTypes/FileChunkReference64x32.h"
namespace MSONcommon {

    /// \todo FileNodeList class seems duplicate with FileNodeListFragment
class FileNodeList {
private:
  FileNodeListHeader m_fileNodeListHeader;

  std::vector<FileNode *> m_children;

  static constexpr const quint64 header_magic_id = 0xA4567AB1F5F7F4C4;

  quint64 m_paddingLength;

  FileChunkReference64x32 *m_nextFragment;

  static constexpr const uint64_t footer_magic_id = 0x8BC215C38233BA4B;

public:
  FileNodeList();

  FileNodeList(const FileNodeList &fnl); // copy constructor
  FileNodeList(FileNodeList &&fnl);      // move constructor

  ~FileNodeList();

  void appendFileNode(const FileNode &fn);
  void prependFileNode(const FileNode &fn);
  void addFileNode(const FileNode &fn, const quint32 &position);
  void removeFileNode(const quint32 &position);
  void removeFileNodeByID(const quint16 FileNodeID);

  friend QDataStream &operator<<(QDataStream &ds, const FileNodeList &obj);
  friend QDataStream &operator>>(QDataStream &ds, FileNodeList &obj);

  friend QDebug operator<<(QDebug dbg, const FileNodeList &obj);

  FileNodeList &operator=(const FileNodeList &rhs); // copy assignment
  FileNodeList &operator=(FileNodeList &&rhs);      // move assignment

  FileNodeListHeader getFileNodeListHeader() const;
  void setFileNodeListHeader(const FileNodeListHeader &value);
  std::vector<FileNode *> getChildren() const;
  void setChildren(const std::vector<FileNode *> &value);
  quint64 getPaddingLength() const;
  void setPaddingLength(const quint64 &value);
  FileChunkReference64x32 *getNextFragment() const;
  void setNextFragment(FileChunkReference64x32 *nextFragment);
};
} // namespace MSONcommon
#endif // FILENODELIST_H
