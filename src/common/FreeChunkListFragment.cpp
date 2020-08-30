#include "FreeChunkListFragment.h"
#include "helper/Helper.h"
namespace MSONcommon {
void FreeChunkListFragment::deserialize(QDataStream &ds) {

  qDebug() << "FreeChunkListFragment: Reading at pos in file: "
           << qStringHex(ds.device()->pos(), 16);
  ds >> crc;
  ds >> fcrNextChunk;

  quint64 chunksToRead = m_size / 16 - 1;

  for (size_t i{0}; i < chunksToRead; i++) {
    FileChunkReference64 temp;
    ds >> temp;
    fcrFreeChunk.push_back(temp);
  }

  qDebug() << "FreeChunkListFragment: Finished at pos in file: "
           << qStringHex(ds.device()->pos(), 16);
}

void FreeChunkListFragment::serialize(QDataStream &ds) const {
  ds << crc;
  ds << fcrNextChunk;

  for (size_t i{0}; i < fcrFreeChunk.size(); i++) {
    ds << fcrFreeChunk.at(i);
  }
}

void FreeChunkListFragment::toDebugString(QDebug dbg) const {
  dbg.noquote() << "FreeChunkListFragment:  size: "
                << QString("0x%1").arg(m_size, 16, 16, QLatin1Char('0')) << '\n'
                << " fcrNextChunk: " << fcrNextChunk << '\n';

  for (size_t i{0}; i < fcrFreeChunk.size(); i++) {
    dbg.noquote() << fcrFreeChunk.at(i) << '\n';
  }
}

FreeChunkListFragment::FreeChunkListFragment(quint64 size)
    : m_size{size}, crc{} {}

QDataStream &operator<<(QDataStream &ds, const FreeChunkListFragment &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, FreeChunkListFragment &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const FreeChunkListFragment &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

void FreeChunkListFragment::generateXml(QXmlStreamWriter &xmlWriter) const {

  xmlWriter.writeStartElement("FreeChunkListFragment");

  xmlWriter.writeStartElement("size");
  xmlWriter.writeCharacters(qStringHex(m_size, 16));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("crc");
  xmlWriter.writeCharacters(qStringHex(crc, 8));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fcrNextChunk");
  fcrNextChunk.generateXml(xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fcrFreeChunks");
  for (auto entry : fcrFreeChunk) {
    entry.generateXml(xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();
}

FileChunkReference64x32 FreeChunkListFragment::getFcrNextChunk() const {
  return fcrNextChunk;
}

void FreeChunkListFragment::setFcrNextChunk(
    const FileChunkReference64x32 &value) {
  fcrNextChunk = value;
}

std::vector<FileChunkReference64>
FreeChunkListFragment::getFcrFreeChunk() const {
  return fcrFreeChunk;
}

void FreeChunkListFragment::setFcrFreeChunk(
    const std::vector<FileChunkReference64> &value) {
  fcrFreeChunk = value;
}

quint32 FreeChunkListFragment::getCrc() const { return crc; }

void FreeChunkListFragment::setCrc(const quint32 &value) { crc = value; }
} // namespace MSONcommon
