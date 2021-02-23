#include "MultiByteEncoding.h"

namespace libmson::isf {

constexpr const quint8 flagMask = 0x80;
constexpr const quint8 valMask  = 0x7F;
constexpr const quint8 signMask = 0x01;

quint64 MultiByteEncoding::decodeUInt(const QByteArray& ba, quint8* bytesread)
{
  QDataStream ds(ba);

  return decodeUInt(ds, bytesread);
}

quint64 MultiByteEncoding::decodeUInt(QDataStream& ds, quint8* bytesread)
{
  qint64 originalPos = ds.device()->pos();

  bool flag     = true; // end of block flag
  quint8 count  = 0;    // how many bytes read
  quint64 value = 0;    // return variable

  while (flag && !ds.atEnd() && count < 10) {
    quint8 byte = 0;
    ds >> byte;

    flag = (byte & flagMask) == flagMask;
    value += static_cast<quint64>(byte & valMask) << (count * 7);
    count++;
  }
  // if ds ends early, flag might still be true indicating it failed decoding
  if (flag) {
    ds.device()->seek(originalPos);
    count = 0;
    value = 0;
  }

  if (bytesread != nullptr) {
    *bytesread = count;
  }
  return value;
}

qint64 MultiByteEncoding::decodeInt(const QByteArray& ba, quint8* bytesread)
{
  QDataStream ds(ba);

  return decodeInt(ds, bytesread);
}

qint64 MultiByteEncoding::decodeInt(QDataStream& ds, quint8* bytesread)
{
  bool isNegative    = false;
  quint64 predecoded = decodeUInt(ds, bytesread);

  if ((predecoded & signMask) == signMask) {
    isNegative = true;
  }

  predecoded >>= 1;

  auto value = static_cast<qint64>(predecoded);

  if (isNegative) {
    value *= -1;
  }

  return value;
}

QByteArray MultiByteEncoding::encodeUInt(quint64 val)
{
  QByteArray result;

  QDataStream ds(&result, QIODevice::WriteOnly);

  encodeUInt(val, ds);

  return result;
}

void MultiByteEncoding::encodeUInt(quint64 val, QDataStream& ds)
{
  while (val > valMask) {
    quint8 byte = (val & valMask) | flagMask;
    ds << byte;
    val >>= 7;
  }

  // remainder
  ds << static_cast<quint8>(val);
}

QByteArray MultiByteEncoding::encodeInt(qint64 val)
{
  QByteArray result;
  QDataStream ds(&result, QIODevice::WriteOnly);

  encodeInt(val, ds);

  return result;
}

void MultiByteEncoding::encodeInt(qint64 val, QDataStream& ds)
{
  bool isNegative = (val < 0);

  if (isNegative) {
    val *= -1;
  }

  auto preencode = static_cast<quint64>(val << 1);

  if (isNegative) {
    preencode |= signMask;
  }

  while (preencode > valMask) {
    quint8 byte = (preencode & valMask) | flagMask;
    ds << byte;
    preencode >>= 7;
  }

  ds << static_cast<quint8>(preencode);
}

std::vector<qint64> MultiByteEncoding::decodeInkPath(const QByteArray& ba)
{
  QDataStream ds(ba);

  return decodeInkPath(ds);
}

std::vector<qint64> MultiByteEncoding::decodeInkPath(QDataStream& ds)
{
  std::vector<qint64> vec;
  quint8 bytesread = 0;

  auto vecsize = decodeInt(ds, &bytesread);

  if (bytesread == 0 || vecsize == 0) {
    return vec;
  }


  while (!ds.atEnd()) {

    auto val = decodeInt(ds, &bytesread);

    if (bytesread == 0) {
      break;
    }

    vec.push_back(val);
  }


  if (vec.size() != static_cast<size_t>(vecsize)) {
    return std::vector<qint64>();
  }


  return vec;
}

QByteArray MultiByteEncoding::encodeInkPath(const std::vector<qint64>& inkPath)
{
  QByteArray ba;
  QDataStream ds(&ba, QIODevice::WriteOnly);

  encodeInkPath(inkPath, ds);

  return ba;
}

void MultiByteEncoding::encodeInkPath(
    const std::vector<qint64>& inkPath, QDataStream& ds)
{
  encodeInt(inkPath.size(), ds);

  for (const auto& val : inkPath) {
    encodeInt(val, ds);
  }
}

} // namespace libmson::isf
