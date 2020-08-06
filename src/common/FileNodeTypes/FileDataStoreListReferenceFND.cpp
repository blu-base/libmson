#include "FileDataStoreListReferenceFND.h"

FileDataStoreListReferenceFND::FileDataStoreListReferenceFND(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : m_ref(stpFormat, cbFormat) {}

FileDataStoreListReferenceFND::FileDataStoreListReferenceFND(quint8 stpFormat,
                                                             quint8 cbFormat)
    : m_ref(stpFormat, cbFormat) {}

FileDataStoreListReferenceFND::~FileDataStoreListReferenceFND() {}

FileNodeChunkReference FileDataStoreListReferenceFND::getRef() const {
  return m_ref;
}

void FileDataStoreListReferenceFND::setRef(
    const FileNodeChunkReference &value) {
  m_ref = value;
}

void FileDataStoreListReferenceFND::deserialize(QDataStream &ds) { ds >> m_ref; }

void FileDataStoreListReferenceFND::serialize(QDataStream &ds) const {
  ds << m_ref;
}

void FileDataStoreListReferenceFND::toDebugString(QDebug dbg) const {
  dbg << " FileDataStoreObjectReferenceFND:\n"
      << " ref: " << m_ref << '\n';
}


void FileDataStoreListReferenceFND::generateXml(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("FileDataStoreListReferenceFND");
    m_ref.generateXml(xmlWriter);
    xmlWriter.writeEndElement();
}
