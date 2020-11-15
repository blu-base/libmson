#include "ObjectDataEncryptionKeyV2FNDX.h"

#include "../../utils/Helper.h"

#include "../FileNode.h"

namespace libmson {
namespace priv {
ObjectDataEncryptionKeyV2FNDX::ObjectDataEncryptionKeyV2FNDX(
    FileNode_WPtr_t parentFileNode)
    : IFileNodeType(parentFileNode)
{
}


EncryptedData_WPtr_t ObjectDataEncryptionKeyV2FNDX::getBlobRef() const
{
  return m_blobRef;
}

void ObjectDataEncryptionKeyV2FNDX::setBlobRef(
    const EncryptedData_WPtr_t& value)
{
  m_blobRef = value;
}

///**
// * @brief ObjectDataEncryptionKeyV2FNDX::deserialize
// * @param ds
// *
// * \todo there is probably an error here
// */
// void ObjectDataEncryptionKeyV2FNDX::deserialize(QDataStream& ds)
//{
//  ds >> m_blobRef;

//  quint64 currentloc = ds.device()->pos();

//  ds.device()->seek(m_blobRef.stp());
//  ds >> m_header;
//  /// \todo read data chunk
//  m_EncryptionData = ds.device()->read(m_blobRef.cb() - 16);
//  ds >> m_footer;

//  ds.device()->seek(currentloc);
//}

///**
// * @brief ObjectDataEncryptionKeyV2FNDX::serialize
// * @param ds
// *
// * \todo figure out when encrypted data should be stored, currently
// * unimplemented
// */
// void ObjectDataEncryptionKeyV2FNDX::serialize(QDataStream& ds) const { ds <<
// m_blobRef; }

// void ObjectDataEncryptionKeyV2FNDX::toDebugString(QDebug& dbg) const
//{
//  dbg << " ObjectDataEncryptionKeyV2FNDX:\n"
//      << " Ref: " << m_ref << '\n';
//}

// void ObjectDataEncryptionKeyV2FNDX::writeLowLevelXml(QXmlStreamWriter&
// xmlWriter) const
//{
//  xmlWriter.writeStartElement("ObjectDataEncryptionKeyV2FNDX");

//  xmlWriter.writeAttribute("header", qStringHex(m_header, 16));
//  xmlWriter.writeAttribute("footer", qStringHex(m_header, 16));

//  xmlWriter << m_ref;

//  xmlWriter.writeStartElement("m_EncryptionData");
//  xmlWriter.writeCDATA(m_EncryptionData);
//  xmlWriter.writeEndElement();

//  xmlWriter.writeEndElement();
//}

quint64 ObjectDataEncryptionKeyV2FNDX::getSizeInFile() const
{
  return m_parent.lock()->getFileNodeChunkReferenceSize();
}

} // namespace priv
} // namespace libmson
