#include "ListMSAAIndex.h"

namespace libmson {

ListMSAAIndex::ListMSAAIndex() : m_value() {}

void ListMSAAIndex::setID(const ListSymbolID id)
{
  m_value = static_cast<quint16>(id);
}

ListSymbolID ListMSAAIndex::getID() const
{
  return static_cast<ListSymbolID>(m_value);
}

void ListMSAAIndex::setIDValue(const quint16 id) { m_value = id; }

quint16 ListMSAAIndex::getIDValue() const { return m_value; }

// void ListMSAAIndex::writeLowLevelXml(
// QXmlStreamWriter &xmlWriter) const {
// xmlWriter.writeStartElement("ListMSAAIndex");
// xmlWriter.writeCharacters(IDtoString(m_value));
// xmlWriter.writeEndElement();
// }

void ListMSAAIndex::deserialize(QDataStream& ds) { ds >> m_value; }

void ListMSAAIndex::serialize(QDataStream& ds) const { ds << m_value; }

QString ListMSAAIndex::IDtoString(const ListSymbolID id)
{
  switch (id) {
  case ListSymbolID::nil:
    return "nil";
  case ListSymbolID::circle_solid_small:
    return "circle_solid_small";
  case ListSymbolID::circle_hollow_small:
    return "circle_hollow_small";
  case ListSymbolID::circle_solid:
    return "circle_solid";
  case ListSymbolID::circle_hollow:
    return "circle_hollow";
  case ListSymbolID::donut_solid:
    return "donut_solid";
  case ListSymbolID::donut_hollow:
    return "donut_hollow";
  case ListSymbolID::square_solid_small:
    return "square_solid_small";
  case ListSymbolID::square_hollow_small:
    return "square_hollow_small";
  case ListSymbolID::square_solid:
    return "square_solid";
  case ListSymbolID::square_hollow:
    return "square_hollow";
  case ListSymbolID::triangle_narrow:
    return "triangle_narrow";
  case ListSymbolID::triangle_wide:
    return "triangle_wide";
  case ListSymbolID::diamond_hollow_large:
    return "diamond_hollow_large";
  case ListSymbolID::diamond_hollow:
    return "diamond_hollow";
  case ListSymbolID::diamond_solid_small:
    return "diamond_solid_small";
  case ListSymbolID::fourSmallDiamonds:
    return "fourSmallDiamonds";
  case ListSymbolID::star_solid_large:
    return "star_solid_large";
  case ListSymbolID::star_hollow_large:
    return "star_hollow_large";
  case ListSymbolID::sun_solid_large:
    return "sun_solid_large";
  case ListSymbolID::greaterThan_sign:
    return "greaterThan_sign";
  case ListSymbolID::arrow_single_line:
    return "arrow_single_line";
  case ListSymbolID::arrow_double_line:
    return "arrow_double_line";
  case ListSymbolID::arrow_hollow_large:
    return "arrow_hollow_large";
  case ListSymbolID::asterisk:
    return "asterisk";
  case ListSymbolID::dash:
    return "dash";
  case ListSymbolID::enDash:
    return "enDash";
  case ListSymbolID::emDash:
    return "emDash";
  case ListSymbolID::smilingFace:
    return "smilingFace";
  case ListSymbolID::neutralFace:
    return "neutralFace";
  case ListSymbolID::frowningFace:
    return "frowningFace";
  case ListSymbolID::checkMark:
    return "checkMark";
  case ListSymbolID::telephone:
    return "telephone";
  case ListSymbolID::EnvelopeBack:
    return "EnvelopeBack";
  case ListSymbolID::diamond_solid:
    return "diamond_solid";

  default:
    return "invalid";
  }
}

QString ListMSAAIndex::IDtoString(const quint16 id)
{
  return IDtoString(static_cast<ListSymbolID>(id));
}

} // namespace libmson
