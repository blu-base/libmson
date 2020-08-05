#include "ObjectDeclarationFileData3RefCountFND.h"
#include "../helper/Helper.h"

CompactID ObjectDeclarationFileData3RefCountFND::oid() const
{
    return m_oid;
}

void ObjectDeclarationFileData3RefCountFND::setOid(const CompactID& oid)
{
    m_oid = oid;
}

JCID ObjectDeclarationFileData3RefCountFND::jcid() const
{
    return m_jcid;
}

void ObjectDeclarationFileData3RefCountFND::setJcid(const JCID& jcid)
{
    m_jcid = jcid;
}

quint8 ObjectDeclarationFileData3RefCountFND::cRef() const
{
    return m_cRef;
}

void ObjectDeclarationFileData3RefCountFND::setCRef(const quint8& cRef)
{
    m_cRef = cRef;
}

StringInStorageBuffer ObjectDeclarationFileData3RefCountFND::FileDataReference() const
{
    return m_FileDataReference;
}

void ObjectDeclarationFileData3RefCountFND::setFileDataReference(const StringInStorageBuffer& FileDataReference)
{
    m_FileDataReference = FileDataReference;
}

StringInStorageBuffer ObjectDeclarationFileData3RefCountFND::Extension() const
{
    return m_Extension;
}

void ObjectDeclarationFileData3RefCountFND::setExtension(const StringInStorageBuffer& Extension)
{
    m_Extension = Extension;
}

ObjectDeclarationFileData3RefCountFND::ObjectDeclarationFileData3RefCountFND()
{

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

void ObjectDeclarationFileData3RefCountFND::toDebugString(QDebug dbg) const
{
    dbg << " ObjectDeclarationFileData3RefCountFND\n"
        << " oid: " << m_oid << '\n'
        << " jcid: " << m_jcid << '\n'
        << " cRef: " << qStringHex(m_cRef,4) << '\n'
           /// \todo get the file name/do something with the stringinstoragebuffer
        << " FileDataReference:\n"
           /// \todo get the file name/do something with the stringinstoragebuffer
        << " Extension:\n"
        << '\n';
}