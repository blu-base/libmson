#include "ObjectSpaceObjectPropSet.h"
namespace libmson {
namespace priv {


ObjectSpaceObjectPropSet::ObjectSpaceObjectPropSet() {}


ObjectSpaceObjectStreamOfOIDs ObjectSpaceObjectPropSet::getOIDs() const { return m_OIDs; }

ObjectSpaceObjectStreamOfOIDs& ObjectSpaceObjectPropSet::OIDs() { return m_OIDs; }

void ObjectSpaceObjectPropSet::setOIDs(const ObjectSpaceObjectStreamOfOIDs& OIDs) { m_OIDs = OIDs; }

ObjectSpaceObjectStreamOfOSIDs ObjectSpaceObjectPropSet::getOSIDs() const { return m_OSIDs; }

ObjectSpaceObjectStreamOfOSIDs& ObjectSpaceObjectPropSet::OSIDs() { return m_OSIDs; }

void ObjectSpaceObjectPropSet::setOSIDs(const ObjectSpaceObjectStreamOfOSIDs& OSIDs) { m_OSIDs = OSIDs; }

ObjectSpaceObjectStreamOfContextIDs ObjectSpaceObjectPropSet::getContextIDs() const { return m_ContextIDs; }

ObjectSpaceObjectStreamOfContextIDs& ObjectSpaceObjectPropSet::contextIDs() { return m_ContextIDs; }

void ObjectSpaceObjectPropSet::setContextIDs(const ObjectSpaceObjectStreamOfContextIDs& ContextIDs)
{
  m_ContextIDs = ContextIDs;
}

PropertySet ObjectSpaceObjectPropSet::getBody() const { return m_body; }

void ObjectSpaceObjectPropSet::setBody(const PropertySet& body) { m_body = body; }

quint64 ObjectSpaceObjectPropSet::getPaddingLength() const { return m_paddingLength; }

quint64 libmson::priv::ObjectSpaceObjectPropSet::cb() const
{
  return m_OIDs.getSizeInFile() + m_OSIDs.getSizeInFile() + m_ContextIDs.getSizeInFile() + m_body.getSizeInFile() +
         m_paddingLength;
}

libmson::priv::RevisionStoreChunkType libmson::priv::ObjectSpaceObjectPropSet::getType() const
{
  return RevisionStoreChunkType::ObjectSpaceObjectPropSet;
}

} // namespace priv
} // namespace libmson
