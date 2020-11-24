#include "FileDataStoreObjectReferenceFND.h"

#include "../FileNode.h"

namespace libmson {
namespace priv {
FileDataStoreObjectReferenceFND::FileDataStoreObjectReferenceFND(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode))
{
}

FileDataStoreObject_WPtr_t FileDataStoreObjectReferenceFND::getBlobRef() const
{
  return m_blobRef;
}

void FileDataStoreObjectReferenceFND::setBlobRef(
    const FileDataStoreObject_SPtr_t& value)
{
  m_blobRef = value;
}

QUuid FileDataStoreObjectReferenceFND::getGuidReference() const
{
  return m_guidReference;
}

void FileDataStoreObjectReferenceFND::setGuidReference(const QUuid& value)
{
  m_guidReference = value;
}


/*void FileDataStoreObjectReferenceFND::deserialize(QDataStream &ds) {
  ds >> m_ref;
  ds >> m_guidReference;

  m_blob = FileDataStoreObject(ds, m_ref);
}

void FileDataStoreObjectReferenceFND::serialize(QDataStream &ds) const {
  ds << m_ref;
  ds << m_guidReference;
}

void FileDataStoreObjectReferenceFND::toDebugString(QDebug &dbg) const {
  dbg << " FileDataStoreObjectReferenceFND:\n"
      << " ref: " << m_ref << '\n'
      << " guidReference: " << m_guidReference << '\n';
}

void FileDataStoreObjectReferenceFND::writeLowLevelXml(
    QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("FileDataStoreObjectReferenceFND");
  xmlWriter << m_ref;

  xmlWriter.writeStartElement("guidReference");
  xmlWriter.writeCharacters(m_guidReference.toString());
  xmlWriter.writeEndElement();

  xmlWriter << m_blob;

  xmlWriter.writeEndElement();
}*/

quint64 FileDataStoreObjectReferenceFND::getSizeInFile() const
{
  return m_parent.lock()->getFileNodeChunkReferenceSize() + sizeOfGUID;
}

} // namespace priv
} // namespace libmson
