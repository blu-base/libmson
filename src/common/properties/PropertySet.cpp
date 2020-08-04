#include "PropertySet.h"
#include <QDebug>

#include "PropertyType_NoData.h"
#include "PropertyType_ArrayNumber.h"
#include "PropertyType_OneByteOfData.h"
#include "PropertyType_TwoBytesOfData.h"
#include "PropertyType_FourBytesOfData.h"
#include "PropertyType_EightBytesOfData.h"
#include "PropertyType_FourBytesOfLengthFollowedByData.h"
#include "PropertyType_ArrayOfPropertyValues.h"
#include "PropertyType_PropertySet.h"

quint32 PropertySet::cProperties() const { return m_cProperties; }

void PropertySet::setCProperties(const quint32 &cProperties) {
  m_cProperties = cProperties;
}

std::vector<PropertyID> PropertySet::rgPrids() const { return m_rgPrids; }

void PropertySet::setRgPrids(const std::vector<PropertyID> &rgPrids) {
  m_rgPrids = rgPrids;
}

std::vector<IPropertyType*> PropertySet::rgData() const { return m_rgData; }

void PropertySet::setRgData(const std::vector<IPropertyType*> &rgData) { m_rgData = rgData; }

/// \todo implement propertyset
void PropertySet::deserialize(QDataStream &ds) {

    ds >> m_cProperties;

    for (int i = 0; i< m_cProperties; i++) {
        PropertyID prid;
        ds >> prid;
        m_rgPrids.push_back(prid);

    }

    for( PropertyID propID : m_rgPrids) {

        IPropertyType* prop = nullptr;

        switch(propID.type()) {
            case PropertyIDType::NoData:
            case PropertyIDType::Bool:
            case PropertyIDType::ObjectID:
            case PropertyIDType::ContextID:
            case PropertyIDType::ObjectSpaceID:
                prop = new PropertyType_NoData();
                break;

            case PropertyIDType::ArrayOfObjectIDs:
            case PropertyIDType::ArrayOfObjectSpaceIDs:
            case PropertyIDType::ArrayOfContextIDs:
                prop = new PropertyType_ArrayNumber();
                break;

            case PropertyIDType::OneByteOfData:
                prop = new PropertyType_OneByteOfData();
                break;

            case PropertyIDType::TwoBytesOfData:
                prop = new PropertyType_TwoBytesOfData();
                break;

            case PropertyIDType::FourBytesOfData:
                prop = new PropertyType_FourBytesOfData();
                break;

            case PropertyIDType::EightBytesOfData:
                prop = new PropertyType_EightBytesOfData();
                break;

            case PropertyIDType::FourBytesOfLengthFollowedByData:
                prop = new PropertyType_FourBytesOfLengthFollowedByData();
                break;

            case PropertyIDType::ArrayOfPropertyValues:
                prop = new PropertyType_ArrayOfPropertyValues();
                break;

            case PropertyIDType::PropertySet:
                prop = new PropertyType_PropertySet();
                break;

            default:
                break;
        }

        if( prop != nullptr)
        {
            ds >> *prop;
        }
        m_rgData.push_back(prop);
    }
}

void PropertySet::serialize(QDataStream &ds) const {

    ds << m_cProperties;

    foreach(auto propid : m_rgPrids) {
        ds << propid;
    }

    foreach(IPropertyType* prop : m_rgData) {
        ds << *prop;
    }
}

void PropertySet::toDebugString(QDebug dbg) const {}

PropertySet::PropertySet() : m_cProperties{} {}

QDataStream &operator<<(QDataStream &ds, const PropertySet &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, PropertySet &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const PropertySet &obj) {
  obj.toDebugString(dbg);
  return dbg;
}
