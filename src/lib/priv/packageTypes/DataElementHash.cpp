#include "DataElementHash.h"

#include "dataTypes/CompactUInt64.h"

namespace libmson {
namespace fsshttpb {

DataElementHash::DataElementHash() : m_scheme() {}

quint64 DataElementHash::getScheme() const { return m_scheme; }

void DataElementHash::setScheme(const quint64 scheme) { m_scheme = scheme; }

QByteArray DataElementHash::getData() const { return m_data; }

void DataElementHash::setData(const QByteArray& data) { m_data = data; }

quint64 DataElementHash::strObjBody_cb() const
{

  return CompactUInt64::getSizeInFile(m_scheme) +
         CompactUInt64::getSizeInFile(m_data.size()) + m_data.size();
}

quint64 DataElementHash::cbNextHeader() const
{
  return strObjBody_cb();
}

StreamObjectType DataElementHash::getType() const
{
  return StreamObjectType::DataElementHash;
}

void DataElementHash::push_back(IStreamObject_SPtr_t& obj) { Q_UNUSED(obj); }

IStreamObj_It_t
DataElementHash::insert(IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(pos);
  Q_UNUSED(obj);
  m_children.clear();
  return m_children.end();
}

void DataElementHash::deserializeStrObj(QDataStream& ds)
{
  CompactUInt64 val;
  ds >> val;
  m_scheme = val.getValue();

  ds >> val;
  m_data = ds.device()->read(val.getValue());
}

void DataElementHash::serializeStrObj(QDataStream& ds) const
{
  ds << CompactUInt64(m_scheme);
  ds << CompactUInt64(m_data.size());

  ds.writeRawData(m_data.data(), m_data.size());
}


} // namespace fsshttpb
} // namespace libmson
