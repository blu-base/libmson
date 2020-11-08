#include "PropertyType_NoData.h"
#include <QDebug>

namespace libmson{
namespace priv{

PropertyType_NoData::PropertyType_NoData() {}

void PropertyType_NoData::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("NoData");
  xmlWriter.writeEndElement();
}

void PropertyType_NoData::deserialize(QDataStream &ds) {}

void PropertyType_NoData::serialize(QDataStream &ds) const {}

void PropertyType_NoData::toDebugString(QDebug &dbg) const {}

} //namespace priv
} // namespace libmson
