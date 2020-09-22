#ifndef IOBJECTSPACEOPBJECTSTREAM_H
#define IOBJECTSPACEOPBJECTSTREAM_H

#include <QtCore/qglobal.h>

#include "../commonTypes/CompactID.h"
#include "ObjectSpaceObjectStreamHeader.h"

#include "../IRevisionStoreFileObject.h"

namespace MSONcommon {

class IObjectSpaceObjectStream : public IRevisionStoreFileObject {
protected:
  ObjectSpaceObjectStreamHeader m_header;
  std::vector<CompactID> m_body;

  IObjectSpaceObjectStream();
  IObjectSpaceObjectStream(
      const ObjectSpaceObjectStreamHeader::OsidStreamPresence
          &osidStreamPresence,
      const ObjectSpaceObjectStreamHeader::ExtendedStreamPresence
          &extendedStreamPresence);

public:
  virtual ~IObjectSpaceObjectStream();

  ObjectSpaceObjectStreamHeader header() const;
  void setHeader(const ObjectSpaceObjectStreamHeader &header);

  std::vector<CompactID> body() const;
  void setBody(const std::vector<CompactID> &body);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

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

  quint64 getSizeInFile() const;

protected:
  /**
   * @brief creates IObjectSpaceObjectStream from QDataStream
   * @param ds <QDataStream> containing the deserializable
   * IObjectSpaceObjectStream
   *
   * Note, that only 4GB of an FileDataStoreObject can be parsed because an
   * limitation of QByteArray
   */
  virtual void deserialize(QDataStream &ds) override;
  /**
   * @brief creates byte stream from IObjectSpaceObjectStream object
   * @param ds <QDataStream> is the output stream to which the serialized
   * IObjectSpaceObjectStream is send
   *

   */
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  /**
   * @brief prints the IObjectSpaceObjectStream to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  virtual void toDebugString(QDebug &dbg) const override;

  static const quint64 sizeInFileBase;
};

} // namespace MSONcommon

#endif // IOBJECTSPACEOPBJECTSTREAM_H
