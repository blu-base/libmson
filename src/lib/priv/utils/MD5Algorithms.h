#ifndef MD5ALGORITHMS_H
#define MD5ALGORITHMS_H

#include <QtCore/qglobal.h>
#include <QByteArray>

namespace libmson {
namespace priv {

class MD5Algorithm
{
public:

  static QByteArray chunkCheckSum(const QByteArray& data);

};

} // namespace priv
} // namespace libmson

#endif // MD5ALGORITHMS_H
