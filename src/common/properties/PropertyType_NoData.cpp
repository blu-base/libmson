#include "PropertyType_NoData.h"
#include <QDebug>

namespace MSONcommon {

PropertyType_NoData::PropertyType_NoData() {}

void PropertyType_NoData::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("NoData");
  xmlWriter.writeEndElement();
}

void PropertyType_NoData::deserialize(QDataStream &ds) {}

void PropertyType_NoData::serialize(QDataStream &ds) const {}

void PropertyType_NoData::toDebugString(QDebug dbg) const {}

} // namespace MSONcommon
