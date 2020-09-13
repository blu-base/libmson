#include "GlobalIdTableEndFNDX.h"

namespace MSONcommon {

void GlobalIdTableEndFNDX::deserialize(QDataStream& ds)
{
}

void GlobalIdTableEndFNDX::serialize(QDataStream& ds) const
{
}

void GlobalIdTableEndFNDX::toDebugString(QDebug &dbg) const
{
}


void GlobalIdTableEndFNDX::writeLowLevelXml(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("GlobalIdTableEndFNDX");
    xmlWriter.writeEndElement();
}
} // namespace MSONcommon
