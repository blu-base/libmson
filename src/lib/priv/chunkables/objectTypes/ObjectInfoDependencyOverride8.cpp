#include "ObjectInfoDependencyOverride8.h"

#include <QDataStream>
#include <QDebug>

namespace libmson {
namespace priv {


CompactID ObjectInfoDependencyOverride8::getOid() const { return m_oid; }

void ObjectInfoDependencyOverride8::setOid(const CompactID& oid)
{
  m_oid = oid;
}

quint8 ObjectInfoDependencyOverride8::getCRef() const { return m_cRef; }

void ObjectInfoDependencyOverride8::setCRef(const quint8& cRef)
{
  m_cRef = cRef;
}

void ObjectInfoDependencyOverride8::deserialize(QDataStream& ds)
{
  ds >> m_oid;
  ds >> m_cRef;
}

void ObjectInfoDependencyOverride8::serialize(QDataStream& ds) const
{
  ds << m_oid;
  ds << m_cRef;
}

} // namespace priv
} // namespace libmson
