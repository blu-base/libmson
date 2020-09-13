#include "RevisionManifestStart6FND.h"

namespace MSONcommon {

RevisionManifestStart6FND::RevisionManifestStart6FND() : m_revisionRole(), m_odcsDefault() {}

ExtendedGUID RevisionManifestStart6FND::getRid() const { return m_rid; }

void RevisionManifestStart6FND::setRid(const ExtendedGUID &value) {
  m_rid = value;
}

ExtendedGUID RevisionManifestStart6FND::getRidDependent() const {
  return m_ridDependent;
}

void RevisionManifestStart6FND::setRidDependent(const ExtendedGUID &value) {
  m_ridDependent = value;
}

qint32 RevisionManifestStart6FND::getRevisionRole() const {
  return m_revisionRole;
}

void RevisionManifestStart6FND::setRevisionRole(const qint32 &value) {
  m_revisionRole = value;
}

quint16 RevisionManifestStart6FND::getOdcsDefault() const {
  return m_odcsDefault;
}

void RevisionManifestStart6FND::setOdcsDefault(const quint16 &value) {
  m_odcsDefault = value;
}

void RevisionManifestStart6FND::deserialize(QDataStream &ds) {
  ds >> m_rid;
  ds >> m_ridDependent;
  ds >> m_revisionRole;
  ds >> m_odcsDefault;
}

void RevisionManifestStart6FND::serialize(QDataStream &ds) const {
  ds << m_rid;
  ds << m_ridDependent;
  ds << m_revisionRole;
  ds << m_odcsDefault;
}

void RevisionManifestStart6FND::toDebugString(QDebug &dbg) const {
  dbg << " RevisionManifestStart6FND:\n"
      << " rid:          " << m_rid << '\n'
      << " ridDependent: " << m_ridDependent << '\n'
      << " revisionRole: " << m_revisionRole << '\n'
      << " odcsDefault:  " << m_odcsDefault << '\n';
}

void RevisionManifestStart6FND::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("RevisionManifestStart6FND");

  xmlWriter.writeAttribute("revisionRole", QString::number(m_revisionRole));
  xmlWriter.writeAttribute("odcsDefault", QString::number(m_revisionRole));

  xmlWriter << m_rid;
  xmlWriter << m_ridDependent;

  xmlWriter.writeEndElement();
}

} // namespace MSONcommon
