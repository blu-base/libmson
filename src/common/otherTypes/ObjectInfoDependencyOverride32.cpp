#include "ObjectInfoDependencyOverride32.h"

#include <QDataStream>
#include <QDebug>

ObjectInfoDependencyOverride32::ObjectInfoDependencyOverride32() {}

QDataStream &operator<<(QDataStream &ds,
                        const ObjectInfoDependencyOverride32 &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, ObjectInfoDependencyOverride32 &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const ObjectInfoDependencyOverride32 &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

CompactID ObjectInfoDependencyOverride32::oid() const { return m_oid; }

void ObjectInfoDependencyOverride32::setOid(const CompactID &oid) {
  m_oid = oid;
}

quint32 ObjectInfoDependencyOverride32::cRef() const { return m_cRef; }

void ObjectInfoDependencyOverride32::setCRef(const quint32 &cRef) {
  m_cRef = cRef;
}

void ObjectInfoDependencyOverride32::generateXml(
    QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ObjectInfoDependencyOverride32");
  xmlWriter.writeAttribute("cRef", QString::number(m_cRef));
  m_oid.generateXml(xmlWriter);

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

void ObjectInfoDependencyOverride32::toDebugString(QDebug dbg) const {
  dbg << "ObjectInfoDependencyOverride32:\n"
      << "oid:  " << m_oid << '\n'
      << "cRef: " << m_cRef << '\n';
}
