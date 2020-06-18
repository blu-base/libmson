#ifndef FILENODELISTFRAGMENT_H
#define FILENODELISTFRAGMENT_H

#include <QtCore/qglobal.h>

#include "FileNode.h"
#include "FileNodeListHeader.h"
#include "commonTypes/FileChunkReference64x32.h"

class FileNodeListFragment {

private:
  quint64 m_size;

  FileNodeListHeader m_fnlheader;

  std::vector<FileNode *> m_rgFileNodes;

  quint64 m_paddingLength;

  FileChunkReference64x32 m_nextFragment;
  /**
   * @brief footer_magic_id
   *
   * \todo find a static place for footer_magic_id
   */
  const quint64 footer_magic_id = 0x8BC215C38233BA4B;

public:
  FileNodeListFragment(const quint64 size);
  ~FileNodeListFragment();

  friend QDataStream &operator<<(QDataStream &ds,
                                 const FileNodeListFragment &obj);
  friend QDataStream &operator>>(QDataStream &ds, FileNodeListFragment &obj);

  friend QDebug operator<<(QDebug dbg, const FileNodeListFragment &obj);

  quint64 size() const;
  void setSize(const quint64 &size);
  FileNodeListHeader fnlheader() const;
  void setFnlheader(const FileNodeListHeader &fnlheader);
  std::vector<FileNode *> rgFileNodes() const;
  void setRgFileNodes(const std::vector<FileNode *> &rgFileNodes);
  quint64 paddingLength() const;
  void setPaddingLength(const quint64 &paddingLength);
  FileChunkReference64x32 nextFragment() const;
  void setNextFragment(const FileChunkReference64x32 &next);
};

#endif // FILENODELISTFRAGMENT_H
