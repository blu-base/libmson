#include "DataElementFragment.h"

#include "dataTypes/CompactExtGuid.h"
#include "dataTypes/CompactUInt64.h"

namespace libmson {
namespace fsshttpb {

QByteArray DataElementFragment::getData() const { return m_data; }

void DataElementFragment::setData(const QByteArray& data) { m_data = data; }

DataElementFragment::DataElementFragment() : m_size(0), m_fileChunkStart(0) {}

priv::ExtendedGUID DataElementFragment::getExtendedGuid() const
{
  return m_extendedGuid;
}

void DataElementFragment::setExtendedGuid(
    const priv::ExtendedGUID& extendedGuid)
{
  m_extendedGuid = extendedGuid;
}

quint64 DataElementFragment::getSize() const { return m_size; }

void DataElementFragment::setSize(const quint64& size) { m_size = size; }

quint64 DataElementFragment::getFileChunkStart() const
{
  return m_fileChunkStart;
}

void DataElementFragment::setFileChunkStart(const quint64& fileChunkStart)
{
  m_fileChunkStart = fileChunkStart;
}

quint64 DataElementFragment::getFileChunkSize() const { return m_data.size(); }


quint64 DataElementFragment::strObjBody_cb() const
{
  quint64 total = CompactExtGuid(m_extendedGuid).getSizeInFile();
  total += CompactUInt64::getSizeInFile(m_size);
  total += CompactUInt64::getSizeInFile(m_fileChunkStart);
  total += CompactUInt64::getSizeInFile(m_data.size());
  total += m_data.size();

  return total;
}

quint64 DataElementFragment::cbNextHeader() const
{
  return strObjBody_cb();
}

void DataElementFragment::push_back(IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(obj);
}

IStreamObj_It_t DataElementFragment::insert(
    IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(pos);
  Q_UNUSED(obj);
  m_children.clear();
  return m_children.end();
}

void DataElementFragment::deserializeStrObj(QDataStream& ds)
{
  CompactExtGuid guid;
  ds >> guid;
  m_extendedGuid = guid.getExtendedGUID();

  CompactUInt64 val;
  ds >> val;
  m_size = val.getValue();

  ds >> val;
  m_fileChunkStart = val.getValue();

  // length
  ds >> val;

  m_data = ds.device()->read(val.getValue());
}

void DataElementFragment::serializeStrObj(QDataStream& ds) const
{
  ds << CompactExtGuid(m_extendedGuid);
  ds << CompactUInt64(m_size);
  ds << CompactUInt64(m_fileChunkStart);
  ds << CompactUInt64(m_data.size());

  ds.writeRawData(m_data.constData(), m_data.size());
}

} // namespace fsshttpb
} // namespace libmson
