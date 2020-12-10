#include "ObjectDeclarationFileData3LargeRefCountFND.h"
#include "../../utils/Helper.h"

namespace libmson {
namespace priv {

ObjectDeclarationFileData3LargeRefCountFND::
    ObjectDeclarationFileData3LargeRefCountFND(FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode)), m_cRef()
{
}

CompactID ObjectDeclarationFileData3LargeRefCountFND::getOid() const
{
  return m_oid;
}

void ObjectDeclarationFileData3LargeRefCountFND::setOid(const CompactID& oid)
{
  m_oid = oid;
}

JCID ObjectDeclarationFileData3LargeRefCountFND::getJcid() const
{
  return m_jcid;
}

void ObjectDeclarationFileData3LargeRefCountFND::setJcid(const JCID& jcid)
{
  m_jcid = jcid;
}

quint32 ObjectDeclarationFileData3LargeRefCountFND::getCRef() const
{
  return m_cRef;
}

void ObjectDeclarationFileData3LargeRefCountFND::setCRef(const quint32& cRef)
{
  m_cRef = cRef;
}

StringInStorageBuffer
ObjectDeclarationFileData3LargeRefCountFND::getFileDataReference() const
{
  return m_FileDataReference;
}

void ObjectDeclarationFileData3LargeRefCountFND::setFileDataReference(
    const StringInStorageBuffer& FileDataReference)
{
  m_FileDataReference = FileDataReference;
}

StringInStorageBuffer
ObjectDeclarationFileData3LargeRefCountFND::getExtension() const
{
  return m_Extension;
}

void ObjectDeclarationFileData3LargeRefCountFND::setExtension(
    const StringInStorageBuffer& Extension)
{
  m_Extension = Extension;
}

quint64 ObjectDeclarationFileData3LargeRefCountFND::getSizeInFile() const
{
  return CompactID::getSizeInFile() + JCID::getSizeInFile() + sizeof(m_cRef) +
         m_FileDataReference.getSizeInFile() + m_Extension.getSizeInFile();
}


void ObjectDeclarationFileData3LargeRefCountFND::deserialize(QDataStream& ds)
{
  ds >> m_oid;
  ds >> m_jcid;
  ds >> m_cRef;
  ds >> m_FileDataReference;
  ds >> m_Extension;
}

void ObjectDeclarationFileData3LargeRefCountFND::serialize(
    QDataStream& ds) const
{
  ds << m_oid;
  ds << m_jcid;
  ds << m_cRef;
  ds << m_FileDataReference;
  ds << m_Extension;
}

} // namespace priv
} // namespace libmson
