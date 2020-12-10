#include "ObjectRevisionWithRefCountFNDX.h"

#include "../FileNode.h"

namespace libmson {
namespace priv {

ObjectRevisionWithRefCountFNDX::ObjectRevisionWithRefCountFNDX(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode)), m_fHasOidReferences(false),
      m_fHasOsidReferences(false), m_cRef(0)
{
}

bool ObjectRevisionWithRefCountFNDX::getFHasOsidReferences() const
{
  return m_fHasOsidReferences;
}

void ObjectRevisionWithRefCountFNDX::setFHasOsidReferences(bool value)
{
  m_fHasOsidReferences = value;
}

bool ObjectRevisionWithRefCountFNDX::getFHasOidReferences() const
{
  return m_fHasOidReferences;
}

void ObjectRevisionWithRefCountFNDX::setFHasOidReferences(bool value)
{
  m_fHasOidReferences = value;
}

quint8 ObjectRevisionWithRefCountFNDX::getCRef() const { return m_cRef; }

void ObjectRevisionWithRefCountFNDX::setCRef(const quint8& value)
{
  m_cRef = value;
}

CompactID ObjectRevisionWithRefCountFNDX::getOid() const { return m_oid; }

void ObjectRevisionWithRefCountFNDX::setOid(const CompactID& value)
{
  m_oid = value;
}

ObjectSpaceObjectPropSet_WPtr_t ObjectRevisionWithRefCountFNDX::getRef() const
{
  return m_ref;
}

void ObjectRevisionWithRefCountFNDX::setRef(
    const ObjectSpaceObjectPropSet_SPtr_t value)
{
  m_ref = value;
}

quint64 ObjectRevisionWithRefCountFNDX::getSizeInFile() const
{

  return m_parent.lock()->getFileNodeChunkReferenceSize() + sizeInFileBase;
}

} // namespace priv
} // namespace libmson
