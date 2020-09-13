#include "RevisionManifestEndFND.h"

namespace MSONcommon {

void RevisionManifestEndFND::deserialize(QDataStream &ds) {}

void RevisionManifestEndFND::serialize(QDataStream &ds) const {}

void RevisionManifestEndFND::toDebugString(QDebug &dbg) const {
  dbg << "RevisionManifestEndFND.\n";
}


void RevisionManifestEndFND::writeLowLevelXml(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("RevisionManifestEndFND");
    xmlWriter.writeEndElement();
}

} // namespace MSONcommon
