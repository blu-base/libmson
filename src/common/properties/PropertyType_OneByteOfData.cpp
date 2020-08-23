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

void PropertyType_OneByteOfData::generateXml(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("OneByteOfData");
    xmlWriter.writeCharacters(m_data.toHex());
    xmlWriter.writeEndElement();
}

PropertyType_OneByteOfData::PropertyType_OneByteOfData()
{

}


void PropertyType_OneByteOfData::deserialize(QDataStream& ds)
{

    char* rawBody = new char[1];
    ds.readRawData(rawBody, 1);

    m_data = QByteArray(QByteArray::fromRawData(rawBody, 1));

}

void PropertyType_OneByteOfData::serialize(QDataStream& ds) const
{
    ds << m_data;
}

void PropertyType_OneByteOfData::toDebugString(QDebug dbg) const
{
}
