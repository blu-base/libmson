#include "PropertyType_ArrayOfPropertyValues.h"

#include <QDataStream>
#include <QDebug>

namespace MSONcommon {

PropertyType_ArrayOfPropertyValues::PropertyType_ArrayOfPropertyValues()
    : m_cProperties(0) {}

QDataStream &operator<<(QDataStream &ds,
                        const PropertyType_ArrayOfPropertyValues &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds,
                        PropertyType_ArrayOfPropertyValues &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const PropertyType_ArrayOfPropertyValues &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

quint32 PropertyType_ArrayOfPropertyValues::cProperties() const {
  return m_cProperties;
}

void PropertyType_ArrayOfPropertyValues::setCProperties(
    const quint32 &cProperties) {
  m_cProperties = cProperties;
}

PropertyID PropertyType_ArrayOfPropertyValues::prid() const { return m_prid; }

void PropertyType_ArrayOfPropertyValues::setPrid(const PropertyID &prid) {
  m_prid = prid;
}

std::vector<PropertySet> PropertyType_ArrayOfPropertyValues::data() const {
  return m_data;
}

void PropertyType_ArrayOfPropertyValues::setData(
    const std::vector<PropertySet> &data) {
  m_data = data;
}

void PropertyType_ArrayOfPropertyValues::deserialize(QDataStream &ds) {
  ds >> m_cProperties;

  if (m_cProperties != 0) {
    ds >> m_prid;

    for (quint32 i{0}; i < m_cProperties; i++) {
      PropertySet ps;
      ds >> ps;
      m_data.push_back(ps);
    }
  }
}

void PropertyType_ArrayOfPropertyValues::serialize(QDataStream &ds) const {}

void PropertyType_ArrayOfPropertyValues::toDebugString(QDebug dbg) const {}

void PropertyType_ArrayOfPropertyValues::generateXml(
    QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ArrayOfPropertyValues");
  xmlWriter.writeAttribute("m_cProperties", QString::number(m_cProperties));
  m_prid.generateXml(xmlWriter);

  xmlWriter.writeStartElement("PropertySets");
  for (const auto &entry : m_data) {
    entry.generateXml(xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();
}

} // namespace MSONcommon
