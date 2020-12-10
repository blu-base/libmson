#include "RevisionManifestStart6FND.h"

namespace libmson {
namespace priv {

RevisionManifestStart6FND::RevisionManifestStart6FND(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode)), m_revisionRole(),
      m_odcsDefault()
{
}

ExtendedGUID RevisionManifestStart6FND::getRid() const { return m_rid; }

void RevisionManifestStart6FND::setRid(const ExtendedGUID& value)
{
  m_rid = value;
}

const quint64 RevisionManifestStart6FND::sizeInFile =
    2 * ExtendedGUID::getSizeInFile() + 6;

quint64 RevisionManifestStart6FND::getSizeInFile() const { return sizeInFile; }

ExtendedGUID RevisionManifestStart6FND::getRidDependent() const
{
  return m_ridDependent;
}

void RevisionManifestStart6FND::setRidDependent(const ExtendedGUID& value)
{
  m_ridDependent = value;
}

qint32 RevisionManifestStart6FND::getRevisionRole() const
{
  return m_revisionRole;
}

void RevisionManifestStart6FND::setRevisionRole(const qint32& value)
{
  m_revisionRole = value;
}

quint16 RevisionManifestStart6FND::getOdcsDefault() const
{
  return m_odcsDefault;
}

void RevisionManifestStart6FND::setOdcsDefault(const quint16& value)
{
  m_odcsDefault = value;
}

void RevisionManifestStart6FND::deserialize(QDataStream& ds)
{
  ds >> m_rid;
  ds >> m_ridDependent;
  ds >> m_revisionRole;
  ds >> m_odcsDefault;
}

void RevisionManifestStart6FND::serialize(QDataStream& ds) const
{
  ds << m_rid;
  ds << m_ridDependent;
  ds << m_revisionRole;
  ds << m_odcsDefault;
}

} // namespace priv
} // namespace libmson
