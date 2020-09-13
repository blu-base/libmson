#ifndef FREECHUNKLISTFRAGMENT_H
#define FREECHUNKLISTFRAGMENT_H

#include <QtCore/qglobal.h>
#include <vector>

#include <QDebug>

#include "IRevisionStoreFileObject.h"

#include "commonTypes/FileChunkReference64.h"
#include "commonTypes/FileChunkReference64x32.h"

class QDataStream;

namespace MSONcommon {

class FreeChunkListFragment : public IRevisionStoreFileObject {
private:
  quint64 m_size = 0;

  /**
   * @brief specifies the CRC of the fcrFreeChunk
   */
  quint32 crc;

  FileChunkReference64x32 fcrNextChunk;

  std::vector<std::shared_ptr<FileChunkReference64>> fcrFreeChunk;

public:
  FreeChunkListFragment(quint64 size);

  friend QDebug operator<<(QDebug dbg, const FreeChunkListFragment &obj);

  quint32 getCrc() const;
  void setCrc(const quint32 &value);

  FileChunkReference64x32 getFcrNextChunk() const;
  void setFcrNextChunk(const FileChunkReference64x32 &value);

  std::vector<std::shared_ptr<FileChunkReference64>> getFcrFreeChunk() const;
  void setFcrFreeChunk(
      const std::vector<std::shared_ptr<FileChunkReference64>> &value);

private:
  /**
   * @brief creates FreeChunkListFragment from QDataStream
   * @param ds <QDataStream> containing the deserializable FreeChunkListFragment
   */
  virtual void deserialize(QDataStream &ds) override;
  /**
   * @brief creates byte stream from FreeChunkListFragment object
   * @param ds <QDataStream> is the output stream to which the serialized
   * FreeChunkListFragment is send
   */
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  /**
   * @brief prints the FreeChunkListFragment to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  void toDebugString(QDebug dbg) const;
};

} // namespace MSONcommon

#endif // FREECHUNKLISTFRAGMENT_H
