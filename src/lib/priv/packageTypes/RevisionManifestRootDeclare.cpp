#include "RevisionManifestRootDeclare.h"

#include "dataTypes/CompactExtGuid.h"

namespace libmson {
namespace fsshttpb {

RevisionManifestRootDeclare::RevisionManifestRootDeclare()
    : m_root(), m_object()
{
}

priv::ExtendedGUID RevisionManifestRootDeclare::getRootGUID() const
{
  return m_root;
}

void RevisionManifestRootDeclare::setRootGUID(const priv::ExtendedGUID& root)
{
  m_root = root;
}

priv::ExtendedGUID RevisionManifestRootDeclare::getObjectGUID() const
{
  return m_object;
}

void RevisionManifestRootDeclare::setObjectGUID(const priv::ExtendedGUID& object)
{
  m_object = object;
}

quint64 RevisionManifestRootDeclare::strObjBody_cb() const
{
  if (m_set) {
    return CompactExtGuid(m_root).getSizeInFile() +
           CompactExtGuid(m_object).getSizeInFile();
  }

  return 0;
}

quint64 RevisionManifestRootDeclare::cbNextHeader() const
{
  return strObjBody_cb();
}

StreamObjectType RevisionManifestRootDeclare::getType() const
{
  return StreamObjectType::RevisionManifestRootDeclare;
}

void RevisionManifestRootDeclare::push_back(IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(obj);
}

IStreamObj_It_t RevisionManifestRootDeclare::insert(
    IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(pos);
  Q_UNUSED(obj);
  m_children.clear();
  return m_children.end();
}

void RevisionManifestRootDeclare::deserializeStrObj(QDataStream& ds)
{
  if (m_cbNxtHd == 0) {
    m_set = false;
    return;
  }
  m_set = true;

  auto curPos = ds.device()->pos();

  CompactExtGuid guid;
  ds >> guid;
  m_root = guid.getExtendedGUID();

  auto diff = ds.device()->pos() - curPos;

  if (diff == 0) {
    return;
  }


  ds >> guid;
  m_object = guid.getExtendedGUID();
}

void RevisionManifestRootDeclare::serializeStrObj(QDataStream& ds) const
{
  if (m_set) {
    ds << CompactExtGuid(m_root);
    ds << CompactExtGuid(m_object);
  }
}


} // namespace fsshttpb
} // namespace libmson
