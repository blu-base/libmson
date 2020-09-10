#include "LayoutAlignment.h"

namespace MSONcommon {

LayoutAlignment::LayoutAlignment() {}

QDataStream &operator<<(QDataStream &ds, const LayoutAlignment &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, LayoutAlignment &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const LayoutAlignment &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

void LayoutAlignment::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("LayoutAlignment");
  xmlWriter.writeAttribute("horizontal", hAlignmentToString(lha()));
  xmlWriter.writeAttribute("vertial", vAlignmentToString(lva()));
  xmlWriter.writeAttribute("hMargin", fHorizMargin() ? "true" : "false");
  xmlWriter.writeAttribute("vMargin", fVertMargin() ? "true" : "false");
  xmlWriter.writeAttribute("valid", !laNil() ? "true" : "false");
  xmlWriter.writeEndElement();
}

HAlignment LayoutAlignment::lha() const {
  return static_cast<HAlignment>((m_value & LayoutAlignment_maskLha) >>
                                 LayoutAlignment_shiftLha);
}

void LayoutAlignment::setLha(const HAlignment &val) {
  m_value = (m_value & ~LayoutAlignment_maskLha) +
            (static_cast<quint32>(val) << LayoutAlignment_shiftLha);
}

VAlignment LayoutAlignment::lva() const {
  return static_cast<VAlignment>((m_value & LayoutAlignment_maskLva) >>
                                 LayoutAlignment_shiftLva);
}

void LayoutAlignment::setLva(const VAlignment &val) {
  m_value = (m_value & ~LayoutAlignment_maskLva) +
            (static_cast<quint32>(val) << LayoutAlignment_shiftLva);
}

bool LayoutAlignment::fHorizMargin() const {
  return (m_value & LayoutAlignment_maskFHorizMargin) >>
         LayoutAlignment_shiftFHorizMargin;
}

void LayoutAlignment::setFHorizMargin(const bool val) {
  m_value = (m_value & ~LayoutAlignment_maskFHorizMargin) +
            (static_cast<quint32>(val) << LayoutAlignment_shiftFHorizMargin);
}

bool LayoutAlignment::fVertMargin() const {
  return (m_value & LayoutAlignment_maskFVertMargin) >>
         LayoutAlignment_shiftFVertMargin;
}

void LayoutAlignment::setFVertMargin(const bool val) {
  m_value = (m_value & ~LayoutAlignment_maskFVertMargin) +
            (static_cast<quint32>(val) << LayoutAlignment_shiftFVertMargin);
}

bool LayoutAlignment::laNil() const {
  return (m_value & LayoutAlignment_maskLaNil) >> LayoutAlignment_shiftLaNil;
}

void LayoutAlignment::setLaNil(const bool val) {
  m_value = (m_value & ~LayoutAlignment_maskLaNil) +
            (static_cast<quint32>(val) << LayoutAlignment_shiftLaNil);
}

void LayoutAlignment::deserialize(QDataStream &ds) { ds >> m_value; }

void LayoutAlignment::serialize(QDataStream &ds) const { ds << m_value; }

void LayoutAlignment::toDebugString(QDebug dbg) const {
  dbg << "LayoutAligment:\n"
      << "h: " << hAlignmentToString(lha())
      << " v: " << vAlignmentToString(lva())
      << " hMargin: " << (fHorizMargin() ? "true" : "false")
      << " vMargin: " << (fVertMargin() ? "true" : "false") << '\n';
}

QString hAlignmentToString(const HAlignment &val) {
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

QString vAlignmentToString(const VAlignment &val) {
  switch (val) {
  case VAlignment::bottom:
    return "bottom";
  case VAlignment::top:
    return "top";
  }
  return "";
}

} // namespace MSONcommon
