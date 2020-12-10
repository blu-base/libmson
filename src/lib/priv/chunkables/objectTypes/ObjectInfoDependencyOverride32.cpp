#include "ObjectInfoDependencyOverride32.h"

namespace libmson {
namespace priv {

CompactID ObjectInfoDependencyOverride32::getOid() const { return m_oid; }

void ObjectInfoDependencyOverride32::setOid(const CompactID& oid)
{
  m_oid = oid;
}

quint32 ObjectInfoDependencyOverride32::getCRef() const { return m_cRef; }

void ObjectInfoDependencyOverride32::setCRef(const quint32& cRef)
{
  m_cRef = cRef;
}


void ObjectInfoDependencyOverride32::deserialize(QDataStream& ds)
{
  ds >> m_oid;
  ds >> m_cRef;
}

void ObjectInfoDependencyOverride32::serialize(QDataStream& ds) const
{
  ds << m_oid;
  ds << m_cRef;
}

} // namespace priv
} // namespace libmson
