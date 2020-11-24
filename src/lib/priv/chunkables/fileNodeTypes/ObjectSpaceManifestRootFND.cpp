#include "ObjectSpaceManifestRootFND.h"

namespace libmson {
namespace priv {

ObjectSpaceManifestRootFND::ObjectSpaceManifestRootFND(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode))
{
}

ExtendedGUID ObjectSpaceManifestRootFND::getGosidRoot() const
{
  return m_gosidRoot;
}

void ObjectSpaceManifestRootFND::setGosidRoot(const ExtendedGUID& value)
{
  m_gosidRoot = value;
}

quint64 ObjectSpaceManifestRootFND::getSizeInFile() const
{
  return ExtendedGUID::getSizeInFile();
}

void ObjectSpaceManifestRootFND::deserialize(QDataStream& ds)
{
  ds >> m_gosidRoot;
}

void ObjectSpaceManifestRootFND::serialize(QDataStream& ds) const
{
  ds << m_gosidRoot;
}

// void ObjectSpaceManifestRootFND::toDebugString(QDebug &dbg) const {
//  dbg << " ObjectSpaceManifestRootFND:\n"
//      << " gosidRoot: " << m_gosidRoot << '\n';
//}

// void ObjectSpaceManifestRootFND::writeLowLevelXml(
//    QXmlStreamWriter &xmlWriter) const {
//  xmlWriter.writeStartElement("ObjectSpaceManifestRootFND");

//  xmlWriter << m_gosidRoot;

//  xmlWriter.writeEndElement();
//}

} // namespace priv
} // namespace libmson
