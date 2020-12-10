#include "ObjectInfoDependencyOverridesFND.h"
#include "../FileNode.h"

namespace libmson {
namespace priv {

ObjectInfoDependencyOverridesFND::ObjectInfoDependencyOverridesFND(
    FileNode_SPtr_t parentFileNode)
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
    ObjectInfoDependencyOverrideData_SPtr_t remote)
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
    const ObjectInfoDependencyOverrideData_SPtr_t value)
{
  m_ref = value;
}

} // namespace priv
} // namespace libmson
