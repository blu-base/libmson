#include "ObjectGroupEndFND.h"

ObjectGroupEndFND::ObjectGroupEndFND() {}

void ObjectGroupEndFND::deserialize(QDataStream &ds) {}

void ObjectGroupEndFND::serialize(QDataStream &ds) const {}

void ObjectGroupEndFND::toDebugString(QDebug dbg) const {
  dbg << "ObjectGroupEndFND.\n";
}

void ObjectGroupEndFND::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ObjectGroupEndFND");
  xmlWriter.writeEndElement();
}
