#include "RevisionManifestListStartFND.h"

namespace MSONcommon {

RevisionManifestListStartFND::RevisionManifestListStartFND() : m_nInstance() {}

ExtendedGUID RevisionManifestListStartFND::getGosid() const { return m_gosid; }

void RevisionManifestListStartFND::setGosid(const ExtendedGUID &value) {
  m_gosid = value;
}

quint32 RevisionManifestListStartFND::getNInstance() const {
  return m_nInstance;
}

void RevisionManifestListStartFND::setNInstance(const quint32 &value) {
  m_nInstance = value;
}

void RevisionManifestListStartFND::deserialize(QDataStream &ds) {
  ds >> m_gosid;
  ds >> m_nInstance;
}

void RevisionManifestListStartFND::serialize(QDataStream &ds) const {
  ds << m_gosid;
  ds << m_nInstance;
}

void RevisionManifestListStartFND::toDebugString(QDebug &dbg) const {
  dbg << " RevisionManifestListStartFND: gosid: " << m_gosid
      << " nInstance: " << m_nInstance << '\n';
}

void RevisionManifestListStartFND::writeLowLevelXml(
    QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("RevisionManifestListStartFND");
  xmlWriter.writeAttribute("nInstance", QString::number(m_nInstance));
  xmlWriter << m_gosid;

  xmlWriter.writeEndElement();
}

} // namespace MSONcommon
