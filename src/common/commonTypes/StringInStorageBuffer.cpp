#include "StringInStorageBuffer.h"


StringInStorageBuffer::StringInStorageBuffer()
{

}

QString StringInStorageBuffer::getStringData() const
{
    return StringData;
}

void StringInStorageBuffer::setStringData(const QString& value)
{
    StringData = value;
}

/**
 * @brief StringInStorageBuffer::deserialize
 * @param ds
 *
 * \todo check which endianess to be used here
 */
void StringInStorageBuffer::deserialize(QDataStream& ds)
{
    ds >> cch;

    QByteArray rawstring = QByteArray(cch*2,Qt::Uninitialized);

    ds.readRawData(rawstring.data(),cch*2);

    StringData = QString(rawstring);

}

void StringInStorageBuffer::serialize(QDataStream& ds) const
{

}

void StringInStorageBuffer::toDebugString(QDebug dbg) const
{

}

quint32 StringInStorageBuffer::getCch() const
{
    return cch;
}

void StringInStorageBuffer::setCch(const quint32& value)
{
    cch = value;
}
