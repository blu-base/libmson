#ifndef FILEDATASTOREOBJECT_H
#define FILEDATASTOREOBJECT_H

#include <QtCore/qglobal.h>
#include <cstdlib>

#include <QUuid>

class FileDataStoreObject {
private:
  /**
   * @brief MUST be {BDE316E7-2665-4511-A4C4-8D4D0B7A9EAC}.
   */
  QUuid m_guidHeader;

  /**
   * @brief specifies the size, in bytes, of the FileData field without padding.
   */
  quint64 m_cbLength;

  /**
   * @brief MUST be zero, and MUST be ignored
   */
  quint32 m_unused;

  /**
   * @brief MUST be zero, and MUST be ignored
   */
  quint64 m_reserved;

  /**
   * @brief specifies the data for the file data object.
   *
   * Padding is added to the end of the FileData stream to ensure that the
   * FileDataStoreObject structure ends on an 8-byte boundary
   */
  QByteArray m_FileData;

  /**
   * @brief number of bytes of padding added to m_FileData, to increase its size
   * to multiple of 8 byte.
   */
  quint8 m_padding;

  /**
   * @brief MUST be {71FBA722-0F79-4A0B-BB13-899256426B24}.
   */
  QUuid m_guidFooter;

public:
  FileDataStoreObject();

  friend QDataStream &operator<<(QDataStream &ds,
                                 const FileDataStoreObject &obj);
  friend QDataStream &operator>>(QDataStream &ds, FileDataStoreObject &obj);

  friend QDebug operator<<(QDebug dbg, const FileDataStoreObject &obj);

  QUuid guidHeader() const;
  void setGuidHeader(const QUuid &guidHeader);

  quint64 cbLength() const;
  void setCbLength(const quint64 &cbLength);

  QByteArray FileData() const;
  void setFileData(const QByteArray &FileData);

  QUuid guidFooter() const;
  void setGuidFooter(const QUuid &guidFooter);

private:
  /**
   * @brief creates IProperty from QDataStream
   * @param ds <QDataStream> containing the deserializable IProperty
   *
   * Note, that only 4GB of an FileDataStoreObject can be parsed because an
   * limitation of QByteArray
   */
  void deserialize(QDataStream &ds);
  /**
   * @brief creates byte stream from IProperty object
   * @param ds <QDataStream> is the output stream to which the serialized
   * IProperty is send
   *

   */
  void serialize(QDataStream &ds) const;

  /**
   * @brief prints the IProperty to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  void toDebugString(QDebug dbg) const;
};

#endif // FILEDATASTOREOBJECT_H
