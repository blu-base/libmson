#include "ObjectDeclarationFileData3LargeRefCountFND.h"
#include "../../utils/Helper.h"

namespace libmson {
namespace priv {
CompactID ObjectDeclarationFileData3LargeRefCountFND::oid() const
{
  return m_oid;
}

void ObjectDeclarationFileData3LargeRefCountFND::setOid(const CompactID& oid)
{
  m_oid = oid;
}

JCID ObjectDeclarationFileData3LargeRefCountFND::jcid() const { return m_jcid; }

void ObjectDeclarationFileData3LargeRefCountFND::setJcid(const JCID& jcid)
{
  m_jcid = jcid;
}

quint32 ObjectDeclarationFileData3LargeRefCountFND::cRef() const
{
  return m_cRef;
}

void ObjectDeclarationFileData3LargeRefCountFND::setCRef(const quint32& cRef)
{
  m_cRef = cRef;
}

StringInStorageBuffer
ObjectDeclarationFileData3LargeRefCountFND::FileDataReference() const
{
  return m_FileDataReference;
}

void ObjectDeclarationFileData3LargeRefCountFND::setFileDataReference(
    const StringInStorageBuffer& FileDataReference)
{
  m_FileDataReference = FileDataReference;
}

StringInStorageBuffer
ObjectDeclarationFileData3LargeRefCountFND::Extension() const
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

ObjectDeclarationFileData3LargeRefCountFND::
    ObjectDeclarationFileData3LargeRefCountFND(
        RSChunkContainer_WPtr_t parentFileNode)
    : IFileNodeType(parentFileNode), m_cRef()
{
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

// void ObjectDeclarationFileData3LargeRefCountFND::toDebugString(
//    QDebug& dbg) const
//{
//  dbg << " ObjectDeclarationFileData3LargeRefCountFND\n"
//      << " oid: " << m_oid << '\n'
//      << " jcid: " << m_jcid << '\n'
//      << " cRef: " << qStringHex(m_cRef, 8)
//      << '\n'
//      /// \todo get the file name/do something with the stringinstoragebuffer
//      << " FileDataReference:\n"
//      /// \todo get the file name/do something with the stringinstoragebuffer
//      << " Extension:\n"
//      << '\n';
//}

// void ObjectDeclarationFileData3LargeRefCountFND::writeLowLevelXml(
//    QXmlStreamWriter& xmlWriter) const
//{
//  xmlWriter.writeStartElement("ObjectDeclarationFileData3LargeRefCountFND");

//  xmlWriter.writeAttribute("cRef", qStringHex(m_cRef, 8));

//  xmlWriter.writeStartElement("oid");
//  xmlWriter << m_oid;
//  xmlWriter.writeEndElement();

//  xmlWriter.writeStartElement("jcid");
//  xmlWriter << m_jcid;
//  xmlWriter.writeEndElement();

//  xmlWriter << m_FileDataReference;
//  xmlWriter << m_Extension;

//  xmlWriter.writeEndElement();
//}
} // namespace priv
} // namespace libmson
