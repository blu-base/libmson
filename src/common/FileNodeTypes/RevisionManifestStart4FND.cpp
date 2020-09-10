#include "RevisionManifestStart4FND.h"

namespace MSONcommon {

RevisionManifestStart4FND::RevisionManifestStart4FND() {}

ExtendedGUID RevisionManifestStart4FND::getRid() const { return m_rid; }

void RevisionManifestStart4FND::setRid(const ExtendedGUID &value) {
  m_rid = value;
}

ExtendedGUID RevisionManifestStart4FND::getRidDependent() const {
  return m_ridDependent;
}

void RevisionManifestStart4FND::setRidDependent(const ExtendedGUID &value) {
  m_ridDependent = value;
}

quint64 RevisionManifestStart4FND::getTimeCreation() const {
  return m_timeCreation;
}

void RevisionManifestStart4FND::setTimeCreation(const quint64 &value) {
  m_timeCreation = value;
}

qint32 RevisionManifestStart4FND::getRevisionRole() const {
  return m_revisionRole;
}

void RevisionManifestStart4FND::setRevisionRole(const qint32 &value) {
  m_revisionRole = value;
}

quint16 RevisionManifestStart4FND::getOdcsDefault() const {
  return m_odcsDefault;
}

void RevisionManifestStart4FND::setOdcsDefault(const quint16 &value) {
  m_odcsDefault = value;
}

void RevisionManifestStart4FND::deserialize(QDataStream &ds) {
  ds >> m_rid;
  ds >> m_ridDependent;
  ds >> m_timeCreation;
  ds >> m_revisionRole;
  ds >> m_odcsDefault;
}

void RevisionManifestStart4FND::serialize(QDataStream &ds) const {
  ds << m_rid;
  ds << m_ridDependent;
  ds << m_timeCreation;
  ds << m_revisionRole;
  ds << m_odcsDefault;
}

void RevisionManifestStart4FND::toDebugString(QDebug dbg) const {
  dbg << " RevisionManifestStart4FND:\n"
      << " rid:          " << m_rid << '\n'
      << " ridDependent: " << m_ridDependent << '\n'
      << " timeCreation: " << m_timeCreation << '\n'
      << " revisionRole: " << m_revisionRole << '\n'
      << " odcsDefault:  " << m_odcsDefault << '\n';
}

void RevisionManifestStart4FND::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("RevisionManifestStart4FND");

  xmlWriter.writeAttribute("revisionRole", QString::number(m_revisionRole));
  xmlWriter.writeAttribute("timeCreation", QString::number(m_timeCreation));
  xmlWriter.writeAttribute("odcsDefault", QString::number(m_revisionRole));

  m_rid.generateXml(xmlWriter);
  m_ridDependent.generateXml(xmlWriter);

  xmlWriter.writeEndElement();
}

} // namespace MSONcommon
