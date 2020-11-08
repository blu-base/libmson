#include "ObjectInfoDependencyOverride32.h"

#include <QDataStream>
#include <QDebug>

namespace libmson{
namespace priv{

CompactID ObjectInfoDependencyOverride32::oid() const { return m_oid; }

void ObjectInfoDependencyOverride32::setOid(const CompactID &oid) {
  m_oid = oid;
}

quint32 ObjectInfoDependencyOverride32::cRef() const { return m_cRef; }

void ObjectInfoDependencyOverride32::setCRef(const quint32 &cRef) {
  m_cRef = cRef;
}

void ObjectInfoDependencyOverride32::writeLowLevelXml(
    QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ObjectInfoDependencyOverride32");
  xmlWriter.writeAttribute("cRef", QString::number(m_cRef));
  xmlWriter << m_oid;

  xmlWriter.writeEndElement();
}

void ObjectInfoDependencyOverride32::deserialize(QDataStream &ds) {
  ds >> m_oid;
  ds >> m_cRef;
}

void ObjectInfoDependencyOverride32::serialize(QDataStream &ds) const {
  ds << m_oid;
  ds << m_cRef;
}

void ObjectInfoDependencyOverride32::toDebugString(QDebug &dbg) const {
  dbg << "ObjectInfoDependencyOverride32:\n"
      << "oid:  " << m_oid << '\n'
      << "cRef: " << m_cRef << '\n';
}

} //namespace priv
} // namespace libmson
