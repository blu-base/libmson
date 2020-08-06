#ifndef FILENODELISTFRAGMENT_H
#define FILENODELISTFRAGMENT_H

#include <QtCore/qglobal.h>

#include "FileNode.h"
#include "FileNodeListHeader.h"
#include "commonTypes/FileChunkReference32.h"
#include "commonTypes/FileChunkReference64.h"
#include "commonTypes/FileChunkReference64x32.h"
#include "commonTypes/FileNodeChunkReference.h"

#include <QByteArray>

namespace MSONcommon {

class FileNodeListFragment {

private:
  FileChunkReference64 m_ref;

  FileNodeListHeader m_fnlheader;

  std::vector<FileNode *> m_rgFileNodes;

  quint64 m_paddingLength;

  /// \todo temporary Qbytearray to check junk in padding
  QByteArray padding;

  FileChunkReference64x32 m_nextFragment;
  /**
   * @brief footer_magic_id
   *
   * \todo find a static place for footer_magic_id
   */
  const quint64 footer_magic_id = 0x8BC215C38233BA4B;

public:
  FileNodeListFragment(const FileChunkReference64 ref);
  FileNodeListFragment(const FileChunkReference64x32 ref);
  FileNodeListFragment(const FileChunkReference32 ref);
  FileNodeListFragment(const FileNodeChunkReference ref);
  ~FileNodeListFragment();

  FileChunkReference64 ref() const;
  void setRef(const FileChunkReference64 &size);
  void setRef(const FileChunkReference64x32 &size);
  void setRef(const FileChunkReference32 &size);
  void setRef(const FileNodeChunkReference &size);

  FileNodeListHeader fnlheader() const;
  void setFnlheader(const FileNodeListHeader &fnlheader);
  std::vector<FileNode *> rgFileNodes() const;
  void setRgFileNodes(const std::vector<FileNode *> &rgFileNodes);
  quint64 paddingLength() const;
  void setPaddingLength(const quint64 &paddingLength);
  FileChunkReference64x32 nextFragment() const;
  void setNextFragment(const FileChunkReference64x32 &next);

  friend QDataStream &operator<<(QDataStream &ds,
                                 const FileNodeListFragment &obj);
  friend QDataStream &operator>>(QDataStream &ds, FileNodeListFragment &obj);
  friend QDebug operator<<(QDebug dbg, const FileNodeListFragment &obj);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

private:
  /**
   * @brief creates FileNodeListFragment from QDataStream
   * @param ds <QDataStream> containing the deserializable
   * FileNodeListFragment
   */
  void deserialize(QDataStream &ds);
  /**
   * @brief creates byte stream from FileNodeListFragment object
   * @param ds <QDataStream> is the output stream to which the serialized
   * FileNodeListFragment is send
   */
  void serialize(QDataStream &ds) const;

  /**
   * @brief prints the FileNodeListFragment to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  void toDebugString(QDebug dbg) const;
};
} // namespace MSONcommon
#endif // FILENODELISTFRAGMENT_H
