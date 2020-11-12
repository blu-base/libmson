#include "GlobalIdTableEndFNDX.h"

namespace libmson {
namespace priv {

void GlobalIdTableEndFNDX::deserialize(QDataStream& ds) {}

void GlobalIdTableEndFNDX::serialize(QDataStream& ds) const {}

// void GlobalIdTableEndFNDX::toDebugString(QDebug &dbg) const
//{
//}


// void GlobalIdTableEndFNDX::writeLowLevelXml(QXmlStreamWriter& xmlWriter)
// const
//{
//    xmlWriter.writeStartElement("GlobalIdTableEndFNDX");
//    xmlWriter.writeEndElement();
//}

GlobalIdTableEndFNDX::GlobalIdTableEndFNDX(
    RSChunkContainer_WPtr_t parentFileNode)
    : IFileNodeType(parentFileNode)
{
}

quint64 GlobalIdTableEndFNDX::getSizeInFile() const { return 0; }
} // namespace priv
} // namespace libmson
