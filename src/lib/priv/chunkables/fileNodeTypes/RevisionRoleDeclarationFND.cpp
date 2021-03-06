#include "RevisionRoleDeclarationFND.h"

namespace libmson {
namespace priv {

RevisionRoleDeclarationFND::RevisionRoleDeclarationFND(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode)), m_RevisionRole()
{
}

quint32 RevisionRoleDeclarationFND::getRevisionRole() const
{
  return m_RevisionRole;
}

void RevisionRoleDeclarationFND::setRevisionRole(const quint32& value)
{
  m_RevisionRole = value;
}

const quint64 RevisionRoleDeclarationFND::sizeInFile =
    ExtendedGUID::getSizeInFile() + sizeof(m_RevisionRole);

quint64 RevisionRoleDeclarationFND::getSizeInFile() const { return sizeInFile; }


ExtendedGUID RevisionRoleDeclarationFND::getRid() const { return m_rid; }

void RevisionRoleDeclarationFND::setRid(const ExtendedGUID& value)
{
  m_rid = value;
}

void RevisionRoleDeclarationFND::deserialize(QDataStream& ds)
{
  ds >> m_rid;
  ds >> m_RevisionRole;
}

void RevisionRoleDeclarationFND::serialize(QDataStream& ds) const
{
  ds << m_rid;
  ds << m_RevisionRole;
}

// void RevisionRoleDeclarationFND::toDebugString(QDebug& dbg) const
//{
//  dbg << " RevisionRoleDeclarationFND:\n"
//      << " Rid: " << m_rid << '\n'
//      << " RevisionRole: " << m_RevisionRole << '\n';
//}

// void RevisionRoleDeclarationFND::writeLowLevelXml(
//    QXmlStreamWriter& xmlWriter) const
//{
//  xmlWriter.writeStartElement("RevisionRoleDeclarationFND");
//  xmlWriter.writeAttribute("revisionRole", QString::number(m_RevisionRole));
//  xmlWriter << m_rid;
//  xmlWriter.writeEndElement();
//}

} // namespace priv
} // namespace libmson
