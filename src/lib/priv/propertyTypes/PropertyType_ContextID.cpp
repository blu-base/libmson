#include "PropertyType_ContextID.h"

namespace libmson {
namespace priv {

CompactID PropertyType_ContextID::data() const { return m_data; }

void PropertyType_ContextID::setData(const CompactID& data) { m_data = data; }

PropertyType_ContextID::PropertyType_ContextID() {}

void PropertyType_ContextID::deserialize(QDataStream& ds) { ds >> m_data; }

void PropertyType_ContextID::serialize(QDataStream& ds) const { ds << m_data; }

// void PropertyType_ContextID::toDebugString(QDebug &dbg) const {}


// void PropertyType_ContextID::writeLowLevelXml(QXmlStreamWriter& xmlWriter)
// const
//{
//    xmlWriter.writeStartElement("ContextID");
//    xmlWriter << m_data;
//    xmlWriter.writeEndElement();
//}

} // namespace priv
} // namespace libmson
