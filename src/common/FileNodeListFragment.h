#ifndef FILENODELISTFRAGMENT_H
#define FILENODELISTFRAGMENT_H

#include <QtCore/qglobal.h>

#include "IRevisionStoreFileObject.h"

#include "FileNode.h"
#include "FileNodeListHeader.h"
#include "commonTypes/FileChunkReference32.h"
#include "commonTypes/FileChunkReference64.h"
#include "commonTypes/FileChunkReference64x32.h"
#include "commonTypes/FileNodeChunkReference.h"

#include <QByteArray>

namespace MSONcommon {

class FileNodeListFragment : public IRevisionStoreFileObject {

private:
  FileChunkReference64 m_ref;

  FileNodeListHeader m_fnlheader;

  std::vector<std::shared_ptr<FileNode>> m_rgFileNodes;

  quint64 m_paddingLength;

  FileChunkReference64x32 m_nextFragment;
  /**
   * @brief footer_magic_id
   *
   * \todo find a static place for footer_magic_id
   */
  static constexpr const quint64 footer_magic_id = 0x8BC215C38233BA4B;

public:
  FileNodeListFragment();
  FileNodeListFragment(const FileChunkReference64 ref);
  FileNodeListFragment(const FileChunkReference64x32 ref);
  FileNodeListFragment(const FileChunkReference32 ref);
  FileNodeListFragment(const FileNodeChunkReference ref);
  virtual ~FileNodeListFragment() = default;

  FileChunkReference64 getRef() const;
  void setRef(const FileChunkReference64 &ref);
  void setRef(const FileChunkReference64x32 &ref);
  void setRef(const FileChunkReference32 &ref);
  void setRef(const FileNodeChunkReference &ref);

  FileNodeListHeader getFnlheader() const;
  void setFnlheader(const FileNodeListHeader &fnlheader);

  std::vector<std::shared_ptr<FileNode>> rgFileNodes() const;
  void
  setRgFileNodes(const std::vector<std::shared_ptr<FileNode>> &rgFileNodes);

  quint64 paddingLength() const;
  void setPaddingLength(const quint64 &paddingLength);

  FileChunkReference64x32 getNextFragment() const;
  void setNextFragment(const FileChunkReference64x32 &next);

  quint64 getSizeInFile() const;

private:
  /**
   * @brief creates FileNodeListFragment from QDataStream
   * @param ds <QDataStream> containing the deserializable
   * FileNodeListFragment
   */
  virtual void deserialize(QDataStream &ds) override;
  /**
   * @brief creates byte stream from FileNodeListFragment object
   * @param ds <QDataStream> is the output stream to which the serialized
   * FileNodeListFragment is send
   */
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  /**
   * @brief prints the FileNodeListFragment to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  virtual void toDebugString(QDebug &dbg) const override;
};
} // namespace MSONcommon
#endif // FILENODELISTFRAGMENT_H
