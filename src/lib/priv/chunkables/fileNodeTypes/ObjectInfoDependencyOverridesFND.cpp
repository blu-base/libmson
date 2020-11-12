#include "ObjectInfoDependencyOverridesFND.h"
#include "../FileNode.h"

namespace libmson {
namespace priv {

ObjectInfoDependencyOverridesFND::ObjectInfoDependencyOverridesFND(
    RSChunkContainer_WPtr_t parentFileNode)
    : IFileNodeType(parentFileNode)
{
}

ObjectInfoDependencyOverrideData
ObjectInfoDependencyOverridesFND::getData() const
{
  return m_data;
}

void ObjectInfoDependencyOverridesFND::setData(
    const ObjectInfoDependencyOverrideData& value)
{
  m_data = value;
}

void ObjectInfoDependencyOverridesFND::setData(RSChunkContainer_WPtr_t remote)
{
  m_ref = remote;
}

quint64 ObjectInfoDependencyOverridesFND::getSizeInFile() const
{
  return std::static_pointer_cast<FileNode>(m_parent.lock()->getContent())
             ->getFileNodeChunkReferenceSize() +
         m_data.getSizeInFile();
}

RSChunkContainer_WPtr_t ObjectInfoDependencyOverridesFND::getRef() const
{
  return m_ref;
}

void ObjectInfoDependencyOverridesFND::setRef(
    const RSChunkContainer_WPtr_t value)
{
  m_ref = value;
}

///**
// * @brief ObjectInfoDependencyOverridesFND::deserialize
// * @param ds
// *
// * \todo check if device/seek stuff is working
// */
// void ObjectInfoDependencyOverridesFND::deserialize(QDataStream &ds) {
//  ds >> m_ref;

//  if (m_ref.is_fcrNil()) {
//    ds >> m_data;
//  } else {
//    quint64 currentloc = ds.device()->pos();
//    ds.device()->seek(m_ref.stp());
//    ds >> m_data;
//    ds.device()->seek(currentloc);
//  }
//}

///**
// * @brief ObjectInfoDependencyOverridesFND::serialize
// * @param ds
// *
// * \todo likely contains bugs
// * \todo ObjectInfoDependencyOverrideData is not yet parsed.
// */
// void ObjectInfoDependencyOverridesFND::serialize(QDataStream &ds) const {
//  ds << m_ref;

//  if (m_ref.is_fcrNil()) {
//    ds << m_data;
//  } else {
//    quint64 currentloc = ds.device()->pos();
//    ds.device()->seek(m_ref.stp());
//    ds << m_data;
//    ds.device()->seek(currentloc);
//  }
//}

// void ObjectInfoDependencyOverridesFND::toDebugString(QDebug &dbg) const {
//  dbg << " ObjectInfoDependencyOverridesFND:\n"
//      << " ref: " << m_ref << "data: " << m_data << '\n';
//}

// void ObjectInfoDependencyOverridesFND::writeLowLevelXml(
//    QXmlStreamWriter &xmlWriter) const {
//  xmlWriter.writeStartElement("ObjectInfoDependencyOverridesFND");
//  xmlWriter << m_ref;

//  xmlWriter << m_data;

//  xmlWriter.writeEndElement();
//}

} // namespace priv
} // namespace libmson
