#include "BodyTextAlignment.h"

#include <QDataStream>

namespace libmson {

BodyTextAlignment::BodyTextAlignment() : m_value() {}
BodyTextAlignment::BodyTextAlignment(const quint32 val) : m_value(val) {}

// void BodyTextAlignment::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
//   xmlWriter.writeStartElement("BodyTextAlignment");
//   xmlWriter.writeCharacters(QString::number(m_value));
//   xmlWriter.writeEndElement();
// }

quint32 BodyTextAlignment::getValue() const { return m_value; }

void BodyTextAlignment::setValue(const quint32 val) { m_value = val; }

void BodyTextAlignment::deserialize(QDataStream& ds) { ds >> m_value; }

void BodyTextAlignment::serialize(QDataStream& ds) const { ds << m_value; }

} // namespace libmson
