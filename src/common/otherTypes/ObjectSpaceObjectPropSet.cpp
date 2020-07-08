#include "ObjectSpaceObjectPropSet.h"

ObjectSpaceObjectPropSet::ObjectSpaceObjectPropSet() {}

QDataStream &operator<<(QDataStream &ds, const ObjectSpaceObjectPropSet &obj) {
    obj.serialize(ds);
    return ds;
}

QDataStream &operator>>(QDataStream &ds, ObjectSpaceObjectPropSet &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const ObjectSpaceObjectPropSet &obj) {
  obj.toDebugString(dbg);
  return dbg;
}




ObjectSpaceObjectStreamOfOIDs ObjectSpaceObjectPropSet::OIDs() const
{
    return m_OIDs;
}

void ObjectSpaceObjectPropSet::setOIDs(const ObjectSpaceObjectStreamOfOIDs& OIDs)
{
    m_OIDs = OIDs;
}

ObjectSpaceObjectStreamOfOSIDs ObjectSpaceObjectPropSet::OSIDs() const
{
    return m_OSIDs;
}

void ObjectSpaceObjectPropSet::setOSIDs(const ObjectSpaceObjectStreamOfOSIDs& OSIDs)
{
    m_OSIDs = OSIDs;
}

ObjectSpaceObjectStreamOfContextIDs ObjectSpaceObjectPropSet::ContextIDs() const
{
    return m_ContextIDs;
}

void ObjectSpaceObjectPropSet::setContextIDs(const ObjectSpaceObjectStreamOfContextIDs& ContextIDs)
{
    m_ContextIDs = ContextIDs;
}

PropertySet ObjectSpaceObjectPropSet::body() const
{
    return m_body;
}

void ObjectSpaceObjectPropSet::setBody(const PropertySet& body)
{
    m_body = body;
}

void ObjectSpaceObjectPropSet::deserialize(QDataStream& ds)
{
    quint64 propSetstart = ds.device()->pos();
    ds >> m_OIDs;

    if (m_OIDs.header().OsidStream_isNotPresent() == false) {
        ds >> m_OSIDs;

        if (m_OSIDs.header().ExtendedStream_isPresent() == true) {
            ds >> m_ContextIDs;
        }
    }
    ds >> m_body;

    //
    m_paddingLength = 8 - (ds.device()->pos() - propSetstart) % 8;

    ds.skipRawData(m_paddingLength);
}

void ObjectSpaceObjectPropSet::serialize(QDataStream& ds) const
{
    ds << m_OIDs;
    if (m_OIDs.header().OsidStream_isNotPresent() == false) {
        ds << m_OSIDs;

        if (m_OSIDs.header().ExtendedStream_isPresent() == true) {
            ds << m_ContextIDs;
        }
    }
    ds << m_body;

    QByteArray padding;

    ds << padding.append('\0',m_paddingLength);
}

void ObjectSpaceObjectPropSet::toDebugString(QDebug dbg) const
{
    dbg << "ObjectSpaceObjectPropSet:\n";
    dbg << m_OIDs;

    if (m_OIDs.header().OsidStream_isNotPresent() == false) {
        dbg <<  m_OSIDs;

        if (m_OSIDs.header().ExtendedStream_isPresent() == true) {
            dbg << m_ContextIDs;
        }
    }
}

