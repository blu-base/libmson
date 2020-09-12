#ifndef STRINGINSTORAGEBUFFER_H
#define STRINGINSTORAGEBUFFER_H

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QXmlStreamWriter>
#include <QtCore/qglobal.h>

#include "../IDeserializable.h"
#include "../ISerializable.h"

namespace MSONcommon {

class StringInStorageBuffer : public ISerializable, public IDeserializable{
private:
  quint32 m_cch;

  QByteArray m_rawstring;

public:
  StringInStorageBuffer();

  friend QDebug operator<<(QDebug dbg, const StringInStorageBuffer &obj);

  quint32 getCch() const;
  void setCch(const quint32 &value);

  QString getStringData() const;
  void setStringData(const QString &value);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

private:
  /**
   * @brief creates StringInStorageBuffer from QDataStream
   * @param ds <QDataStream> containing the deserializable
   * StringInStorageBuffer
   */
  virtual void deserialize(QDataStream &ds) override;
  /**
   * @brief creates byte stream from StringInStorageBuffer object
   * @param ds <QDataStream> is the output stream to which the serialized
   * StringInStorageBuffer is send
   */
  virtual void serialize(QDataStream &ds) const override;

  /**
   * @brief prints the StringInStorageBuffer to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  void toDebugString(QDebug dbg) const;
};

} // namespace MSONcommon

#endif // STRINGINSTORAGEBUFFER_H
