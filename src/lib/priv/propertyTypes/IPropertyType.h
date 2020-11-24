#ifndef IPROPERTYTYPE_H
#define IPROPERTYTYPE_H

#include <QtCore/qglobal.h>

#include "../IStreamable.h"
#include <memory>

namespace libmson {
namespace priv {

class IPropertyType : public IStreamable {
public:
  IPropertyType()          = default;
  virtual ~IPropertyType() = default;

  virtual quint64 getSizeInFile() const = 0;
};

typedef std::shared_ptr<IPropertyType> IPropertyType_SPtr_t;
typedef std::weak_ptr<IPropertyType> IPropertyType_WPtr_t;

} // namespace priv
} // namespace libmson

#endif // IPROPERTYTYPE_H
