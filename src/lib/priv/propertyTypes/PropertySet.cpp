#include "PropertySet.h"
#include <algorithm>

#include "PropertyType_ArrayNumber.h"
#include "PropertyType_ArrayOfPropertyValues.h"
#include "PropertyType_EightBytesOfData.h"
#include "PropertyType_FourBytesOfData.h"
#include "PropertyType_FourBytesOfLengthFollowedByData.h"
#include "PropertyType_NoData.h"
#include "PropertyType_ObjectID.h"
#include "PropertyType_OneByteOfData.h"
#include "PropertyType_PropertySet.h"
#include "PropertyType_TwoBytesOfData.h"

#include "../utils/Helper.h"

//#include "../simpleTypes/BodyTextAlignment.h"
//#include "../simpleTypes/ColorRef.h"
//#include "../simpleTypes/FileTime.h"
//#include "../simpleTypes/LCID.h"
//#include "../simpleTypes/LayoutAlignment.h"
//#include "../simpleTypes/ListMSAAIndex.h"
//#include "../simpleTypes/NoteTagShape.h"
//#include "../simpleTypes/PageSize.h"
//#include "../simpleTypes/Time32.h"

namespace libmson {
namespace priv {

PropertySet::PropertySet() : m_cProperties{} {}

quint16 PropertySet::cProperties() const { return m_cProperties; }

void PropertySet::setCProperties(const quint16& cProperties)
{
  m_cProperties = cProperties;
}

std::vector<PropertyID> PropertySet::rgPrids() const { return m_rgPrids; }

void PropertySet::setRgPrids(const std::vector<PropertyID>& rgPrids)
{
  m_rgPrids = rgPrids;
}

std::vector<IPropertyType_SPtr_t> PropertySet::rgData() const
{
  return m_rgData;
}

void PropertySet::setRgData(const std::vector<IPropertyType_SPtr_t>& rgData)
{
  m_rgData = rgData;
}

quint64 PropertySet::getSizeInFile() const
{

  // compute m_rgData size


  quint64 dataSize = std::accumulate(
      m_rgData.begin(), m_rgData.end(), 0,
      [&](quint64 a, const std::shared_ptr<IPropertyType>& b) {
        return a + b->getSizeInFile();
      });


  //  quint64 dataSize = 0;
  //  for (const auto& entry : m_rgData) {
  //    dataSize += entry->getSizeInFile();
  //  }

  return sizeof(m_cProperties) +
         m_rgPrids.size() * PropertyID::getSizeInFile() + dataSize;
}

/// \todo implement propertyset
void PropertySet::deserialize(QDataStream& ds)
{
  ds >> m_cProperties;

  for (quint32 i = 0; i < m_cProperties; i++) {
    PropertyID prid;
    ds >> prid;
    m_rgPrids.push_back(prid);
  }

  for (const auto& propID : m_rgPrids) {
    std::shared_ptr<IPropertyType> prop;

    switch (propID.type()) {
    case PropertyIDType::NoData:
    case PropertyIDType::Bool:
    case PropertyIDType::ContextID:
    case PropertyIDType::ObjectSpaceID:
    case PropertyIDType::ObjectID:
      prop = std::make_shared<PropertyType_NoData>();
      break;

    case PropertyIDType::ArrayOfObjectIDs:
    case PropertyIDType::ArrayOfObjectSpaceIDs:
    case PropertyIDType::ArrayOfContextIDs:
      prop = std::make_shared<PropertyType_ArrayNumber>();
      break;

    case PropertyIDType::OneByteOfData:
      prop = std::make_shared<PropertyType_OneByteOfData>();
      break;

    case PropertyIDType::TwoBytesOfData:
      prop = std::make_shared<PropertyType_TwoBytesOfData>();
      break;

    case PropertyIDType::FourBytesOfData:
      prop = std::make_shared<PropertyType_FourBytesOfData>();
      break;

    case PropertyIDType::EightBytesOfData:
      prop = std::make_shared<PropertyType_EightBytesOfData>();
      break;

    case PropertyIDType::FourBytesOfLengthFollowedByData:
      prop = std::make_shared<PropertyType_FourBytesOfLengthFollowedByData>();
      break;

    case PropertyIDType::ArrayOfPropertyValues:
      prop = std::make_shared<PropertyType_ArrayOfPropertyValues>();
      break;

    case PropertyIDType::PropertySet:
      prop = std::make_shared<PropertyType_PropertySet>();
      break;

    default:
      break;
    }

    //        if (propID.type() == PropertyIDType::PropertySet) {
    //            qWarning() << "Encountered PropertySetElement of type
    //            PropertySet"; break;
    //        }

    //    if (propID.type() == PropertyIDType::InvalidType) {
    //      qWarning() << "Encountered invalid PropertyType";
    //      break;
    //    }

    if (prop != nullptr) {
      ds >> *prop;
    }
    m_rgData.push_back(prop);
  }
}

void PropertySet::serialize(QDataStream& ds) const
{

  ds << m_cProperties;

  for (const auto& propid : m_rgPrids) {
    ds << propid;
  }

  for (const auto& prop : m_rgData) {
    ds << *prop;
  }
}

} // namespace priv
} // namespace libmson
