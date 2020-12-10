#include "LayoutAlignment.h"

namespace libmson {

LayoutAlignment::LayoutAlignment() : m_value() {}

// void LayoutAlignment::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
// xmlWriter.writeStartElement("LayoutAlignment");
// xmlWriter.writeAttribute("horizontal", hAlignmentToString(lha()));
// xmlWriter.writeAttribute("vertial", vAlignmentToString(lva()));
// xmlWriter.writeAttribute("hMargin", fHorizMargin() ? "true" : "false");
// xmlWriter.writeAttribute("vMargin", fVertMargin() ? "true" : "false");
// xmlWriter.writeAttribute("valid", !laNil() ? "true" : "false");
// xmlWriter.writeEndElement();
// }

HAlignment LayoutAlignment::getHAlignment() const
{
  return static_cast<HAlignment>(
      (m_value & LayoutAlignment_maskLha) >> LayoutAlignment_shiftLha);
}

void LayoutAlignment::setAlignment(const HAlignment& val)
{
  m_value = (m_value & ~LayoutAlignment_maskLha) +
            (static_cast<quint32>(val) << LayoutAlignment_shiftLha);
}

VAlignment LayoutAlignment::getVAlignment() const
{
  return static_cast<VAlignment>(
      (m_value & LayoutAlignment_maskLva) >> LayoutAlignment_shiftLva);
}

void LayoutAlignment::setAlignment(const VAlignment& val)
{
  m_value = (m_value & ~LayoutAlignment_maskLva) +
            (static_cast<quint32>(val) << LayoutAlignment_shiftLva);
}

bool LayoutAlignment::getFHorizMargin() const
{
  return (m_value & LayoutAlignment_maskFHorizMargin) >>
         LayoutAlignment_shiftFHorizMargin;
}

void LayoutAlignment::setFHorizMargin(const bool val)
{
  m_value = (m_value & ~LayoutAlignment_maskFHorizMargin) +
            (static_cast<quint32>(val) << LayoutAlignment_shiftFHorizMargin);
}

bool LayoutAlignment::getFVertMargin() const
{
  return (m_value & LayoutAlignment_maskFVertMargin) >>
         LayoutAlignment_shiftFVertMargin;
}

void LayoutAlignment::setFVertMargin(const bool val)
{
  m_value = (m_value & ~LayoutAlignment_maskFVertMargin) +
            (static_cast<quint32>(val) << LayoutAlignment_shiftFVertMargin);
}

bool LayoutAlignment::isNil() const
{
  return (m_value & LayoutAlignment_maskLaNil) >> LayoutAlignment_shiftLaNil;
}

void LayoutAlignment::setNil(const bool val)
{
  m_value = (m_value & ~LayoutAlignment_maskLaNil) +
            (static_cast<quint32>(val) << LayoutAlignment_shiftLaNil);
}

void LayoutAlignment::deserialize(QDataStream& ds) { ds >> m_value; }

void LayoutAlignment::serialize(QDataStream& ds) const { ds << m_value; }

QString LayoutAlignment::hAlignmentToString(const HAlignment& val)
{
  switch (val) {
  case HAlignment::val0:
    return "val0";
  case HAlignment::left:
    return "left";
  case HAlignment::center:
    return "center";
  case HAlignment::right:
    return "right";
  case HAlignment::inReadDirection:
    return "inReadDirection";
  case HAlignment::reverseReadDirection:
    return "reverseReadDirection";
  case HAlignment::val6:
    return "val6";
  case HAlignment::val7:
    return "val7";
  }
  return "";
}

QString LayoutAlignment::vAlignmentToString(const VAlignment& val)
{
  switch (val) {
  case VAlignment::bottom:
    return "bottom";
  case VAlignment::top:
    return "top";
  }
  return "";
}

} // namespace libmson
