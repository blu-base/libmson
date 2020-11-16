#include "ObjectSpaceObjectPropSet.h"
namespace libmson {
namespace priv {


ObjectSpaceObjectPropSet::ObjectSpaceObjectPropSet(
    const quint64 initialStp, const quint64 initialCb)
    : Chunkable(initialStp, initialCb)
{
}


ObjectSpaceObjectStreamOfOIDs ObjectSpaceObjectPropSet::getOIDs() const
{
  return m_OIDs;
}

ObjectSpaceObjectStreamOfOIDs& ObjectSpaceObjectPropSet::OIDs()
{
  return m_OIDs;
}

void ObjectSpaceObjectPropSet::setOIDs(
    const ObjectSpaceObjectStreamOfOIDs& OIDs)
{
  m_OIDs = OIDs;
}

ObjectSpaceObjectStreamOfOSIDs ObjectSpaceObjectPropSet::getOSIDs() const
{
  return m_OSIDs;
}

ObjectSpaceObjectStreamOfOSIDs& ObjectSpaceObjectPropSet::OSIDs()
{
  return m_OSIDs;
}

void ObjectSpaceObjectPropSet::setOSIDs(
    const ObjectSpaceObjectStreamOfOSIDs& OSIDs)
{
  m_OSIDs = OSIDs;
}

ObjectSpaceObjectStreamOfContextIDs
ObjectSpaceObjectPropSet::getContextIDs() const
{
  return m_ContextIDs;
}

ObjectSpaceObjectStreamOfContextIDs& ObjectSpaceObjectPropSet::contextIDs()
{
  return m_ContextIDs;
}

void ObjectSpaceObjectPropSet::setContextIDs(
    const ObjectSpaceObjectStreamOfContextIDs& ContextIDs)
{
  m_ContextIDs = ContextIDs;
}

PropertySet ObjectSpaceObjectPropSet::getBody() const { return m_body; }

void ObjectSpaceObjectPropSet::setBody(const PropertySet& body)
{
  m_body = body;
}

quint64 ObjectSpaceObjectPropSet::getPaddingLength() const
{

  quint8 modulo = unPaddedCb() % 8;

  if (modulo > 0) {
    return 8 - modulo;
  }

  return 0;
}

quint64 ObjectSpaceObjectPropSet::unPaddedCb() const
{
  quint32 size = m_OIDs.getSizeInFile();

  if (m_OIDs.header().OsidStream_isNotPresent() == false) {
    size += m_OSIDs.getSizeInFile();


    if (m_OSIDs.header().ExtendedStream_isPresent() == true) {
      size += m_ContextIDs.getSizeInFile();
    }
  }

  size += m_body.getSizeInFile();

  return size;
}

quint64 libmson::priv::ObjectSpaceObjectPropSet::cb() const
{
  return unPaddedCb() + getPaddingLength();
}

libmson::priv::RevisionStoreChunkType
libmson::priv::ObjectSpaceObjectPropSet::getType() const
{
  return RevisionStoreChunkType::ObjectSpaceObjectPropSet;
}

} // namespace priv
} // namespace libmson
