#include "RevisionManifest.h"

#include "dataTypes/CompactExtGuid.h"

namespace libmson {
namespace fsshttpb {


RevisionManifest::RevisionManifest() {}

priv::ExtendedGUID RevisionManifest::getRevisionId() const
{
  return m_revisionId;
}

void RevisionManifest::setRevisionId(const priv::ExtendedGUID& revisionId)
{
  m_revisionId = revisionId;
}

priv::ExtendedGUID RevisionManifest::getBaseRevisionId() const
{
  return m_baseRevisionId;
}

void RevisionManifest::setBaseRevisionId(
    const priv::ExtendedGUID& baseRevisionId)
{
  m_baseRevisionId = baseRevisionId;
}

quint64 RevisionManifest::strObjBody_cb() const
{
  return CompactExtGuid(m_revisionId).getSizeInFile() +
         CompactExtGuid(m_baseRevisionId).getSizeInFile();
}

quint64 RevisionManifest::cbNextHeader() const
{
  return strObjBody_cb();
}

StreamObjectType RevisionManifest::getType() const
{

  return StreamObjectType::RevisionManifest;
}

void RevisionManifest::push_back(fsshttpb::IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(obj);
}

IStreamObj_It_t
RevisionManifest::insert(IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(pos);
  Q_UNUSED(obj);
  m_children.clear();
  return m_children.end();
}

void RevisionManifest::deserializeStrObj(QDataStream& ds)
{
  CompactExtGuid guid;
  ds >> guid;
  m_revisionId = guid.getExtendedGUID();
  ds >> guid;
  m_baseRevisionId = guid.getExtendedGUID();
}

void RevisionManifest::serializeStrObj(QDataStream& ds) const
{
  ds << CompactExtGuid(m_revisionId);
  ds << CompactExtGuid(m_baseRevisionId);
}


} // namespace fsshttpb
} // namespace libmson
