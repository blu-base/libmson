#include "RevisionRoleAndContextDeclarationFND.h"

namespace libmson {
namespace priv {

RevisionRoleAndContextDeclarationFND::RevisionRoleAndContextDeclarationFND(
    FileNode_WPtr_t parentFileNode)
    : IFileNodeType(parentFileNode), m_base(parentFileNode)
{
}

RevisionRoleDeclarationFND RevisionRoleAndContextDeclarationFND::getBase() const
{
  return m_base;
}

void RevisionRoleAndContextDeclarationFND::setBase(
    const RevisionRoleDeclarationFND& value)
{
  m_base = value;
}

ExtendedGUID RevisionRoleAndContextDeclarationFND::getGctxid() const
{
  return m_gctxid;
}

void RevisionRoleAndContextDeclarationFND::setGctxid(const ExtendedGUID& value)
{
  m_gctxid = value;
}

ExtendedGUID RevisionRoleAndContextDeclarationFND::getRid() const
{
  return m_base.getRid();
}

quint32 RevisionRoleAndContextDeclarationFND::getRevisionRole() const
{
  return m_base.getRevisionRole();
}

quint64 RevisionRoleAndContextDeclarationFND::getSizeInFile() const
{
  return m_base.getSizeInFile() + ExtendedGUID::getSizeInFile();
}


void RevisionRoleAndContextDeclarationFND::deserialize(QDataStream& ds)
{
  ds >> m_base;
  ds >> m_gctxid;
}

void RevisionRoleAndContextDeclarationFND::serialize(QDataStream& ds) const
{
  ds << m_base;
  ds << m_gctxid;
}

// void RevisionRoleAndContextDeclarationFND::toDebugString(QDebug &dbg) const {
//  dbg << " RevisionRoleAndContextDeclarationFND\n"
//      << " Base:\n"
//      << m_base << "gctxid: " << m_gctxid << '\n';
//}

// void RevisionRoleAndContextDeclarationFND::writeLowLevelXml(
//    QXmlStreamWriter &xmlWriter) const {
//  xmlWriter.writeStartElement("RevisionRoleAndContextDeclarationFND");

//  xmlWriter << m_base;

//  xmlWriter << m_gctxid;

//  xmlWriter.writeEndElement();
//}

} // namespace priv
} // namespace libmson
