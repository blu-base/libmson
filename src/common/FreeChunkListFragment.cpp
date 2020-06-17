#include "FreeChunkListFragment.h"

void FreeChunkListFragment::deserialize(QDataStream &ds) {
  ds >> crc;
  ds >> fcrNextChunk;

  quint64 chunksToRead = m_size / 16 - 1;

  for (size_t i{0}; i < chunksToRead; i++) {
    FileChunkReference64 temp;
    ds >> temp;
    fcrFreeChunk.push_back(temp);
  }
}

void FreeChunkListFragment::serialize(QDataStream &ds) const {
    ds << crc;
    ds << fcrNextChunk;

    for(size_t i {0}; i < fcrFreeChunk.size(); i++) {
        ds << fcrFreeChunk.at(i);
    }
}

void FreeChunkListFragment::toDebugString(QDebug dbg) const {
    dbg.noquote() << "FreeChunkListFragment:  size: " << QString("0x%1").arg(m_size,16,16,QLatin1Char('0')) << '\n'
        << " fcrNextChunk: " << fcrNextChunk << '\n';

    for(size_t i {0}; i < fcrFreeChunk.size(); i++) {
        dbg.noquote() << fcrFreeChunk.at(i) << '\n';
    }

}

FreeChunkListFragment::FreeChunkListFragment(quint64 size) : m_size{size} {}

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
