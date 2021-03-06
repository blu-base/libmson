#include "RootObjectReference3FND.h"

namespace libmson {
namespace priv {

RootObjectReference3FND::RootObjectReference3FND(FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode)), m_RootRole(0)
{
}

quint32 RootObjectReference3FND::getRootRole() const { return m_RootRole; }

void RootObjectReference3FND::setRootRole(const quint32& value)
{
  m_RootRole = value;
}

const quint64 RootObjectReference3FND::sizeInFile =
    ExtendedGUID::getSizeInFile() + sizeof(m_RootRole);

quint64 RootObjectReference3FND::getSizeInFile() const { return sizeInFile; }

ExtendedGUID RootObjectReference3FND::getOidRoot() const { return m_oidRoot; }

void RootObjectReference3FND::setOidRoot(const ExtendedGUID& value)
{
  m_oidRoot = value;
}

void RootObjectReference3FND::deserialize(QDataStream& ds)
{
  ds >> m_oidRoot;
  ds >> m_RootRole;
}

void RootObjectReference3FND::serialize(QDataStream& ds) const
{
  ds << m_oidRoot;
  ds << m_RootRole;
}

// void RootObjectReference3FND::toDebugString(QDebug &dbg) const {
//  dbg << " RootObjectReference2FNDX:\n"
//      << " oidRoot: " << m_oidRoot << '\n'
//      << " RootRole: " << m_RootRole << '\n';
//}

// void RootObjectReference3FND::writeLowLevelXml(
//    QXmlStreamWriter &xmlWriter) const {
//  xmlWriter.writeStartElement("RootObjectReference3FND");
//  xmlWriter.writeAttribute("rootRole", QString::number(m_RootRole));

//  xmlWriter << m_oidRoot;

//  xmlWriter.writeEndElement();
//}

} // namespace priv
} // namespace libmson
