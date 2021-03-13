#ifndef STREAMOBJECT_H
#define STREAMOBJECT_H

#include <memory>

#include <QtCore/qglobal.h>

#include "../StreamObjectHeader.h"
#include "../interfaces/StreamObjectTypes.h"

namespace libmson {
namespace packStore {
namespace streamObj {

/** An abstract class for StreamObjects which start with StreamObjectHeader and
 * have no StreamObjectHeaderEnd */
class StreamObject {
protected:
  /** return the size in bytes of the data contained in this StreamObject,
   * excluding the size of the StreamObjectHeader.*/
  virtual quint64 body_cb() const = 0;

public:
  virtual ~StreamObject() = default;

  quint64 getSizeInFile()
  {
    auto cb = body_cb();

    return cb + StreamObjectHeader::getSizeInFile(cb, getType());
  };

  virtual StreamObjectType getType() const = 0;
};

typedef std::shared_ptr<StreamObject> StreamObject_SPtr_t;
typedef std::weak_ptr<StreamObject> StreamObject_WPtr_t;


} // namespace streamObj
} // namespace packStore
} // namespace libmson

#endif // STREAMOBJECT_H
