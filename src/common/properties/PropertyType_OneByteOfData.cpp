#include "PropertyType_OneByteOfData.h"

#include <QDataStream>
#include <QDebug>

QByteArray PropertyType_OneByteOfData::data() const
{
    return m_data;
}

void PropertyType_OneByteOfData::setData(const QByteArray& data)
{
    m_data = data;
}

PropertyType_OneByteOfData::PropertyType_OneByteOfData()
{

}


void PropertyType_OneByteOfData::deserialize(QDataStream& ds)
{

    char* raw;
    uint len = 1;
    ds.readBytes(raw,len);
    m_data = QByteArray(raw,len);
}

void PropertyType_OneByteOfData::serialize(QDataStream& ds) const
{
    ds << m_data;
}

void PropertyType_OneByteOfData::toDebugString(QDebug dbg) const
{
}
