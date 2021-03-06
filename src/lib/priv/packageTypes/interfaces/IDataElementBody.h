#ifndef DATAELEMENTBODY_H
#define DATAELEMENTBODY_H

#include <memory>

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "DataElementType.h"

namespace libmson {
namespace fsshttpb {

/** Data between DataElement's  CompactUInt64 m_DataElementType and the
 * StreamObjectHeaderEnd */
class DataElementBody {
protected:
  virtual quint64 cb() const = 0;

public:
  DataElementBody() = default;

  virtual DataElementType getType() const = 0;

  quint64 getSizeInFile() { return cb(); }
};

typedef std::shared_ptr<DataElementBody> DataElementBody_SPtr_t;
typedef std::weak_ptr<DataElementBody> DataElementBody_WPtr_t;

} // namespace fsshttpb
} // namespace libmson

#endif // DATAELEMENTBODY_H
