#ifndef FREECHUNKLISTFRAGMENT_H
#define FREECHUNKLISTFRAGMENT_H

#include <QtCore/qglobal.h>
#include <vector>


#include <QDebug>

#include "IDeserializable.h"
#include "ISerializable.h"

#include "commonTypes/FileChunkReference64.h"
#include "commonTypes/FileChunkReference64x32.h"

class QDataStream;

namespace MSONcommon {

class FreeChunkListFragment : public ISerializable, public IDeserializable {
private:
  quint64 m_size = 0;

  /**
   * @brief specifies the CRC of the fcrFreeChunk
   */
  quint32 crc;

  FileChunkReference64x32 fcrNextChunk;

  std::vector<std::shared_ptr<FileChunkReference64>> fcrFreeChunk;

  /**
   * @brief creates FreeChunkListFragment from QDataStream
   * @param ds <QDataStream> containing the deserializable FreeChunkListFragment
   */
  void deserialize(QDataStream &ds);
  /**
   * @brief creates byte stream from FreeChunkListFragment object
   * @param ds <QDataStream> is the output stream to which the serialized
   * FreeChunkListFragment is send
   */
  void serialize(QDataStream &ds) const;

  /**
   * @brief prints the FreeChunkListFragment to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  void toDebugString(QDebug dbg) const;

public:
  FreeChunkListFragment(quint64 size);

  friend QDebug operator<<(QDebug dbg, const FreeChunkListFragment &obj);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

  quint32 getCrc() const;
  void setCrc(const quint32 &value);

  FileChunkReference64x32 getFcrNextChunk() const;
  void setFcrNextChunk(const FileChunkReference64x32 &value);

  std::vector<std::shared_ptr<FileChunkReference64>>  getFcrFreeChunk() const;
  void setFcrFreeChunk(const std::vector<std::shared_ptr<FileChunkReference64>> &value);
};

} // namespace MSONcommon

#endif // FREECHUNKLISTFRAGMENT_H
