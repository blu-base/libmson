#include "ObjectSpaceManifestListStartFND.h"

namespace libmson {
namespace priv {

ObjectSpaceManifestListStartFND::ObjectSpaceManifestListStartFND(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode))
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

// void ObjectSpaceManifestListStartFND::writeLowLevelXml(
//    QXmlStreamWriter& xmlWriter) const
//{
//  xmlWriter.writeStartElement("ObjectSpaceManifestListStartFND");
//  xmlWriter << m_gosid;
//  xmlWriter.writeEndElement();
//}

} // namespace priv
} // namespace libmson
