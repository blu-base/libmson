#include "ObjectDataBLOB.h"

namespace libmson {
namespace fsshttpb {

QByteArray ObjectDataBLOB::getData() const { return m_data; }

void ObjectDataBLOB::setData(const QByteArray& data) { m_data = data; }

StreamObjectType ObjectDataBLOB::getType() const
{
  return StreamObjectType::ObjectDataBLOB;
}

quint64 ObjectDataBLOB::strObjBody_cb() const { return m_data.size(); }

quint64 ObjectDataBLOB::cbNextHeader() const
{
  return strObjBody_cb();
}

void ObjectDataBLOB::push_back(IStreamObject_SPtr_t& obj) { Q_UNUSED(obj); }

IStreamObj_It_t
ObjectDataBLOB::insert(IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(pos);
  Q_UNUSED(obj);
  m_children.clear();
  return m_children.end();
}

void ObjectDataBLOB::deserializeStrObj(QDataStream& ds)
{
  m_data = ds.device()->read(m_cbNxtHd);
}

void ObjectDataBLOB::serializeStrObj(QDataStream& ds) const
{
  ds.writeRawData(m_data.data(), m_data.size());
}

} // namespace fsshttpb
} // namespace libmson
