#include "ObjectInfoDependencyOverride8.h"

#include <QDataStream>
#include <QDebug>

namespace MSONcommon {


void ObjectInfoDependencyOverride8::writeLowLevelXml(
    QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ObjectInfoDependencyOverride8");
  xmlWriter.writeAttribute("cRef", QString::number(m_cRef));
  xmlWriter << m_oid;

  xmlWriter.writeEndElement();
}

QDebug operator<<(QDebug dbg, const ObjectInfoDependencyOverride8 &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

CompactID ObjectInfoDependencyOverride8::oid() const { return m_oid; }

void ObjectInfoDependencyOverride8::setOid(const CompactID &oid) {
  m_oid = oid;
}

quint8 ObjectInfoDependencyOverride8::cRef() const { return m_cRef; }

void ObjectInfoDependencyOverride8::setCRef(const quint8 &cRef) {
  m_cRef = cRef;
}

void ObjectInfoDependencyOverride8::deserialize(QDataStream &ds) {
  ds >> m_oid;
  ds >> m_cRef;
}

void ObjectInfoDependencyOverride8::serialize(QDataStream &ds) const {
  ds << m_oid;
  ds << m_cRef;
}

void ObjectInfoDependencyOverride8::toDebugString(QDebug dbg) const {
  dbg << "ObjectInfoDependencyOverride8:\n"
      << "oid:  " << m_oid << '\n'
      << "cRef: " << m_cRef << '\n';
}

} // namespace MSONcommon
