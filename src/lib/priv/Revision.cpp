#include "Revision.h"


namespace libmson {
namespace priv {

libmson::priv::Revision::Revision() {}

Revision::Revision(
    const std::map<quint32, QUuid>& globalId,
    const std::list<FileNode_WPtr_t>& manifestList, const ExtendedGUID& gosid,
    const ExtendedGUID& dependent)
    : m_globalId(globalId), m_manifestList(manifestList), m_gosid(gosid),
      m_dependent(dependent)
{
}


std::map<quint32, QUuid> Revision::getGlobalId() const
{
  return m_globalId;
}

void Revision::setGlobalId(const std::map<quint32, QUuid>& globalId)
{
  m_globalId = globalId;
}

std::list<FileNode_WPtr_t> Revision::getManifestList() const
{
  return m_manifestList;
}

void Revision::setManifestList(const std::list<FileNode_WPtr_t>& manifestList)
{
  m_manifestList = manifestList;
}

ExtendedGUID Revision::getGosid() const
{
  return m_gosid;
}

void Revision::setGosid(const ExtendedGUID& gosid)
{
  m_gosid = gosid;
}

ExtendedGUID Revision::getDependent() const
{
  return m_dependent;
}

void Revision::setDependent(const ExtendedGUID& dependent)
{
  m_dependent = dependent;
}



} // namespace priv
} // namespace libmson
