#include "prtArrayOfPropertyValues.h"
#include "../commonTypes/Enums.h"
#include <QDataStream>
#include <QDebug>

#include "PropertyType_PropertySet.h"


prtArrayOfPropertyValues::prtArrayOfPropertyValues() {}

QDataStream &operator<<(QDataStream &ds, const prtArrayOfPropertyValues &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, prtArrayOfPropertyValues &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const prtArrayOfPropertyValues &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

quint32 prtArrayOfPropertyValues::cProperties() const { return m_cProperties; }

void prtArrayOfPropertyValues::setCProperties(const quint32 &cProperties) {
  m_cProperties = cProperties;
}

PropertyID prtArrayOfPropertyValues::prid() const { return m_prid; }

void prtArrayOfPropertyValues::setPrid(const PropertyID &prid) {
  m_prid = prid;
}

std::vector<PropertySet> prtArrayOfPropertyValues::dataVector() const {
  return m_dataVector;
}

void prtArrayOfPropertyValues::setDataVector(
    const std::vector<PropertySet> &dataVector) {
  m_dataVector = dataVector;
}

void prtArrayOfPropertyValues::deserialize(QDataStream &ds) {
  ds >> m_cProperties;

  if (m_cProperties != 0) {
    ds >> m_prid;

    for (size_t i{0}; i < m_cProperties; i++) {
      PropertySet entry;
      ds >> entry;
      m_dataVector.push_back(entry);
    }

  }
}

void prtArrayOfPropertyValues::serialize(QDataStream &ds) const {}

void prtArrayOfPropertyValues::toDebugString(QDebug dbg) const {}

void prtArrayOfPropertyValues::generateXml(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("prtArrayOfPropertyValues");
    xmlWriter.writeAttribute("cProperties", QString::number(m_cProperties));
    m_prid.generateXml(xmlWriter);

    xmlWriter.writeStartElement("PropertySets");
    for(const auto& entry : m_dataVector) {
        entry.generateXml(xmlWriter);
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
}
