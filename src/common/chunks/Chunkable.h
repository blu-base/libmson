#ifndef CHUNKABLE_H
#define CHUNKABLE_H

#include <QtCore/qglobal.h>

enum class RevisionStoreChunkType;

namespace libmson {

class Chunkable {
public:
  virtual qint64 getSize() const = 0;
  virtual RevisionStoreChunkType getType() const = 0;
};

} // namespace libmson

#endif // CHUNKABLE_H
