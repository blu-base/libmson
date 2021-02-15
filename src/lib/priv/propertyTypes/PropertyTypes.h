#ifndef PROPERTYTYPES_H
#define PROPERTYTYPES_H

#include <memory>

// case PropertyIDType::ArrayOfObjectIDs:
// case PropertyIDType::ArrayOfObjectSpaceIDs:
// case PropertyIDType::ArrayOfContextIDs:
#include "PropertyType_ArrayNumber.h"

#include "PropertyType_ArrayOfPropertyValues.h"
#include "PropertyType_EightBytesOfData.h"
#include "PropertyType_FourBytesOfData.h"
#include "PropertyType_FourBytesOfLengthFollowedByData.h"

// case PropertyIDType::NoData:
// case PropertyIDType::Bool:
// case PropertyIDType::ContextID:
// case PropertyIDType::ObjectSpaceID:
// case PropertyIDType::ObjectID:
#include "PropertyType_NoData.h"

#include "PropertyType_OneByteOfData.h"
#include "PropertyType_PropertySet.h"
#include "PropertyType_TwoBytesOfData.h"


namespace libmson {
namespace priv {

typedef std::shared_ptr<PropertyType_ArrayNumber>
    PropertyType_ArrayNumber_SPtr_t;
typedef std::weak_ptr<PropertyType_ArrayNumber> PropertyType_ArrayNumber_WPtr_t;

typedef std::shared_ptr<PropertyType_ArrayOfPropertyValues>
    PropertyType_ArrayOfPropertyValues_SPtr_t;
typedef std::weak_ptr<PropertyType_ArrayOfPropertyValues>
    PropertyType_ArrayOfPropertyValues_WPtr_t;

typedef std::shared_ptr<PropertyType_EightBytesOfData>
    PropertyType_EightBytesOfData_SPtr_t;
typedef std::weak_ptr<PropertyType_EightBytesOfData>
    PropertyType_EightBytesOfData_WPtr_t;

typedef std::shared_ptr<PropertyType_FourBytesOfData>
    PropertyType_FourBytesOfData_SPtr_t;
typedef std::weak_ptr<PropertyType_FourBytesOfData>
    PropertyType_FourBytesOfData_WPtr_t;

typedef std::shared_ptr<PropertyType_FourBytesOfLengthFollowedByData>
    PropertyType_FourBytesOfLengthFollowedByData_SPtr_t;
typedef std::weak_ptr<PropertyType_FourBytesOfLengthFollowedByData>
    PropertyType_FourBytesOfLengthFollowedByData_WPtr_t;

typedef std::shared_ptr<PropertyType_NoData> PropertyType_NoData_SPtr_t;
typedef std::weak_ptr<PropertyType_NoData> PropertyType_NoData_WPtr_t;

typedef std::shared_ptr<PropertyType_OneByteOfData>
    PropertyType_OneByteOfData_SPtr_t;
typedef std::weak_ptr<PropertyType_OneByteOfData>
    PropertyType_OneByteOfData_WPtr_t;

typedef std::shared_ptr<PropertyType_PropertySet>
    PropertyType_PropertySet_SPtr_t;
typedef std::weak_ptr<PropertyType_PropertySet> PropertyType_PropertySet_WPtr_t;

typedef std::shared_ptr<PropertyType_TwoBytesOfData>
    PropertyType_TwoBytesOfData_SPtr_t;
typedef std::weak_ptr<PropertyType_TwoBytesOfData>
    PropertyType_TwoBytesOfData_WPtr_t;


} // namespace priv
} // namespace libmson

#endif // PROPERTYTYPES_H
