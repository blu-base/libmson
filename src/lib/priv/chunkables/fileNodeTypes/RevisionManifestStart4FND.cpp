#include "RevisionManifestStart4FND.h"

namespace libmson {
namespace priv {

RevisionManifestStart4FND::RevisionManifestStart4FND(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode)), m_timeCreation(),
      m_revisionRole(), m_odcsDefault()
{
}

ExtendedGUID RevisionManifestStart4FND::getRid() const { return m_rid; }

void RevisionManifestStart4FND::setRid(const ExtendedGUID& value)
{
  m_rid = value;
}

const quint64 RevisionManifestStart4FND::sizeInFile =
    2 * ExtendedGUID::getSizeInFile() + 14;

quint64 RevisionManifestStart4FND::getSizeInFile() const { return sizeInFile; }

ExtendedGUID RevisionManifestStart4FND::getRidDependent() const
{
  return m_ridDependent;
}

void RevisionManifestStart4FND::setRidDependent(const ExtendedGUID& value)
{
  m_ridDependent = value;
}

quint64 RevisionManifestStart4FND::getTimeCreation() const
{
  return m_timeCreation;
}

void RevisionManifestStart4FND::setTimeCreation(const quint64& value)
{
  m_timeCreation = value;
}

qint32 RevisionManifestStart4FND::getRevisionRole() const
{
  return m_revisionRole;
}

void RevisionManifestStart4FND::setRevisionRole(const qint32& value)
{
  m_revisionRole = value;
}

quint16 RevisionManifestStart4FND::getOdcsDefault() const
{
  return m_odcsDefault;
}

void RevisionManifestStart4FND::setOdcsDefault(const quint16& value)
{
  m_odcsDefault = value;
}

void RevisionManifestStart4FND::deserialize(QDataStream& ds)
{
  ds >> m_rid;
  ds >> m_ridDependent;
  ds >> m_timeCreation;
  ds >> m_revisionRole;
  ds >> m_odcsDefault;
}

void RevisionManifestStart4FND::serialize(QDataStream& ds) const
{
  ds << m_rid;
  ds << m_ridDependent;
  ds << m_timeCreation;
  ds << m_revisionRole;
  ds << m_odcsDefault;
}

} // namespace priv
} // namespace libmson
