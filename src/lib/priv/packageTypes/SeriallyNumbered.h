#ifndef SERIALLYNUMBERED_H
#define SERIALLYNUMBERED_H

#include <QtCore/qglobal.h>

#include "../../commonTypes/LongExtGuid.h"

namespace libmson {
namespace packStore {
namespace streamObj {

class SeriallyNumbered {
protected:
  SeriallyNumbered() = default;

  LongExtGuid m_serialNumber;

public:
  virtual ~SeriallyNumbered() = default;

  LongExtGuid getSerialNumber() const;
  void setSerialNumber(const LongExtGuid& serialNumber);
};


} // namespace streamObj
} // namespace packStore
} // namespace libmson
#endif // SERIALLYNUMBERED_H
