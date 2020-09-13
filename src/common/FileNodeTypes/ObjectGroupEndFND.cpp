#include "ObjectGroupEndFND.h"

namespace MSONcommon {
void ObjectGroupEndFND::deserialize(QDataStream &ds) {}

void ObjectGroupEndFND::serialize(QDataStream &ds) const {}

void ObjectGroupEndFND::toDebugString(QDebug &dbg) const {
  dbg << "ObjectGroupEndFND.\n";
}

void ObjectGroupEndFND::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ObjectGroupEndFND");
  xmlWriter.writeEndElement();
}

} // namespace MSONcommon
