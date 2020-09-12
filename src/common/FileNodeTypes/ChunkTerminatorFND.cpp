#include "ChunkTerminatorFND.h"

namespace MSONcommon {


void ChunkTerminatorFND::deserialize(QDataStream &ds) {}

void ChunkTerminatorFND::serialize(QDataStream &ds) const {}

void ChunkTerminatorFND::toDebugString(QDebug dbg) const {
  dbg << "ChunkTerminatorFND.\n";
}

void ChunkTerminatorFND::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ChunkTerminatorFND");
  xmlWriter.writeEndElement();
}

} // namespace MSONcommon

