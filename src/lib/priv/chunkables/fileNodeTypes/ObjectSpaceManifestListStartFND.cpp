#include "ObjectSpaceManifestListStartFND.h"

namespace libmson {
namespace priv {

ObjectSpaceManifestListStartFND::ObjectSpaceManifestListStartFND(
    RSChunkContainer_WPtr_t parentFileNode)
    : IFileNodeType(parentFileNode)
{
}

ExtendedGUID ObjectSpaceManifestListStartFND::gosid() const { return m_gosid; }

void ObjectSpaceManifestListStartFND::setGosid(const ExtendedGUID& value)
{
  m_gosid = value;
}

quint64 ObjectSpaceManifestListStartFND::getSizeInFile() const
{
  return ExtendedGUID::getSizeInFile();
}

void ObjectSpaceManifestListStartFND::deserialize(QDataStream& ds)
{
  ds >> m_gosid;
}

void ObjectSpaceManifestListStartFND::serialize(QDataStream& ds) const
{
  ds << m_gosid;
}

// void ObjectSpaceManifestListStartFND::toDebugString(QDebug& dbg) const
//{
//  dbg << " ObjectSpaceManifestListStartFND: gosid: " << m_gosid << '\n';
//}

// void ObjectSpaceManifestListStartFND::writeLowLevelXml(
//    QXmlStreamWriter& xmlWriter) const
//{
//  xmlWriter.writeStartElement("ObjectSpaceManifestListStartFND");
//  xmlWriter << m_gosid;
//  xmlWriter.writeEndElement();
//}

} // namespace priv
} // namespace libmson
