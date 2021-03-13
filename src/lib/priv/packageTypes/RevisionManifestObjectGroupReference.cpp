#include "RevisionManifestObjectGroupReference.h"

#include "dataTypes/CompactExtGuid.h"

namespace libmson {
namespace fsshttpb {

RevisionManifestObjectGroupReference::RevisionManifestObjectGroupReference() {}

priv::ExtendedGUID RevisionManifestObjectGroupReference::getObjectGroup() const
{
  return m_objectGroup;
}

void RevisionManifestObjectGroupReference::setObjectGroup(
    const priv::ExtendedGUID& objectGroup)
{
  m_objectGroup = objectGroup;
}

quint64 RevisionManifestObjectGroupReference::strObjBody_cb() const
{
  return CompactExtGuid(m_objectGroup).getSizeInFile();
}

quint64 RevisionManifestObjectGroupReference::cbNextHeader() const
{
  return strObjBody_cb();
}

StreamObjectType RevisionManifestObjectGroupReference::getType() const
{
  return StreamObjectType::RevisionManifestObjectGroupReference;
  ;
}

void RevisionManifestObjectGroupReference::push_back(IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(obj);
}

IStreamObj_It_t RevisionManifestObjectGroupReference::insert(
    IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(pos);
  Q_UNUSED(obj);
  m_children.clear();
  return m_children.end();
}

void RevisionManifestObjectGroupReference::deserializeStrObj(QDataStream& ds)
{
  CompactExtGuid guid;
  ds >> guid;
  m_objectGroup = guid.getExtendedGUID();
}

void RevisionManifestObjectGroupReference::serializeStrObj(
    QDataStream& ds) const
{
  ds << CompactExtGuid(m_objectGroup);
}

} // namespace fsshttpb
} // namespace libmson
