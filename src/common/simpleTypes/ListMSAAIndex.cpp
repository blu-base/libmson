#include "ListMSAAIndex.h"

namespace MSONcommon {

ListMSAAIndex::ListMSAAIndex() : m_value() {}

void ListMSAAIndex::setID(const ListSymbolID id) {
  m_value = static_cast<quint16>(id);
}

ListSymbolID ListMSAAIndex::getID() const {
  return static_cast<ListSymbolID>(m_value);
}

void ListMSAAIndex::setIDValue(const quint16 id) { m_value = id; }

quint16 ListMSAAIndex::getIDValue() const { return m_value; }

void MSONcommon::ListMSAAIndex::toDebugString(QDebug &dbg) const {
  dbg << "ListMSAAIndex: " << IDtoString(m_value) << '\n';
}

void MSONcommon::ListMSAAIndex::writeLowLevelXml(
    QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ListMSAAIndex");
  xmlWriter.writeCharacters(IDtoString(m_value));
  xmlWriter.writeEndElement();
}

void MSONcommon::ListMSAAIndex::deserialize(QDataStream &ds) { ds >> m_value; }

void MSONcommon::ListMSAAIndex::serialize(QDataStream &ds) const {
  ds << m_value;
}

QString IDtoString(const ListSymbolID id) {
  switch (id) {
  case MSONcommon::ListSymbolID::nil:
    return "nil";
  case MSONcommon::ListSymbolID::circle_solid_small:
    return "circle_solid_small";
  case MSONcommon::ListSymbolID::circle_hollow_small:
    return "circle_hollow_small";
  case MSONcommon::ListSymbolID::circle_solid:
    return "circle_solid";
  case MSONcommon::ListSymbolID::circle_hollow:
    return "circle_hollow";
  case MSONcommon::ListSymbolID::donut_solid:
    return "donut_solid";
  case MSONcommon::ListSymbolID::donut_hollow:
    return "donut_hollow";
  case MSONcommon::ListSymbolID::square_solid_small:
    return "square_solid_small";
  case MSONcommon::ListSymbolID::square_hollow_small:
    return "square_hollow_small";
  case MSONcommon::ListSymbolID::square_solid:
    return "square_solid";
  case MSONcommon::ListSymbolID::square_hollow:
    return "square_hollow";
  case MSONcommon::ListSymbolID::triangle_narrow:
    return "triangle_narrow";
  case MSONcommon::ListSymbolID::triangle_wide:
    return "triangle_wide";
  case MSONcommon::ListSymbolID::diamond_hollow_large:
    return "diamond_hollow_large";
  case MSONcommon::ListSymbolID::diamond_hollow:
    return "diamond_hollow";
  case MSONcommon::ListSymbolID::diamond_solid_small:
    return "diamond_solid_small";
  case MSONcommon::ListSymbolID::fourSmallDiamonds:
    return "fourSmallDiamonds";
  case MSONcommon::ListSymbolID::star_solid_large:
    return "star_solid_large";
  case MSONcommon::ListSymbolID::star_hollow_large:
    return "star_hollow_large";
  case MSONcommon::ListSymbolID::sun_solid_large:
    return "sun_solid_large";
  case MSONcommon::ListSymbolID::greaterThan_sign:
    return "greaterThan_sign";
  case MSONcommon::ListSymbolID::arrow_single_line:
    return "arrow_single_line";
  case MSONcommon::ListSymbolID::arrow_double_line:
    return "arrow_double_line";
  case MSONcommon::ListSymbolID::arrow_hollow_large:
    return "arrow_hollow_large";
  case MSONcommon::ListSymbolID::asterisk:
    return "asterisk";
  case MSONcommon::ListSymbolID::dash:
    return "dash";
  case MSONcommon::ListSymbolID::enDash:
    return "enDash";
  case MSONcommon::ListSymbolID::emDash:
    return "emDash";
  case MSONcommon::ListSymbolID::smilingFace:
    return "smilingFace";
  case MSONcommon::ListSymbolID::neutralFace:
    return "neutralFace";
  case MSONcommon::ListSymbolID::frowningFace:
    return "frowningFace";
  case MSONcommon::ListSymbolID::checkMark:
    return "checkMark";
  case MSONcommon::ListSymbolID::telephone:
    return "telephone";
  case MSONcommon::ListSymbolID::EnvelopeBack:
    return "EnvelopeBack";
  case MSONcommon::ListSymbolID::diamond_solid:
    return "diamond_solid";

  default:
    return "invalid";
  }
}

QString IDtoString(const quint16 id) {
  return IDtoString(static_cast<ListSymbolID>(id));
}

} // namespace MSONcommon
