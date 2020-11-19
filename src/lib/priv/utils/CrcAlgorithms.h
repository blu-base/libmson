#ifndef CRCALGORITHMS_H
#define CRCALGORITHMS_H

#include <QByteArray>
#include <QtCore/qglobal.h>

#include <array>

namespace libmson {
namespace priv {

class MsoCrc32 {
private:
  static std::array<quint32, 256> cache;
  static bool cacheInitialized;

  static const quint32 polynomial;
  static const quint32 initialVal;

  static void initializeCache();

  /// \todo make stream versions of MsoCrc32
public:
  static quint32 computeCRC(const QByteArray& obj, const quint32 crcStart);
  static bool validateCRC(const QByteArray& obj, const quint32 crc);
};

class Crc32 {
private:
  /// \brief Precalculated cache for CRC32
  ///
  /// Using these settings:
  /// +------------+------------+-------+--------+------------+
  /// | Polynomial | InitialVal | RefIn | RefOut | XorOut     |
  /// +------------+------------+-------+--------+------------+
  /// | 0x04C11DB7 | 0xFFFFFFFF | true  | true   | 0xFFFFFFFF |
  /// +------------+------------+-------+--------+------------+
  ///
  static const std::array<quint32, 256> cache;
  /// CRC polynomal: 0x04C11DB7
  static const quint32 polynomial;

  /// \todo make stream versions of Crc32C
public:
  /// \brief CRC32 algorithm according to RFC3309
  ///
  ///
  static quint32
  computeCRC(const QByteArray& obj, const quint32 crcStart = 0xFFFFFFFF);
  static bool validateCRC(const QByteArray& obj, const quint32 crc);

  /// \brief computes RevisionStoreFileHeader's crcName from a fileName
  /// (non-null-terminated).
  static quint32 computeCrcName(const QString& fileName);
};

} // namespace priv
} // namespace libmson

#endif // CRCALGORITHMS_H
