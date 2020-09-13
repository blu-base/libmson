#include "RevisionRoleAndContextDeclarationFND.h"

namespace MSONcommon {

ExtendedGUID RevisionRoleAndContextDeclarationFND::getGctxid() const {
  return m_gctxid;
}

void RevisionRoleAndContextDeclarationFND::setGctxid(
    const ExtendedGUID &value) {
  m_gctxid = value;
}

RevisionRoleDeclarationFND
RevisionRoleAndContextDeclarationFND::getBase() const {
  return m_base;
}

void RevisionRoleAndContextDeclarationFND::setBase(
    const RevisionRoleDeclarationFND &value) {
  m_base = value;
}

void RevisionRoleAndContextDeclarationFND::deserialize(QDataStream &ds) {
  ds >> m_base;
  ds >> m_gctxid;
}

void RevisionRoleAndContextDeclarationFND::serialize(QDataStream &ds) const {
  ds << m_base;
  ds << m_gctxid;
}

void RevisionRoleAndContextDeclarationFND::toDebugString(QDebug dbg) const {
  dbg << " RevisionRoleAndContextDeclarationFND\n"
      << " Base:\n"
      << m_base << "gctxid: " << m_gctxid << '\n';
}

void RevisionRoleAndContextDeclarationFND::writeLowLevelXml(
    QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("RevisionRoleAndContextDeclarationFND");

  xmlWriter << m_base;

  xmlWriter << m_gctxid;

  xmlWriter.writeEndElement();
}

} // namespace MSONcommon
