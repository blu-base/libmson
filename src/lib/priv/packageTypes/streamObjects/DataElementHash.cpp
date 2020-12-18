#include "DataElementHash.h"

namespace libmson {
namespace packStore {
namespace streamObj {

DataElementHash::DataElementHash() : m_scheme() {}

quint64 DataElementHash::getScheme() const { return m_scheme; }

void DataElementHash::setScheme(const quint64& scheme) { m_scheme = scheme; }

BinaryItem DataElementHash::getData() const { return m_data; }

void DataElementHash::setData(const BinaryItem& data) { m_data = data; }


void DataElementHash::deserialize(QDataStream& ds)
{

  StreamObjectHeader header;
  ds >> header;

  if (header.getType() != getType()) {
    qFatal("Trying to deserialze StreamObject of incorrect header type "
           "(DataElementHash)");
  }

  qint64 origPos = ds.device()->pos();

  CompactUInt64 scheme;
  ds >> scheme;
  m_scheme = scheme.getValue();

  ds >> m_data;

  if ((origPos + header.getLength()) != (quint64)ds.device()->pos()) {
    qFatal("Something went wrong parsing DataElementHash");
  }
}

void DataElementHash::serialize(QDataStream& ds) const
{

  StreamObjectHeader header(getType(), body_cb());

  ds << header;

  CompactUInt64 scheme(m_scheme);
  ds << scheme;

  ds << m_data;
}

quint64 DataElementHash::body_cb() const
{
  return CompactUInt64::getSizeInFile(m_scheme) + m_data.getSizeInFile();
}

StreamObjectType DataElementHash::getType() const
{
  return StreamObjectType::DataElementHash;
}


} // namespace streamObj
} // namespace packStore
} // namespace libmson
