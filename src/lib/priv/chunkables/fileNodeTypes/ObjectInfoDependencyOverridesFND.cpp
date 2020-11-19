#include "ObjectInfoDependencyOverridesFND.h"
#include "../FileNode.h"

namespace libmson {
namespace priv {

ObjectInfoDependencyOverridesFND::ObjectInfoDependencyOverridesFND(
    FileNode_WPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode))
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
  /// \todo figure out how to deal with ObjectInfoDependencyOverridesFND
  qWarning(
      "Trying to set ObjectInfoDependencyOverrideData, which is unimplemented");
  //  m_data = value;
}

void ObjectInfoDependencyOverridesFND::setData(
    ObjectInfoDependencyOverrideData_WPtr_t remote)
{
  m_ref = remote;
}

quint64 ObjectInfoDependencyOverridesFND::getSizeInFile() const
{
  return m_parent.lock()->getFileNodeChunkReferenceSize() +
         m_data.getSizeInFile();
}

ObjectInfoDependencyOverrideData_WPtr_t
ObjectInfoDependencyOverridesFND::getRef() const
{
  return m_ref;
}

void ObjectInfoDependencyOverridesFND::setRef(
    const ObjectInfoDependencyOverrideData_WPtr_t value)
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
