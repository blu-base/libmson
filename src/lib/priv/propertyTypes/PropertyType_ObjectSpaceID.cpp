#include "PropertyType_ObjectSpaceID.h"

#include <QDataStream>
#include <QDebug>

namespace libmson{
namespace priv{

void PropertyType_ObjectSpaceID::writeLowLevelXml(
    QXmlStreamWriter &xmlWriter) const {
    xmlWriter.writeStartElement("ObjectSpaceID");
    xmlWriter.writeEndElement();
}

PropertyType_ObjectSpaceID::PropertyType_ObjectSpaceID() {}

void PropertyType_ObjectSpaceID::deserialize(QDataStream &ds) {}

void PropertyType_ObjectSpaceID::serialize(QDataStream &ds) const {}

void PropertyType_ObjectSpaceID::toDebugString(QDebug &dbg) const {}

} //namespace priv
} // namespace libmson
