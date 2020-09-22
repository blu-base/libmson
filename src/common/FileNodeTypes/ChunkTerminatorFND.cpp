#include "ChunkTerminatorFND.h"

namespace MSONcommon {

void ChunkTerminatorFND::deserialize(QDataStream &ds) {}

void ChunkTerminatorFND::serialize(QDataStream &ds) const {}

void ChunkTerminatorFND::toDebugString(QDebug &dbg) const {
  dbg << "ChunkTerminatorFND.\n";
}

void ChunkTerminatorFND::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ChunkTerminatorFND");
  xmlWriter.writeEndElement();
}

quint64 MSONcommon::ChunkTerminatorFND::getSizeInFile() const { return sizeInFile; }

} // namespace MSONcommon
