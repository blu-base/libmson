#ifndef OBJECTSPACEOBJECTSTREAMHEADER_H
#define OBJECTSPACEOBJECTSTREAMHEADER_H

#include <QXmlStreamWriter>
#include <QtCore/qglobal.h>

#include "../IDeserializable.h"
#include "../ISerializable.h"

namespace MSONcommon {

class ObjectSpaceObjectStreamHeader : public ISerializable, public IDeserializable {
private:
  quint32 m_count;
  bool m_OsidStreamNotPresent;
  bool m_ExtendedStreamsPresent;

public:
  enum class OsidStreamPresence : bool {
    Present = false,
    NotPresent = true,
  };

  enum class ExtendedStreamPresence : bool {
    Present = true,
    NotPresent = false,
  };

  ObjectSpaceObjectStreamHeader();
  ObjectSpaceObjectStreamHeader(
      const OsidStreamPresence &osidStreamPresence,
      const ExtendedStreamPresence &extendedStreamPresence);
  ObjectSpaceObjectStreamHeader(
      const quint32 &count, const OsidStreamPresence &osidStreamPresence,
      const ExtendedStreamPresence &extendedStreamPresence);

  quint32 count() const;
  void setCount(const quint32 &count);

  bool incrementCount();
  bool decrementCount();

  bool ExtendedStream_isPresent() const;
  void setExtendedStreamsPresence(
      const ExtendedStreamPresence &extendedStreamPresence);
  bool OsidStream_isNotPresent() const;
  void setOsidStreamPresence(const OsidStreamPresence &osidStreamPresence);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

  friend QDebug operator<<(QDebug dbg,
                           const ObjectSpaceObjectStreamHeader &obj);

private:
  /**
   * @brief creates ObjectSpaceObjectStreamHeader from QDataStream
   * @param ds <QDataStream> containing the deserializable
   * ObjectSpaceObjectStreamHeader
   *
   * Note, that only 4GB of an FileDataStoreObject can be parsed because an
   * limitation of QByteArray
   */
  virtual void deserialize(QDataStream &ds) override;
  /**
   * @brief creates byte stream from ObjectSpaceObjectStreamHeader object
   * @param ds <QDataStream> is the output stream to which the serialized
   * ObjectSpaceObjectStreamHeader is send
   */
  virtual void serialize(QDataStream &ds) const override;

  /**
   * @brief prints the ObjectSpaceObjectStreamHeader to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  void toDebugString(QDebug dbg) const;
};

} // namespace MSONcommon

#endif // OBJECTSPACEOBJECTSTREAMHEADER_H
