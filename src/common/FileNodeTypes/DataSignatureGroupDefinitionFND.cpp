#include "DataSignatureGroupDefinitionFND.h"

DataSignatureGroupDefinitionFND::DataSignatureGroupDefinitionFND()
    : m_dataSignatureGroup(ExtendedGUID())
{

}

ExtendedGUID DataSignatureGroupDefinitionFND::dataSignatureGroup() const
{
    return m_dataSignatureGroup;
}

void DataSignatureGroupDefinitionFND::setDataSignatureGroup(const ExtendedGUID& DataSignatureGroup)
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

void DataSignatureGroupDefinitionFND::toDebugString(QDebug dbg) const
{
    dbg << " DataSignatureGroupDefinitionFND: \n"
        << " m_dataSignatureGroup:  " << m_dataSignatureGroup << '\n';
}
