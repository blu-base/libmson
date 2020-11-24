#include "ObjectDeclarationWithRefCountFNDX.h"

#include "../../utils/Helper.h"
#include "../FileNode.h"

namespace libmson {
namespace priv {

ObjectDeclarationWithRefCountFNDX::ObjectDeclarationWithRefCountFNDX(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode)), m_cRef{}
{
}


ObjectSpaceObjectPropSet_WPtr_t
ObjectDeclarationWithRefCountFNDX::getObjectRef() const
{
  return m_objectRef;
}

void ObjectDeclarationWithRefCountFNDX::setObjectRef(
    const ObjectSpaceObjectPropSet_SPtr_t& value)
{
  m_objectRef = value;
}

ObjectDeclarationWithRefCountBody
ObjectDeclarationWithRefCountFNDX::getBody() const
{
  return m_body;
}

void ObjectDeclarationWithRefCountFNDX::setBody(
    const ObjectDeclarationWithRefCountBody& value)
{
  m_body = value;
}

quint8 ObjectDeclarationWithRefCountFNDX::getCRef() const { return m_cRef; }

void ObjectDeclarationWithRefCountFNDX::setCRef(const quint8& value)
{
  m_cRef = value;
}

quint64 ObjectDeclarationWithRefCountFNDX::getSizeInFile() const
{
  return m_parent.lock()->getFileNodeChunkReferenceSize() +
         m_body.getSizeInFile() + sizeof(m_cRef);
}

// void ObjectDeclarationWithRefCountFNDX::deserialize(QDataStream& ds)
//{
//  ds >> m_objectRef;
//  ds >> m_body;
//  ds >> m_cRef;

//  m_blob = ObjectSpaceObjectPropSet(ds, m_objectRef);
//}

// void ObjectDeclarationWithRefCountFNDX::serialize(QDataStream& ds) const
//{
//  ds << m_objectRef;
//  ds << m_body;
//  ds << m_cRef;
//}

// void ObjectDeclarationWithRefCountFNDX::toDebugString(QDebug& dbg) const
//{
//  dbg << " ObjectDeclarationWithRefCountFNDX:\n"
//      << " objectRef: " << m_objectRef << '\n'
//      << " body: " << m_body << '\n'
//      << " cRef: " << qStringHex(m_cRef, 2) << '\n';
//}

// void ObjectDeclarationWithRefCountFNDX::writeLowLevelXml(
//    QXmlStreamWriter& xmlWriter) const
//{
//  xmlWriter.writeStartElement("ObjectDeclarationWithRefCountFNDX");

//  xmlWriter.writeAttribute("cRef", qStringHex(m_cRef, 2));

//  xmlWriter << m_objectRef;
//  xmlWriter << m_body;

//  xmlWriter << m_blob;

//  xmlWriter.writeEndElement();
//}

} // namespace priv
} // namespace libmson
