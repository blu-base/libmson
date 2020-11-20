#include "MD5Algorithms.h"

#include <QCryptographicHash>

namespace libmson {
namespace priv {

QByteArray MD5Algorithm::chunkCheckSum(const QByteArray& data)
{
  QCryptographicHash hash(QCryptographicHash::Md5);

  hash.addData(data);
  return hash.result();
}




} // namespace priv
} // namespace libmson
