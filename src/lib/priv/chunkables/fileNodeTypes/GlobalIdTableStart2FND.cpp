#include "GlobalIdTableStart2FND.h"

namespace libmson{
namespace priv{
void GlobalIdTableStart2FND::deserialize(QDataStream &ds) {}

void GlobalIdTableStart2FND::serialize(QDataStream &ds) const {}

void GlobalIdTableStart2FND::toDebugString(QDebug &dbg) const {
  dbg << "GlobalIdTableStart2FND.";
}

void GlobalIdTableStart2FND::writeLowLevelXml(
    QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("GlobalIdTableStart2FND");
  xmlWriter.writeEndElement();
}

quint64 GlobalIdTableStart2FND::getSizeInFile() const { return sizeInFile; }

} //namespace priv
} // namespace libmson
