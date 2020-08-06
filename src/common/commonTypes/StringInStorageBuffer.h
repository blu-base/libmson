#ifndef STRINGINSTORAGEBUFFER_H
#define STRINGINSTORAGEBUFFER_H

#include <QtCore/qglobal.h>
#include <QString>
#include <QDataStream>
#include <QDebug>
#include <QXmlStreamWriter>

class StringInStorageBuffer
{
private:
    quint32 m_cch;

    QString m_StringData;
public:
  StringInStorageBuffer();



  friend QDataStream &operator<<(QDataStream &ds,
                                 const StringInStorageBuffer &obj);
  friend QDataStream &operator>>(QDataStream &ds, StringInStorageBuffer &obj);
  friend QDebug operator<<(QDebug dbg, const StringInStorageBuffer &obj);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

  quint32 getCch() const;
  void setCch(const quint32& value);

  QString getStringData() const;
  void setStringData(const QString& value);

private:
  /**
   * @brief creates StringInStorageBuffer from QDataStream
   * @param ds <QDataStream> containing the deserializable
   * StringInStorageBuffer
   */
  void deserialize(QDataStream &ds);
  /**
   * @brief creates byte stream from StringInStorageBuffer object
   * @param ds <QDataStream> is the output stream to which the serialized
   * StringInStorageBuffer is send
   */
  void serialize(QDataStream &ds) const;

  /**
   * @brief prints the StringInStorageBuffer to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  void toDebugString(QDebug dbg) const;
};

#endif // STRINGINSTORAGEBUFFER_H
