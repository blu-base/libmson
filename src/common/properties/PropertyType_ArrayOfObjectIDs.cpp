#include "PropertyType_ArrayOfObjectIDs.h"

#include <QDataStream>
#include <QDebug>

namespace MSONcommon {

std::vector<CompactID> PropertyType_ArrayOfObjectIDs::data() const {
  return m_data;
}

void PropertyType_ArrayOfObjectIDs::setData(
    const std::vector<CompactID> &data) {
  m_data = data;
}

quint32 PropertyType_ArrayOfObjectIDs::cCIDs() const { return m_cCIDs; }

void PropertyType_ArrayOfObjectIDs::setCCIDs(const quint32 &cCIDs) {
  m_cCIDs = cCIDs;
}

PropertyType_ArrayOfObjectIDs::PropertyType_ArrayOfObjectIDs() : m_cCIDs{} {}

void PropertyType_ArrayOfObjectIDs::deserialize(QDataStream &ds) {
  ds >> m_cCIDs;

  CompactID temp;
  for (size_t i{0}; i < m_cCIDs; i++) {
    ds >> temp;
    m_data.push_back(temp);
  }
}

void PropertyType_ArrayOfObjectIDs::serialize(QDataStream &ds) const {
  ds << m_cCIDs;

  for (size_t i{0}; i < m_cCIDs; i++) {
    ds << m_data.at(i);
  }
}

void PropertyType_ArrayOfObjectIDs::toDebugString(QDebug dbg) const {}


void PropertyType_ArrayOfObjectIDs::generateXml(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("ArrayOfObjectIDs");
    xmlWriter.writeAttribute("cCID", QString::number(m_cCIDs));

    xmlWriter.writeStartElement("CompactIDs");
    for(const auto& entry : m_data) {
        entry.generateXml(xmlWriter);
    }
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
}

} // namespace MSONcommon
