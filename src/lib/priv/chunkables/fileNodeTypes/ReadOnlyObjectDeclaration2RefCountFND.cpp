#include "ReadOnlyObjectDeclaration2RefCountFND.h"

#include "../FileNode.h"

namespace libmson {
namespace priv {


ReadOnlyObjectDeclaration2RefCountFND::ReadOnlyObjectDeclaration2RefCountFND(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode)), m_cRef()
{
}


QByteArray ReadOnlyObjectDeclaration2RefCountFND::getMd5hash() const
{
  return m_md5hash;
}

void ReadOnlyObjectDeclaration2RefCountFND::setMd5hash(const QByteArray& value)
{
  m_md5hash = value;
}

quint64 ReadOnlyObjectDeclaration2RefCountFND::getSizeInFile() const
{
  return md5HashSize + m_parent.lock()->getFileNodeChunkReferenceSize() +
         ObjectDeclaration2Body::getSizeInFile() + 1;
}

quint8 ReadOnlyObjectDeclaration2RefCountFND::getCRef() const { return m_cRef; }

void ReadOnlyObjectDeclaration2RefCountFND::setCRef(const quint8& value)
{
  m_cRef = value;
}

ObjectDeclaration2Body ReadOnlyObjectDeclaration2RefCountFND::getBody() const
{
  return m_body;
}

void ReadOnlyObjectDeclaration2RefCountFND::setBody(
    const ObjectDeclaration2Body& value)
{
  m_body = value;
}


ObjectSpaceObjectPropSet_WPtr_t
ReadOnlyObjectDeclaration2RefCountFND::getBlobRef()
{
  return m_blobRef;
}

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
