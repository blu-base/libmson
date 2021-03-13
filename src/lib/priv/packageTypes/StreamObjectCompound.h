#ifndef STREAMOBJECTCOMPOUND_H
#define STREAMOBJECTCOMPOUND_H

#include <memory>
#include <typeinfo>

#include <QtCore/qglobal.h>

#include "StreamObject.h"

namespace libmson {
namespace packStore {
namespace streamObj {


class StreamObjectCompound;

typedef std::shared_ptr<StreamObjectCompound> StreamObjectCompound_SPtr_t;
typedef std::weak_ptr<StreamObjectCompound> StreamObjectCompound_WPtr_t;

/** An interface class for StreamObjects which have StreamObjects as members.
 * StreamObjectCompound must end with a StreamObjectHeaderEnd */
class StreamObjectCompound : public StreamObject {
protected:
  StreamObjectCompound();

public:
  virtual ~StreamObjectCompound() = default;

  virtual std::vector<StreamObjectCompound_SPtr_t> getObjects() const = 0;

  /** returns a vector only of the objects which have the same type_info as ti*/
  virtual std::vector<StreamObjectCompound_SPtr_t>
  getObjects(const std::type_info& ti) const = 0;
};

} // namespace streamObj
} // namespace packStore
} // namespace libmson

#endif // STREAMOBJECTCOMPOUND_H
