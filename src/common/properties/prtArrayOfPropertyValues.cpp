#include "prtArrayOfPropertyValues.h"
#include "../commonTypes/Enums.h"
#include <QDataStream>
#include <QDebug>

#include "PropertyType_PropertySet.h"


prtArrayOfPropertyValues::prtArrayOfPropertyValues() {}

QDataStream &operator<<(QDataStream &ds, const prtArrayOfPropertyValues &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, prtArrayOfPropertyValues &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const prtArrayOfPropertyValues &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

quint32 prtArrayOfPropertyValues::cProperties() const { return m_cProperties; }

void prtArrayOfPropertyValues::setCProperties(const quint32 &cProperties) {
  m_cProperties = cProperties;
}

PropertyID prtArrayOfPropertyValues::prid() const { return m_prid; }

void prtArrayOfPropertyValues::setPrid(const PropertyID &prid) {
  m_prid = prid;
}

QByteArray prtArrayOfPropertyValues::Data() const { return m_Data; }

void prtArrayOfPropertyValues::setData(const QByteArray &Data) {
  m_Data = Data;
}

std::vector<IPropertyType *> prtArrayOfPropertyValues::dataVector() const {
  return m_dataVector;
}

void prtArrayOfPropertyValues::setDataVector(
    const std::vector<IPropertyType *> &dataVector) {
  m_dataVector = dataVector;
}

void prtArrayOfPropertyValues::deserialize(QDataStream &ds) {
  ds >> m_cProperties;

  if (m_cProperties != 0) {
    ds >> m_prid;

    /// \todo implement

    IPropertyType *prop;
    switch (m_prid.type()) {
    case PropertyIDType::ArrayOfContextIDs:
      prop = new PropertyType_ArrayOfContextIDs();
      break;
    case PropertyIDType::ArrayOfObjectIDs:
      prop = new PropertyType_ArrayOfObjectIDs();
      break;
    case PropertyIDType::ArrayOfObjectSpaceIDs:
      prop = new PropertyType_ArrayOfObjectSpaceIDs();
      break;
    case PropertyIDType::ArrayOfPropertyValues:
      prop = new PropertyType_ArrayOfPropertyValues();
      break;
    case PropertyIDType::FourBytesOfLengthFollowedByData:
      prop = new PropertyType_FourBytesOfLengthFollowedByData();
      break;
    case PropertyIDType::Bool:
      prop = new PropertyType_Bool();
      break;
    case PropertyIDType::ContextID:
      prop = new PropertyType_ContextID();
      break;
    case PropertyIDType::EightBytesOfData:
      prop = new PropertyType_EightBytesOfData();
      break;
    case PropertyIDType::FourBytesOfData:
      prop = new PropertyType_FourBytesOfData();
      break;
    case PropertyIDType::NoData:
      prop = new PropertyType_NoData();
      break;
    case PropertyIDType::ObjectID:
      prop = new PropertyType_ObjectID();
      break;
    case PropertyIDType::ObjectSpaceID:
      prop = new PropertyType_ObjectSpaceID();
      break;
    case PropertyIDType::OneByteOfData:
      prop = new PropertyType_OneByteOfData();
      break;
    case PropertyIDType::PropertySet:
      prop = new PropertyType_PropertySet();
      break;
    case PropertyIDType::TwoBytesOfData:
      prop = new PropertyType_TwoBytesOfData();
      break;
    }
    for (size_t i{0}; i < m_cProperties; i++) {
      ds >> *prop;
      m_dataVector.push_back(prop);
    }
  }
}

void prtArrayOfPropertyValues::serialize(QDataStream &ds) const {}

void prtArrayOfPropertyValues::toDebugString(QDebug dbg) const {}
