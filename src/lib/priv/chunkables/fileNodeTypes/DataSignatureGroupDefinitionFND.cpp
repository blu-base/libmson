#include "DataSignatureGroupDefinitionFND.h"

#include <utility>

namespace libmson {
namespace priv {

DataSignatureGroupDefinitionFND::DataSignatureGroupDefinitionFND(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode)),
      m_dataSignatureGroup(ExtendedGUID())
{
}

ExtendedGUID DataSignatureGroupDefinitionFND::getDataSignatureGroup() const
{
  return m_dataSignatureGroup;
}

void DataSignatureGroupDefinitionFND::setDataSignatureGroup(
    const ExtendedGUID& DataSignatureGroup)
{
  m_dataSignatureGroup = DataSignatureGroup;
}

void DataSignatureGroupDefinitionFND::deserialize(QDataStream& ds)
{
  ds >> m_dataSignatureGroup;
}

void DataSignatureGroupDefinitionFND::serialize(QDataStream& ds) const
{
  ds << m_dataSignatureGroup;
}

quint64 DataSignatureGroupDefinitionFND::getSizeInFile() const
{
  return sizeInFile;
}

} // namespace priv
} // namespace libmson
