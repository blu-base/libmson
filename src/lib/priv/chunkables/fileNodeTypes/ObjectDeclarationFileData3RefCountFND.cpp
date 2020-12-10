#include "ObjectDeclarationFileData3RefCountFND.h"
#include "../../utils/Helper.h"

namespace libmson {
namespace priv {

ObjectDeclarationFileData3RefCountFND::ObjectDeclarationFileData3RefCountFND(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode)), m_cRef(0)
{
}

CompactID ObjectDeclarationFileData3RefCountFND::getOid() const
{
  return m_oid;
}

void ObjectDeclarationFileData3RefCountFND::setOid(const CompactID& oid)
{
  m_oid = oid;
}

JCID ObjectDeclarationFileData3RefCountFND::getJcid() const { return m_jcid; }

void ObjectDeclarationFileData3RefCountFND::setJcid(const JCID& jcid)
{
  m_jcid = jcid;
}

quint8 ObjectDeclarationFileData3RefCountFND::getCRef() const { return m_cRef; }

void ObjectDeclarationFileData3RefCountFND::setCRef(const quint8& cRef)
{
  m_cRef = cRef;
}

StringInStorageBuffer
ObjectDeclarationFileData3RefCountFND::getFileDataReference() const
{
  return m_FileDataReference;
}

void ObjectDeclarationFileData3RefCountFND::setFileDataReference(
    const StringInStorageBuffer& FileDataReference)
{
  m_FileDataReference = FileDataReference;
}

StringInStorageBuffer
ObjectDeclarationFileData3RefCountFND::getExtension() const
{
  return m_Extension;
}

void ObjectDeclarationFileData3RefCountFND::setExtension(
    const StringInStorageBuffer& Extension)
{
  m_Extension = Extension;
}

quint64 ObjectDeclarationFileData3RefCountFND::getSizeInFile() const
{
  return CompactID::getSizeInFile() + JCID::getSizeInFile() + sizeof(m_cRef) +
         m_FileDataReference.getSizeInFile() + m_Extension.getSizeInFile();
}


void ObjectDeclarationFileData3RefCountFND::deserialize(QDataStream& ds)
{
  ds >> m_oid;
  ds >> m_jcid;
  ds >> m_cRef;
  ds >> m_FileDataReference;
  ds >> m_Extension;
}

void ObjectDeclarationFileData3RefCountFND::serialize(QDataStream& ds) const
{
  ds << m_oid;
  ds << m_jcid;
  ds << m_cRef;
  ds << m_FileDataReference;
  ds << m_Extension;
}

} // namespace priv
} // namespace libmson
