#ifndef IPROPERTY_H
#define IPROPERTY_H

#include <QtCore/qglobal.h>

#include <QXmlStreamWriter>

#include "../IStreamable.h"

namespace libmson{
namespace priv{

class IProperty : public IStreamable {
protected:
  IProperty() = default;
  virtual ~IProperty() = default;
};

} //namespace priv
} // namespace libmson

#endif // IPROPERTY_H
