#ifndef MULTIBYTEENCODING_H
#define MULTIBYTEENCODING_H

#include <QtCore/qglobal.h>

#include <QByteArray>
#include <QDataStream>
#include <vector>

namespace libmson::isf {

class MultiByteEncoding {
public:
  MultiByteEncoding() = default;


  /**
   * @brief decodes an unsigned integer from the beginning of the QByteArray
   *
   * It will ignore everything after the first decoded block.
   * If bytesread returns 0, then the method failed to decode a valid value.
   * @param ba
   * @param bytesread returns how many bytes are actually used for decoding
   * @return decoded value
   */
  static quint64 decodeUInt(const QByteArray& ba, quint8* bytesread = nullptr);
  /**
   * @brief decodes an unsigned integer from the current position in QDataStream
   *
   * the position pointer will be advanced by the amount of bytes used to decode
   * the current value.
   *
   * @param ds
   * @return decoded value
   */
  static quint64 decodeUInt(QDataStream& ds, quint8* bytesread = nullptr);

  /**
   * @brief decodes a signed integer from the beginning of the QByteArray
   *
   * It will ignore everything after the first decoded block.
   * If bytesread returns 0, then the method failed to decode a valid value.
   * @param ba
   * @param bytesread returns how many bytes are actually used for decoding
   * @return decoded value
   */
  static qint64 decodeInt(const QByteArray& ba, quint8* bytesread = nullptr);
  /**
   * @brief decodes a signed integer from the current position in QDataStream
   * @param ds
   * @return decoded value
   */
  static qint64 decodeInt(QDataStream& ds, quint8* bytesread = nullptr);


  /**
   * @brief encode an unsigned integer into a new QByteArray
   * @param val
   * @return byte array of respectively required length
   */
  static QByteArray encodeUInt(quint64 val);
  /**
   * @brief encode an unsigned integer and append to QDataStream
   * @param val
   * @param ds
   */
  static void encodeUInt(quint64 val, QDataStream& ds);

  /**
   * @brief encode a signed integer into a new QByteArray
   *
   * @param val
   * empty QByteArray
   * @return
   */
  static QByteArray encodeInt(qint64 val);
  /**
   * @brief encode a signed integer and append to QDataStream
   * @param val
   * is written to QDataStream
   * @param ds
   */
  static void encodeInt(qint64 val, QDataStream& ds);


  /**
   * @brief utility which decodes the data in an InkPath property
   * @param ba
   * @return
   */
  static std::vector<qint64> decodeInkPath(const QByteArray& ba);
  /**
   * @brief utility which decodes InkPath property from a QDataStream
   * @param ba
   * @return
   */
  static std::vector<qint64> decodeInkPath(QDataStream& ds);

  /**
   * @brief utility to encode an InkPath property into a new QByteArray
   * @param inkPath
   * @return
   */
  static QByteArray encodeInkPath(const std::vector<qint64>& inkPath);
  /**
   * @brief utility to append an InkPath property to QDataStream
   * @param inkPath
   * @param ds
   */
  static void
  encodeInkPath(const std::vector<qint64>& inkPath, QDataStream& ds);
};

} // namespace libmson::isf

#endif // MULTIBYTEENCODING_H
