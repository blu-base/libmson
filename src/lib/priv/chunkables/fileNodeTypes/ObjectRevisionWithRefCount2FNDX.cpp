#include "ObjectRevisionWithRefCount2FNDX.h"

#include "../../utils/Helper.h"
#include "../FileNode.h"

namespace libmson {
namespace priv {

ObjectRevisionWithRefCount2FNDX::ObjectRevisionWithRefCount2FNDX(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode)), m_fHasOidReferences(false),
      m_fHasOsidReferences(false), m_cRef(0)
{
}

quint32 ObjectRevisionWithRefCount2FNDX::getCRef() const { return m_cRef; }

void ObjectRevisionWithRefCount2FNDX::setCRef(const quint32& value)
{
  m_cRef = value;
}

bool ObjectRevisionWithRefCount2FNDX::getFHasOsidReferences() const
{
  return m_fHasOsidReferences;
}

void ObjectRevisionWithRefCount2FNDX::setFHasOsidReferences(bool value)
{
  m_fHasOsidReferences = value;
}

bool ObjectRevisionWithRefCount2FNDX::getFHasOidReferences() const
{
  return m_fHasOidReferences;
}

void ObjectRevisionWithRefCount2FNDX::setFHasOidReferences(bool value)
{
  m_fHasOidReferences = value;
}

CompactID ObjectRevisionWithRefCount2FNDX::getOid() const { return m_oid; }

void ObjectRevisionWithRefCount2FNDX::setOid(const CompactID& value)
{
  m_oid = value;
}

ObjectSpaceObjectPropSet_WPtr_t ObjectRevisionWithRefCount2FNDX::getRef() const
{
  return m_ref;
}

void ObjectRevisionWithRefCount2FNDX::setRef(
    const ObjectSpaceObjectPropSet_SPtr_t value)
{
  m_ref = value;
}


quint64 ObjectRevisionWithRefCount2FNDX::getSizeInFile() const
{
  return m_parent.lock()->getFileNodeChunkReferenceSize() + sizeInFileBase;
}

// void ObjectRevisionWithRefCount2FNDX::deserialize(QDataStream &ds) {
//  ds >> m_ref;
//  ds >> m_oid;

//  quint32 temp = 0;
//  ds >> temp;

//  m_fHasOidReferences = static_cast<bool>(temp & 0x1);
//  m_fHasOsidReferences = static_cast<bool>((temp & 0x2) >> 1);

//  ds >> m_cRef;

//  m_blob = ObjectSpaceObjectPropSet(ds, m_ref);
//}

// void ObjectRevisionWithRefCount2FNDX::serialize(QDataStream &ds) const {
//  ds << m_ref;
//  ds << m_oid;

//  quint32 temp{0};

//  temp += static_cast<quint32>(m_fHasOidReferences);
//  temp += static_cast<quint32>(m_fHasOsidReferences << 1);

//  ds << temp;

//  ds << m_cRef;
//}

// void ObjectRevisionWithRefCount2FNDX::toDebugString(QDebug &dbg) const {
//  dbg << " ObjectRevisionWithRefCount2FNDX: \n"
//      << " ref: " << m_ref << "oid: " << m_oid
//      << " fHasOidReferences: " << m_fHasOidReferences
//      << " fHasOsidReferences: " << m_fHasOsidReferences << "cRef: " <<
//      m_cRef;
//}

// void ObjectRevisionWithRefCount2FNDX::writeLowLevelXml(
//    QXmlStreamWriter &xmlWriter) const {

//  xmlWriter.writeStartElement("ObjectRevisionWithRefCount2FNDX");

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
