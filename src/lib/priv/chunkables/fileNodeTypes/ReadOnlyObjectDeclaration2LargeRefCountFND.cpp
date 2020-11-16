#include "ReadOnlyObjectDeclaration2LargeRefCountFND.h"

namespace libmson {
namespace priv {


ReadOnlyObjectDeclaration2LargeRefCountFND::
    ReadOnlyObjectDeclaration2LargeRefCountFND(FileNode_WPtr_t parentFileNode)
    : IFileNodeType(parentFileNode)
{
}


QByteArray ReadOnlyObjectDeclaration2LargeRefCountFND::getMd5hash() const
{
  return m_md5hash;
}

void ReadOnlyObjectDeclaration2LargeRefCountFND::setMd5hash(
    const QByteArray& value)
{
  m_md5hash = value;
}

quint64 ReadOnlyObjectDeclaration2LargeRefCountFND::getSizeInFile() const
{
  return md5HashSize + m_parent.lock()->getFileNodeChunkReferenceSize() +
         ObjectDeclaration2Body::getSizeInFile() + 4;
}

ObjectSpaceObjectPropSet_WPtr_t
ReadOnlyObjectDeclaration2LargeRefCountFND::getBlobRef()
{
  return m_blobRef;
}

void ReadOnlyObjectDeclaration2LargeRefCountFND::setBlobRef(
    const ObjectSpaceObjectPropSet_WPtr_t& blobRef)
{
  m_blobRef = blobRef;
}

ObjectDeclaration2Body
ReadOnlyObjectDeclaration2LargeRefCountFND::getBody() const
{
  return m_body;
}

void ReadOnlyObjectDeclaration2LargeRefCountFND::setBody(
    const ObjectDeclaration2Body& body)
{
  m_body = body;
}

quint32 ReadOnlyObjectDeclaration2LargeRefCountFND::getCRef() const
{
  return m_cRef;
}

void ReadOnlyObjectDeclaration2LargeRefCountFND::setCRef(const quint32& cRef)
{
  m_cRef = cRef;
}


// void ReadOnlyObjectDeclaration2LargeRefCountFND::deserialize(QDataStream &ds)
// {

//  m_base = ObjectDeclaration2LargeRefCountFND(m_stpFormat, m_cbFormat);
//  ds >> m_base;

//  m_md5hash = ds.device()->read(md5HashSize);
//}

// void ReadOnlyObjectDeclaration2LargeRefCountFND::serialize(
//    QDataStream &ds) const {

//  ds << m_base;
//  ds << m_md5hash;
//}

// void ReadOnlyObjectDeclaration2LargeRefCountFND::toDebugString(
//    QDebug &dbg) const {

//  dbg << " ReadOnlyObjectDeclaration2LargeRefCountFND\n"
//      << " Base:\n"
//      << m_base << "\nmd5hash: " << m_md5hash.toHex() << '\n';
//}

// void ReadOnlyObjectDeclaration2LargeRefCountFND::writeLowLevelXml(
//    QXmlStreamWriter &xmlWriter) const {

//  xmlWriter.writeStartElement("ReadOnlyObjectDeclaration2LargeRefCountFND");

//  xmlWriter << m_base;

//  xmlWriter.writeStartElement("md5hash");
//  xmlWriter.writeCharacters(m_md5hash.toHex());
//  xmlWriter.writeEndElement();

//  xmlWriter.writeEndElement();
//}

} // namespace priv
} // namespace libmson
