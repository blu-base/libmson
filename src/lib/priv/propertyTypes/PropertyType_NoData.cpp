#include "PropertyType_NoData.h"

namespace libmson {
namespace priv {

PropertyType_NoData::PropertyType_NoData() {}


void PropertyType_NoData::deserialize(QDataStream& ds) {}

void PropertyType_NoData::serialize(QDataStream& ds) const {}

// void PropertyType_NoData::toDebugString(QDebug &dbg) const {}

// void PropertyType_NoData::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const
// {
//  xmlWriter.writeStartElement("NoData");
//  xmlWriter.writeEndElement();
//}

} // namespace priv
} // namespace libmson
