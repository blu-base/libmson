#include "RevisionManifestStart7FND.h"

namespace libmson {
namespace priv {

RevisionManifestStart7FND::RevisionManifestStart7FND(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode)), m_base(parentFileNode)
{
}

RevisionManifestStart6FND RevisionManifestStart7FND::getBase() const
{
  return m_base;
}

void RevisionManifestStart7FND::setBase(const RevisionManifestStart6FND& value)
{
  m_base = value;
}


ExtendedGUID RevisionManifestStart7FND::getGctxid() const { return m_gctxid; }

void RevisionManifestStart7FND::setGctxid(const ExtendedGUID& value)
{
  m_gctxid = value;
}


quint16 RevisionManifestStart7FND::getOdcsDefault() const
{
  return m_base.getOdcsDefault();
}

qint32 RevisionManifestStart7FND::getRevisionRole() const
{
  return m_base.getRevisionRole();
}

ExtendedGUID RevisionManifestStart7FND::getRidDependent() const
{
  return m_base.getRidDependent();
}

ExtendedGUID RevisionManifestStart7FND::getRid() const
{
  return m_base.getRid();
}

quint64 RevisionManifestStart7FND::getSizeInFile() const
{
  return m_base.getSizeInFile() + ExtendedGUID::getSizeInFile();
}

void RevisionManifestStart7FND::deserialize(QDataStream& ds)
{
  ds >> m_base;
  ds >> m_gctxid;
}

void RevisionManifestStart7FND::serialize(QDataStream& ds) const
{
  ds << m_base;
  ds << m_gctxid;
}


} // namespace priv
} // namespace libmson
