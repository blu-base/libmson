#include "PropertyType_ArrayOfObjectSpaceIDs.h"

#include <QDataStream>
#include <QDebug>

namespace libmson{
namespace priv{

std::vector<CompactID> PropertyType_ArrayOfObjectSpaceIDs::data() const {
  return m_data;
}

void PropertyType_ArrayOfObjectSpaceIDs::setData(
    const std::vector<CompactID> &data) {
  m_data = data;
}

quint32 PropertyType_ArrayOfObjectSpaceIDs::cCIDs() const { return m_cCIDs; }

void PropertyType_ArrayOfObjectSpaceIDs::setCCIDs(const quint32 &cCIDs) {
  m_cCIDs = cCIDs;
}

PropertyType_ArrayOfObjectSpaceIDs::PropertyType_ArrayOfObjectSpaceIDs()
    : m_cCIDs{} {}

void PropertyType_ArrayOfObjectSpaceIDs::deserialize(QDataStream &ds) {
  ds >> m_cCIDs;

  CompactID temp;
  for (size_t i{0}; i < m_cCIDs; i++) {
    ds >> temp;
    m_data.push_back(temp);
  }
}

void PropertyType_ArrayOfObjectSpaceIDs::serialize(QDataStream &ds) const {
  ds << m_cCIDs;

  for (size_t i{0}; i < m_cCIDs; i++) {
    ds << m_data.at(i);
  }
}

void PropertyType_ArrayOfObjectSpaceIDs::toDebugString(QDebug &dbg) const {}


void PropertyType_ArrayOfObjectSpaceIDs::generateXml(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("ArrayOfObjectSpaceIDs");
    xmlWriter.writeAttribute("cCID", QString::number(m_cCIDs));

    xmlWriter.writeStartElement("CompactIDs");
    for(const auto& entry : m_data) {
        entry.generateXml(xmlWriter);
    }
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
}

} //namespace priv
} // namespace libmson
