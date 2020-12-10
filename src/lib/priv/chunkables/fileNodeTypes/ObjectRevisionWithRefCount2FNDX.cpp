#include "ObjectRevisionWithRefCount2FNDX.h"

#include "../../utils/Helper.h"
#include "../FileNode.h"

namespace libmson {
namespace priv {

ObjectRevisionWithRefCount2FNDX::ObjectRevisionWithRefCount2FNDX(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode)), m_fHasOidReferences(false),
      m_fHasOsidReferences(false), m_cRef(0)
{
}

quint32 ObjectRevisionWithRefCount2FNDX::getCRef() const { return m_cRef; }

void ObjectRevisionWithRefCount2FNDX::setCRef(const quint32& value)
{
  m_cRef = value;
}

bool ObjectRevisionWithRefCount2FNDX::getFHasOsidReferences() const
{
  return m_fHasOsidReferences;
}

void ObjectRevisionWithRefCount2FNDX::setFHasOsidReferences(bool value)
{
  m_fHasOsidReferences = value;
}

bool ObjectRevisionWithRefCount2FNDX::getFHasOidReferences() const
{
  return m_fHasOidReferences;
}

void ObjectRevisionWithRefCount2FNDX::setFHasOidReferences(bool value)
{
  m_fHasOidReferences = value;
}

CompactID ObjectRevisionWithRefCount2FNDX::getOid() const { return m_oid; }

void ObjectRevisionWithRefCount2FNDX::setOid(const CompactID& value)
{
  m_oid = value;
}

ObjectSpaceObjectPropSet_WPtr_t ObjectRevisionWithRefCount2FNDX::getRef() const
{
  return m_ref;
}

void ObjectRevisionWithRefCount2FNDX::setRef(
    const ObjectSpaceObjectPropSet_SPtr_t value)
{
  m_ref = value;
}


quint64 ObjectRevisionWithRefCount2FNDX::getSizeInFile() const
{
  return m_parent.lock()->getFileNodeChunkReferenceSize() + sizeInFileBase;
}

} // namespace priv
} // namespace libmson
