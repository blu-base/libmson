#ifndef STRINGINSTORAGEBUFFER_H
#define STRINGINSTORAGEBUFFER_H

#include <QDataStream>
#include <QString>
#include <QtCore/qglobal.h>

#include "../IStreamable.h"


namespace libmson {
namespace priv {

class StringInStorageBuffer : public IStreamable {
private:
  quint32 m_cch;

  QByteArray m_rawstring;

  static const quint64 minSizeInFile = 4;
public:
  StringInStorageBuffer();

  quint32 getCch() const;
  void setCch(const quint32 &value);

  QString getStringData() const;
  void setStringData(const QString &value);

  quint64 getSizeInFile() const;

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

};

} // namespace priv
} // namespace libmson

#endif // STRINGINSTORAGEBUFFER_H
