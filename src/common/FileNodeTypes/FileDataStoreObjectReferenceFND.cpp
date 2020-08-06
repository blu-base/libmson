#include "FileDataStoreObjectReferenceFND.h"

FileDataStoreObjectReferenceFND::FileDataStoreObjectReferenceFND(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : m_ref(stpFormat, cbFormat) {}

FileDataStoreObjectReferenceFND::FileDataStoreObjectReferenceFND(
    quint8 stpFormat, quint8 cbFormat)
    : m_ref(stpFormat, cbFormat) {}

FileDataStoreObjectReferenceFND::~FileDataStoreObjectReferenceFND() {}

FileNodeChunkReference FileDataStoreObjectReferenceFND::getRef() const {
  return m_ref;
}

void FileDataStoreObjectReferenceFND::setRef(
    const FileNodeChunkReference &value) {
  m_ref = value;
}

QUuid FileDataStoreObjectReferenceFND::getGuidReference() const {
  return m_guidReference;
}

void FileDataStoreObjectReferenceFND::setGuidReference(const QUuid &value) {
  m_guidReference = value;
}

void FileDataStoreObjectReferenceFND::deserialize(QDataStream &ds) {
  ds >> m_ref;
  ds >> m_guidReference;
}

void FileDataStoreObjectReferenceFND::serialize(QDataStream &ds) const {
  ds << m_ref;
  ds << m_guidReference;
}

void FileDataStoreObjectReferenceFND::toDebugString(QDebug dbg) const {
  dbg << " FileDataStoreObjectReferenceFND:\n"
      << " ref: " << m_ref << '\n'
      << " guidReference: " << m_guidReference << '\n';
}


void FileDataStoreObjectReferenceFND::generateXml(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("FileDataStoreObjectReferenceFND");
    m_ref.generateXml(xmlWriter);

    xmlWriter.writeStartElement("guidReference");
    xmlWriter.writeCharacters(m_guidReference.toString());
    xmlWriter.writeEndElement();


    xmlWriter.writeEndElement();
}
