#include "HashedChunkDescriptor2FND.h"

HashedChunkDescriptor2FND::HashedChunkDescriptor2FND(FNCR_STP_FORMAT stpFormat,
                                                     FNCR_CB_FORMAT cbFormat)
    : m_BlobRef(stpFormat, cbFormat) {}

HashedChunkDescriptor2FND::HashedChunkDescriptor2FND(quint8 stpFormat,
                                                     quint8 cbFormat)
    : m_BlobRef(stpFormat, cbFormat) {}

HashedChunkDescriptor2FND::~HashedChunkDescriptor2FND() {}

FileNodeChunkReference HashedChunkDescriptor2FND::BlobRef() const {
  return m_BlobRef;
}

void HashedChunkDescriptor2FND::setBlobRef(
    const FileNodeChunkReference &BlobRef) {
  m_BlobRef = BlobRef;
}

QByteArray HashedChunkDescriptor2FND::guidHash() const { return m_guidHash; }

void HashedChunkDescriptor2FND::setGuidHash(const QByteArray &guidHash) {
  m_guidHash = guidHash;
}

void HashedChunkDescriptor2FND::deserialize(QDataStream &ds) {
  ds >> m_BlobRef;

  int length = 16;
  char mguidHashRaw[length];
  ds.readRawData(mguidHashRaw, length);
  m_guidHash = QByteArray(mguidHashRaw);
}

void HashedChunkDescriptor2FND::serialize(QDataStream &ds) const {
  ds << m_BlobRef;
  ds << m_guidHash;
}

void HashedChunkDescriptor2FND::toDebugString(QDebug dbg) const {
  dbg << " HashedChunkDescriptor2FND\n"
      << " m_BlobRef:" << m_BlobRef << '\n'
      << " m_guidHash: " << m_guidHash.toHex() << '\n';
}
