#ifndef IPROPERTYTYPE_H
#define IPROPERTYTYPE_H

#include <QtCore/qglobal.h>

#include <QXmlStreamWriter>

#include "../IStreamable.h"

namespace libmson{
namespace priv{

class IPropertyType : public IStreamable {
public:
  IPropertyType() = default;
  virtual ~IPropertyType() = default;

  virtual quint64 getSizeInFile() const = 0;
};

} //namespace priv
} // namespace libmson

#endif // IPROPERTYTYPE_H
