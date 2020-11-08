#include "FileDataStoreListReferenceFND.h"

namespace libmson{
namespace priv{
FileDataStoreListReferenceFND::FileDataStoreListReferenceFND(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : m_ref(stpFormat, cbFormat) {}

FileDataStoreListReferenceFND::FileDataStoreListReferenceFND(quint8 stpFormat,
                                                             quint8 cbFormat)
    : m_ref(stpFormat, cbFormat) {}


FileNodeChunkReference FileDataStoreListReferenceFND::getRef() const {
  return m_ref;
}

void FileDataStoreListReferenceFND::setRef(
    const MSONcommon::FileNodeChunkReference &value) {
  m_ref = value;
}

void FileDataStoreListReferenceFND::deserialize(QDataStream &ds) {
  ds >> m_ref;

  m_StoreList = MSONcommon::FileNodeListFragment(m_ref);
  ds >> m_StoreList;
}

void FileDataStoreListReferenceFND::serialize(QDataStream &ds) const {
  ds << m_ref;
}

void FileDataStoreListReferenceFND::toDebugString(QDebug &dbg) const {
  dbg << " FileDataStoreObjectReferenceFND:\n"
      << " ref: " << m_ref << '\n';
}

void FileDataStoreListReferenceFND::writeLowLevelXml(
    QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("FileDataStoreListReferenceFND");
  xmlWriter << m_ref;

  xmlWriter << m_StoreList;
  xmlWriter.writeEndElement();
}

quint64 MSONcommon::FileDataStoreListReferenceFND::getSizeInFile() const
{ return m_ref.getSizeInFile();
}

} //namespace priv
} // namespace libmson


