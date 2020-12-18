#include "ObjectDataBLOB.h"
namespace libmson {
namespace packStore {
namespace streamObj {

QByteArray ObjectDataBLOB::getData() const { return m_data; }

void ObjectDataBLOB::setData(const QByteArray& data) { m_data = data; }


void ObjectDataBLOB::deserialize(QDataStream& ds)
{
  StreamObjectHeader header;
  ds >> header;

  if (header.getType() != getType()) {
    qFatal("Trying to deserialze StreamObject of incorrect header type "
           "(ObjectDataBLOB)");
  }

  qint64 origPos = ds.device()->pos();

  m_data = ds.device()->read(header.getLength());

  if ((origPos + header.getLength()) != (quint64)ds.device()->pos()) {
    qFatal("Something went wrong parsing ObjectDataBLOB");
  }
}

void ObjectDataBLOB::serialize(QDataStream& ds) const
{
  StreamObjectHeader header(getType(), body_cb());
  ds << header;

  ds.writeRawData(m_data.data(), m_data.size());
}

quint64 ObjectDataBLOB::body_cb() const { return m_data.size(); }

StreamObjectType ObjectDataBLOB::getType() const
{
  return StreamObjectType::ObjectDataBLOB;
}
} // namespace streamObj
} // namespace packStore
} // namespace libmson
