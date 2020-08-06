#include "ObjectGroupStartFND.h"


ObjectGroupStartFND::ObjectGroupStartFND()
    : m_oid(ExtendedGUID())
{

}

ExtendedGUID ObjectGroupStartFND::oid() const
{
    return m_oid;
}

void ObjectGroupStartFND::setOid(const ExtendedGUID &oid)
{
    m_oid = oid;
}


void ObjectGroupStartFND::deserialize(QDataStream& ds)
{
    ds >> m_oid;
}

void ObjectGroupStartFND::serialize(QDataStream& ds) const
{
    ds << m_oid;
}

void ObjectGroupStartFND::toDebugString(QDebug dbg) const
{
    dbg << " ObjectGroupStartFND: \n"
        << " oid:  " << m_oid << '\n';
}


void ObjectGroupStartFND::generateXml(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("ObjectGroupStartFND");

    xmlWriter.writeStartElement("oid");
    xmlWriter.writeCharacters(m_oid.toString());
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
}
