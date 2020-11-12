#include "ReadOnlyObjectDeclaration2LargeRefCountFND.h"

namespace libmson {
namespace priv {


ReadOnlyObjectDeclaration2LargeRefCountFND::
    ReadOnlyObjectDeclaration2LargeRefCountFND(
        RSChunkContainer_WPtr_t parentFileNode)
    : IFileNodeType(parentFileNode), m_base(parentFileNode)
{
}

RSChunkContainer_WPtr_t
ReadOnlyObjectDeclaration2LargeRefCountFND::getBlobRef() const
{
  return m_base.getBlobRef();
}

ObjectDeclaration2Body
ReadOnlyObjectDeclaration2LargeRefCountFND::getBody() const
{
  return m_base.getBody();
}


ObjectDeclaration2LargeRefCountFND
ReadOnlyObjectDeclaration2LargeRefCountFND::getBase() const
{
  return m_base;
}

void ReadOnlyObjectDeclaration2LargeRefCountFND::setBase(
    const ObjectDeclaration2LargeRefCountFND& value)
{
  m_base = value;
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

std::shared_ptr<ObjectSpaceObjectPropSet>
ReadOnlyObjectDeclaration2LargeRefCountFND::getPropSet()
{
  return m_base.getPropSet();
}

quint64 ReadOnlyObjectDeclaration2LargeRefCountFND::getSizeInFile() const
{
  return md5HashSize + m_base.getSizeInFile();
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
