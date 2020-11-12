#include "ReadOnlyObjectDeclaration2RefCountFND.h"


namespace libmson {
namespace priv {


ReadOnlyObjectDeclaration2RefCountFND::ReadOnlyObjectDeclaration2RefCountFND(
    RSChunkContainer_WPtr_t parentFileNode)
    : IFileNodeType(parentFileNode), m_base(parentFileNode)
{
}


ObjectDeclaration2RefCountFND
ReadOnlyObjectDeclaration2RefCountFND::getBase() const
{
  return m_base;
}

void ReadOnlyObjectDeclaration2RefCountFND::setBase(
    const ObjectDeclaration2RefCountFND& value)
{
  m_base = value;
}

QByteArray ReadOnlyObjectDeclaration2RefCountFND::getMd5hash() const
{
  return m_md5hash;
}

void ReadOnlyObjectDeclaration2RefCountFND::setMd5hash(const QByteArray& value)
{
  m_md5hash = value;
}

RSChunkContainer_WPtr_t
ReadOnlyObjectDeclaration2RefCountFND::getBlobRef() const
{
  return m_base.getBlobRef();
}

ObjectDeclaration2Body ReadOnlyObjectDeclaration2RefCountFND::getBody() const
{
  return m_base.getBody();
}

std::shared_ptr<ObjectSpaceObjectPropSet>
ReadOnlyObjectDeclaration2RefCountFND::getPropSet()
{
  return m_base.getPropSet();
}

quint64 ReadOnlyObjectDeclaration2RefCountFND::getSizeInFile() const
{
  return md5HashSize + m_base.getSizeInFile();
}

// void ReadOnlyObjectDeclaration2RefCountFND::deserialize(QDataStream &ds) {

//  m_base = ObjectDeclaration2RefCountFND(m_stpFormat, m_cbFormat);
//  ds >> m_base;

//  m_md5hash = ds.device()->read(md5HashSize);
//}

// void ReadOnlyObjectDeclaration2RefCountFND::serialize(QDataStream &ds) const
// {

//  ds << m_base;
//  ds << m_md5hash;
//}

// void ReadOnlyObjectDeclaration2RefCountFND::toDebugString(QDebug &dbg) const
// {

//  dbg << " ReadOnlyObjectDeclaration2RefCountFND\n"
//      << " Base:\n"
//      << m_base << '\n'
//      << " md5hash: " << m_md5hash.toHex() << '\n';
//}

// void ReadOnlyObjectDeclaration2RefCountFND::writeLowLevelXml(
//    QXmlStreamWriter &xmlWriter) const {

//  xmlWriter.writeStartElement("ReadOnlyObjectDeclaration2RefCountFND");

//  xmlWriter << m_base;

//  xmlWriter.writeStartElement("md5hash");
//  xmlWriter.writeCharacters(m_md5hash.toHex());
//  xmlWriter.writeEndElement();

//  xmlWriter.writeEndElement();
//}

} // namespace priv
} // namespace libmson
