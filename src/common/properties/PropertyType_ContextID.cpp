#include "PropertyType_ContextID.h"

#include <QDataStream>
#include <QDebug>

namespace MSONcommon {

CompactID PropertyType_ContextID::data() const { return m_data; }

void PropertyType_ContextID::setData(const CompactID &data) { m_data = data; }

PropertyType_ContextID::PropertyType_ContextID() {}

void PropertyType_ContextID::deserialize(QDataStream &ds) { ds >> m_data; }

void PropertyType_ContextID::serialize(QDataStream &ds) const { ds << m_data; }

void PropertyType_ContextID::toDebugString(QDebug dbg) const {}


void PropertyType_ContextID::generateXml(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("ContextID");
    m_data.generateXml(xmlWriter);
    xmlWriter.writeEndElement();
}

} // namespace MSONcommon
