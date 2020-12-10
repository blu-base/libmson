#ifndef IPROPERTYTYPE_H
#define IPROPERTYTYPE_H

#include <QtCore/qglobal.h>

#include "../IStreamable.h"
#include <memory>

namespace libmson {
namespace priv {

enum class PropertyIDType : quint8 {
  None = 0x0,

  NoData                          = 0x1,
  Bool                            = 0x2,
  OneByteOfData                   = 0x3,
  TwoBytesOfData                  = 0x4,
  FourBytesOfData                 = 0x5,
  EightBytesOfData                = 0x6,
  FourBytesOfLengthFollowedByData = 0x7,
  ObjectID                        = 0x8,
  ArrayOfObjectIDs                = 0x9,
  ObjectSpaceID                   = 0xA,
  ArrayOfObjectSpaceIDs           = 0xB,
  ContextID                       = 0xC,
  ArrayOfContextIDs               = 0xD,
  ArrayOfPropertyValues           = 0x10,
  PropertySet                     = 0x11,

  ArrayNumber = 0xFE,
  InvalidType = 0xFF,


};


class IPropertyType : public IStreamable {
public:
  IPropertyType()          = default;
  virtual ~IPropertyType() = default;

  virtual quint64 getSizeInFile() const = 0;

  virtual PropertyIDType getType() const = 0;
};

typedef std::shared_ptr<IPropertyType> IPropertyType_SPtr_t;
typedef std::weak_ptr<IPropertyType> IPropertyType_WPtr_t;

} // namespace priv
} // namespace libmson

#endif // IPROPERTYTYPE_H
