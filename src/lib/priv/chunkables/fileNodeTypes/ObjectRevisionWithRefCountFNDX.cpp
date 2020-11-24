#include "ObjectRevisionWithRefCountFNDX.h"

#include "../FileNode.h"

namespace libmson {
namespace priv {

ObjectRevisionWithRefCountFNDX::ObjectRevisionWithRefCountFNDX(
    FileNode_WPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode)), m_fHasOidReferences(false),
      m_fHasOsidReferences(false), m_cRef(0)
{
}

bool ObjectRevisionWithRefCountFNDX::getFHasOsidReferences() const
{
  return m_fHasOsidReferences;
}

void ObjectRevisionWithRefCountFNDX::setFHasOsidReferences(bool value)
{
  m_fHasOsidReferences = value;
}

bool ObjectRevisionWithRefCountFNDX::getFHasOidReferences() const
{
  return m_fHasOidReferences;
}

void ObjectRevisionWithRefCountFNDX::setFHasOidReferences(bool value)
{
  m_fHasOidReferences = value;
}

quint8 ObjectRevisionWithRefCountFNDX::getCRef() const { return m_cRef; }

void ObjectRevisionWithRefCountFNDX::setCRef(const quint8& value)
{
  m_cRef = value;
}

CompactID ObjectRevisionWithRefCountFNDX::getOid() const { return m_oid; }

void ObjectRevisionWithRefCountFNDX::setOid(const CompactID& value)
{
  m_oid = value;
}

ObjectSpaceObjectPropSet_WPtr_t ObjectRevisionWithRefCountFNDX::getRef() const
{
  return m_ref;
}

void ObjectRevisionWithRefCountFNDX::setRef(
    const ObjectSpaceObjectPropSet_WPtr_t value)
{
  m_ref = value;
}

quint64 ObjectRevisionWithRefCountFNDX::getSizeInFile() const
{

  return m_parent.lock()->getFileNodeChunkReferenceSize() + sizeInFileBase;
}

// void ObjectRevisionWithRefCountFNDX::deserialize(QDataStream &ds) {

//  ds.setByteOrder(QDataStream::LittleEndian);

//  ds >> m_ref;
//  ds >> m_oid;
//  ds >> m_cRef;
//  m_fHasOidReferences = ((m_cRef & 0x1) != 0u);
//  m_fHasOsidReferences = ((m_cRef & 0x2) != 0u);
//  m_cRef = m_cRef >> 2;

//  m_blob = ObjectSpaceObjectPropSet(ds, m_ref);
//}

// void ObjectRevisionWithRefCountFNDX::serialize(QDataStream &ds) const {

//  ds.setByteOrder(QDataStream::LittleEndian);

//  ds << m_ref;
//  ds << m_oid;

//  quint8 temp = m_cRef >> 2;
//  temp += static_cast<quint32>(m_fHasOidReferences);
//  temp += static_cast<quint32>(m_fHasOsidReferences) << 1;

//  ds << temp;
//}

// void ObjectRevisionWithRefCountFNDX::toDebugString(QDebug &dbg) const {
//  dbg << " ObjectRevisionWithRefCountFNDX:\n"
//      << " Ref: " << m_ref << "oid: " << m_oid << "cRef: " << m_cRef
//      << " fHasOidReferences: " << m_fHasOidReferences
//      << " fHasOsidReferences: " << m_fHasOsidReferences << '\n';
//}

// void ObjectRevisionWithRefCountFNDX::writeLowLevelXml(
//    QXmlStreamWriter &xmlWriter) const {
//  xmlWriter.writeStartElement("ObjectRevisionWithRefCountFNDX");

//  xmlWriter.writeAttribute("cRef", qStringHex(m_cRef, 8));
//  xmlWriter.writeAttribute("fHasOidReferences",
//                           m_fHasOidReferences ? "true" : "false");
//  xmlWriter.writeAttribute("fHasOsidReferences",
//                           m_fHasOsidReferences ? "true" : "false");

//  xmlWriter << m_ref;

//  xmlWriter << m_oid;

//  xmlWriter << m_blob;

//  xmlWriter.writeEndElement();
//}

} // namespace priv
} // namespace libmson