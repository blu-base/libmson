#ifndef IOBJECTSPACEOPBJECTSTREAM_H
#define IOBJECTSPACEOPBJECTSTREAM_H

#include <QtCore/qglobal.h>

#include "../commonTypes/CompactID.h"
#include "ObjectSpaceObjectStreamHeader.h"

class IObjectSpaceOpbjectStream {
protected:
  ObjectSpaceObjectStreamHeader m_header;
  std::vector<CompactID> m_body;

  IObjectSpaceOpbjectStream();
  IObjectSpaceOpbjectStream(
      const ObjectSpaceObjectStreamHeader::OsidStreamPresence
          &osidStreamPresence,
      const ObjectSpaceObjectStreamHeader::ExtendedStreamPresence
          &extendedStreamPresence);

public:
  virtual ~IObjectSpaceOpbjectStream();

  friend QDataStream &operator<<(QDataStream &ds,
                                 const IObjectSpaceOpbjectStream &obj);
  friend QDataStream &operator>>(QDataStream &ds,
                                 IObjectSpaceOpbjectStream &obj);

  friend QDebug operator<<(QDebug dbg, const IObjectSpaceOpbjectStream &obj);

  ObjectSpaceObjectStreamHeader header() const;
  void setHeader(const ObjectSpaceObjectStreamHeader &header);

  std::vector<CompactID> body() const;
  void setBody(const std::vector<CompactID> &body);

  /**
   * @brief pushbackToBody
   * @param entry
   * @return true if ID could be added without exceeding this streams limit,
   * else return false
   */
  bool pushbackToBody(const CompactID &entry);

  /**
   * @brief removeIdFromBody
   * @param entry
   * @return true if ID was present and could be deleted, else return false
   */
  bool removeIdFromBody(const CompactID &entry);

  /**
   * @brief removeIdFromBody
   * @param position
   * @return true if ID was present and could be deleted, else return false
   */
  bool removeIdFromBody(const quint32 &position);

  /**
   * @brief positionOfIdInBody
   * @param entry
   * @return -1 if ID is not found, else return position
   */
  qint32 positionOfIdInBody(const CompactID &entry);

  bool isIdInBody(const CompactID &entry);

protected:
  /**
   * @brief creates IObjectSpaceOpbjectStream from QDataStream
   * @param ds <QDataStream> containing the deserializable
   * IObjectSpaceOpbjectStream
   *
   * Note, that only 4GB of an FileDataStoreObject can be parsed because an
   * limitation of QByteArray
   */
  void deserialize(QDataStream &ds);
  /**
   * @brief creates byte stream from IObjectSpaceOpbjectStream object
   * @param ds <QDataStream> is the output stream to which the serialized
   * IObjectSpaceOpbjectStream is send
   *

   */
  void serialize(QDataStream &ds) const;

  /**
   * @brief prints the IObjectSpaceOpbjectStream to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  void toDebugString(QDebug dbg) const;
};

#endif // IOBJECTSPACEOPBJECTSTREAM_H
