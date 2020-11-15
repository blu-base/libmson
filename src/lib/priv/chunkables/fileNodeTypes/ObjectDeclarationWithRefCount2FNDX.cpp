#include "ObjectDeclarationWithRefCount2FNDX.h"

#include "../../utils/Helper.h"
#include "../FileNode.h"

namespace libmson {
namespace priv {

ObjectDeclarationWithRefCount2FNDX::ObjectDeclarationWithRefCount2FNDX(
    FileNode_WPtr_t parentFileNode)
    : IFileNodeType(parentFileNode), m_cRef()
{
}

ObjectSpaceObjectPropSet_WPtr_t
ObjectDeclarationWithRefCount2FNDX::getObjectRef() const
{
  return m_objectRef;
}

void ObjectDeclarationWithRefCount2FNDX::setObjectRef(
    const ObjectSpaceObjectPropSet_WPtr_t& value)
{
  m_objectRef = value;
}

ObjectDeclarationWithRefCountBody
ObjectDeclarationWithRefCount2FNDX::getBody() const
{
  return m_body;
}

void ObjectDeclarationWithRefCount2FNDX::setBody(
    const ObjectDeclarationWithRefCountBody& value)
{
  m_body = value;
}

quint32 ObjectDeclarationWithRefCount2FNDX::getCRef() const { return m_cRef; }

void ObjectDeclarationWithRefCount2FNDX::setCRef(const quint32& value)
{
  m_cRef = value;
}

quint64 ObjectDeclarationWithRefCount2FNDX::getSizeInFile() const
{
  return m_parent.lock()->getFileNodeChunkReferenceSize() +
         m_body.getSizeInFile() + sizeof(m_cRef);
}

// void ObjectDeclarationWithRefCount2FNDX::deserialize(QDataStream &ds) {
//  ds >> m_objectRef;
//  ds >> m_body;
//  ds >> m_cRef;

//  m_blob = ObjectSpaceObjectPropSet(ds, m_objectRef);
//}

// void ObjectDeclarationWithRefCount2FNDX::serialize(QDataStream &ds) const {
//  ds << m_objectRef;
//  ds << m_body;
//  ds << m_cRef;
//}

// void ObjectDeclarationWithRefCount2FNDX::toDebugString(QDebug &dbg) const {
//  dbg << " ObjectDeclarationWithRefCount2FNDX:\n"
//      << " objectRef: " << m_objectRef << '\n'
//      << " body: " << m_body << '\n'
//      << " cRef: " << m_cRef << '\n';
//}

// void ObjectDeclarationWithRefCount2FNDX::writeLowLevelXml(
//    QXmlStreamWriter &xmlWriter) const {
//  xmlWriter.writeStartElement("ObjectDeclarationWithRefCount2FNDX");

//  xmlWriter.writeAttribute("cRef", qStringHex(m_cRef, 8));

//  xmlWriter << m_objectRef;
//  xmlWriter << m_body;

//  xmlWriter << m_blob;

//  xmlWriter.writeEndElement();
//}

} // namespace priv
} // namespace libmson
