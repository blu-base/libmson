#include "FreeChunkListFragment.h"
#include "helper/Helper.h"
namespace MSONcommon {
void FreeChunkListFragment::deserialize(QDataStream &ds) {
  ds >> crc;
  ds >> fcrNextChunk;

  quint64 chunksToRead = m_size / 16 - 1;

  for (size_t i{0}; i < chunksToRead; i++) {
    std::shared_ptr<FileChunkReference64> temp = std::make_shared<FileChunkReference64>();
    ds >> *temp;
    fcrFreeChunk.push_back(temp);
  }
}

void FreeChunkListFragment::serialize(QDataStream &ds) const {
  ds << crc;
  ds << fcrNextChunk;

  for (size_t i{0}; i < fcrFreeChunk.size(); i++) {
    ds << *fcrFreeChunk.at(i);
  }
}

void FreeChunkListFragment::toDebugString(QDebug &dbg) const {
  dbg.noquote() << "FreeChunkListFragment:  size: "
                << QString("0x%1").arg(m_size, 16, 16, QLatin1Char('0')) << '\n'
                << " fcrNextChunk: " << fcrNextChunk << '\n';

  for (size_t i{0}; i < fcrFreeChunk.size(); i++) {
    dbg.noquote() << *fcrFreeChunk.at(i) << '\n';
  }
}

FreeChunkListFragment::FreeChunkListFragment(quint64 size)
    : m_size{size}, crc{} {}

void FreeChunkListFragment::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {

  xmlWriter.writeStartElement("FreeChunkListFragment");

  xmlWriter.writeStartElement("size");
  xmlWriter.writeCharacters(qStringHex(m_size, 16));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("crc");
  xmlWriter.writeCharacters(qStringHex(crc, 8));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fcrNextChunk");
  xmlWriter << fcrNextChunk;
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fcrFreeChunks");
  for (const auto &entry : fcrFreeChunk) {
    xmlWriter << *entry;
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

std::vector<std::shared_ptr<FileChunkReference64>>
FreeChunkListFragment::getFcrFreeChunk() const {
  return fcrFreeChunk;
}

void FreeChunkListFragment::setFcrFreeChunk(
    const std::vector<std::shared_ptr<FileChunkReference64>>  &value) {
  fcrFreeChunk = value;
}

quint64 FreeChunkListFragment::getSizeInFile() const
{
  quint64 size = sizeof(crc) + fcrNextChunk.getSizeInFile();

  /// \todo use std::accumulate
  for(const auto& entry : fcrFreeChunk) {
    size += entry->getSizeInFile();
  }

  return size;
}

quint32 FreeChunkListFragment::getCrc() const { return crc; }

void FreeChunkListFragment::setCrc(const quint32 &value) { crc = value; }
} // namespace MSONcommon
