#include "DataElementFragment.h"

#include <priv/commonTypes/CompactUInt64.h>

namespace libmson {
namespace packStore {

QByteArray DataElementFragment::getData() const
{
  return m_data;
}

void DataElementFragment::setData(const QByteArray& data)
{
  m_data = data;
}

DataElementFragment::DataElementFragment() : m_size(0), m_fileChunkStart(0) {}

CompactExtGuid DataElementFragment::getExtendedGuid() const
{
  return m_extendedGuid;
}

void DataElementFragment::setExtendedGuid(const CompactExtGuid& extendedGuid)
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

void DataElementFragment::deserialize(QDataStream& ds)
{
  ds >> m_extendedGuid;

  CompactUInt64 val;
  ds >> val;
  m_size = val.getValue();

  ds >> val;
  m_fileChunkStart = val.getValue();

  ds >> val;
  m_data = ds.device()->read(val.getValue());
}

void DataElementFragment::serialize(QDataStream& ds) const
{
  ds << m_extendedGuid;

  ds << CompactUInt64(m_size);
  ds << CompactUInt64(m_fileChunkStart);
  ds << CompactUInt64(m_data.size());

  ds.writeRawData(m_data.constData(), m_data.size());
}

quint64 DataElementFragment::cb() const
{
  quint64 total = m_extendedGuid.getSizeInFile();
  total += CompactUInt64::getSizeInFile(m_size);
  total += CompactUInt64::getSizeInFile(m_fileChunkStart);
  total += CompactUInt64::getSizeInFile(m_data.size());
  total += m_data.size();

  return total;
}

DataElementType DataElementFragment::getType() const
{
  return DataElementType::DataElementFragment;
}

} // namespace packStore
} // namespace libmson
