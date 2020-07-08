#include "ObjectInfoDependencyOverride8.h"

#include <QDataStream>
#include <QDebug>

ObjectInfoDependencyOverride8::ObjectInfoDependencyOverride8()
{

}

QDataStream& operator<<(QDataStream& ds, const ObjectInfoDependencyOverride8& obj)
{
    obj.serialize(ds);
    return ds;
}

QDataStream& operator>>(QDataStream& ds, ObjectInfoDependencyOverride8& obj)
{
    obj.deserialize(ds);
    return ds;
}

QDebug operator<<(QDebug dbg, const ObjectInfoDependencyOverride8& obj)
{
    obj.toDebugString(dbg);
    return dbg;
}

CompactID ObjectInfoDependencyOverride8::oid() const
{
    return m_oid;
}

void ObjectInfoDependencyOverride8::setOid(const CompactID& oid)
{
    m_oid = oid;
}

quint8 ObjectInfoDependencyOverride8::cRef() const
{
    return m_cRef;
}

void ObjectInfoDependencyOverride8::setCRef(const quint8& cRef)
{
    m_cRef = cRef;
}

void ObjectInfoDependencyOverride8::deserialize(QDataStream& ds)
{
ds >> m_oid;
ds >> m_cRef;
}

void ObjectInfoDependencyOverride8::serialize(QDataStream& ds) const
{
    ds << m_oid;
    ds << m_cRef;
}

void ObjectInfoDependencyOverride8::toDebugString(QDebug dbg) const
{
    dbg << "ObjectInfoDependencyOverride8:\n"
        << "oid:  " << m_oid << '\n'
        << "cRef: " << m_cRef << '\n';
}




