#include "PropertyType_ArrayOfContextIDs.h"

#include <QDataStream>
#include <QDebug>

namespace libmson {
namespace priv {

std::vector<CompactID> PropertyType_ArrayOfContextIDs::data() const
{
  return m_data;
}

void PropertyType_ArrayOfContextIDs::setData(const std::vector<CompactID>& data)
{
}

quint32 PropertyType_ArrayOfContextIDs::cCIDs() const { return m_cCIDs; }

void PropertyType_ArrayOfContextIDs::setCCIDs(const quint32& cCIDs)
{
  m_cCIDs = cCIDs;
}

PropertyType_ArrayOfContextIDs::PropertyType_ArrayOfContextIDs() : m_cCIDs{} {}

void PropertyType_ArrayOfContextIDs::deserialize(QDataStream& ds)
{
  ds >> m_cCIDs;

  CompactID temp;
  for (size_t i{0}; i < m_cCIDs; i++) {
    ds >> temp;
    m_data.push_back(temp);
  }
}

void PropertyType_ArrayOfContextIDs::serialize(QDataStream& ds) const
{
  ds << m_cCIDs;

  for (size_t i{0}; i < m_cCIDs; i++) {
    ds << m_data.at(i);
  }
}

// void PropertyType_ArrayOfContextIDs::toDebugString(QDebug &dbg) const {}


// void PropertyType_ArrayOfContextIDs::generateXml(QXmlStreamWriter& xmlWriter)
// const
//{
//    xmlWriter.writeStartElement("ArrayOfContextIDs");
//    xmlWriter.writeAttribute("cCID", QString::number(m_cCIDs));

//    xmlWriter.writeStartElement("CompactIDs");
//    for(const auto& entry : m_data) {
//        entry.generateXml(xmlWriter);
//    }
//    xmlWriter.writeEndElement();

//    xmlWriter.writeEndElement();

//}

} // namespace priv
} // namespace libmson
