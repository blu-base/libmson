#include "PropertyType_ArrayNumber.h"

#include <QDataStream>
#include <QDebug>

quint32 PropertyType_ArrayNumber::cCIDs() const { return m_cCIDs; }

void PropertyType_ArrayNumber::setCCIDs(const quint32 &cCIDs) {
  m_cCIDs = cCIDs;
}

PropertyType_ArrayNumber::PropertyType_ArrayNumber() : m_cCIDs{} {}

void PropertyType_ArrayNumber::deserialize(QDataStream &ds) {
  ds >> m_cCIDs;
}

void PropertyType_ArrayNumber::serialize(QDataStream &ds) const {
  ds << m_cCIDs;
}

void PropertyType_ArrayNumber::toDebugString(QDebug dbg) const {}


void PropertyType_ArrayNumber::generateXml(QXmlStreamWriter& xmlWriter) const
{

    xmlWriter.writeStartElement("ArrayNumber");
    xmlWriter.writeAttribute("cCID", QString::number(m_cCIDs));

    xmlWriter.writeEndElement();
}
