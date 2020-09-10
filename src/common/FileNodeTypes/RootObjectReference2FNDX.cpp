#include "RootObjectReference2FNDX.h"

namespace MSONcommon {

RootObjectReference2FNDX::RootObjectReference2FNDX() :
m_RootRole(0) {}

CompactID RootObjectReference2FNDX::getOidRoot() const { return m_oidRoot; }

void RootObjectReference2FNDX::setOidRoot(const CompactID &value) {
  m_oidRoot = value;
}

quint32 RootObjectReference2FNDX::getRootRole() const { return m_RootRole; }

void RootObjectReference2FNDX::setRootRole(const quint32 &value) {
  m_RootRole = value;
}

void RootObjectReference2FNDX::deserialize(QDataStream &ds) {
  ds >> m_oidRoot;
  ds >> m_RootRole;
}

void RootObjectReference2FNDX::serialize(QDataStream &ds) const {
  ds << m_oidRoot;
  ds << m_RootRole;
}

void RootObjectReference2FNDX::toDebugString(QDebug dbg) const {
  dbg << " RootObjectReference2FNDX:\n"
      << " oidRoot: " << m_oidRoot << '\n'
      << " RootRole: " << m_RootRole << '\n';
}


void RootObjectReference2FNDX::generateXml(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("RootObjectReference2FNDX");
    xmlWriter.writeAttribute("rootRole", QString::number(m_RootRole));
    m_oidRoot.generateXml(xmlWriter);


    xmlWriter.writeEndElement();
}

} // namespace MSONcommon
