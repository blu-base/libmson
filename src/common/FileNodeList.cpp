#include <QDataStream>
#include <QDebug>

#include "FileNode.h"
#include "FileNodeList.h"

namespace MSONcommon {

FileNodeList::FileNodeList() : m_paddingLength() {}

void MSONcommon::FileNodeList::serialize(QDataStream &ds) const {}

void MSONcommon::FileNodeList::deserialize(QDataStream &ds) {
  // if byte order is big endian, change to little endian
  if (!ds.byteOrder()) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }

  ds >> m_fileNodeListHeader;

  for (size_t i{0}; i < 4; i++) {
    auto node = std::make_shared<FileNode>();

    ds >> *node;

    m_children.push_back(node);
  }
}

QDebug operator<<(QDebug dbg, const FileNodeList &obj) {
  QDebugStateSaver saver(dbg);
  dbg.nospace() << obj.m_fileNodeListHeader << '\n';

  for (size_t i{0}; i < obj.getChildren().size(); i++) {
    dbg.nospace() << *obj.getChildren().at(i) << '\n';
  }

  //  dbg.nospace() << *obj.getChildren().at(0) << '\n';

  return dbg;
}

FileNodeListHeader FileNodeList::getFileNodeListHeader() const {
  return m_fileNodeListHeader;
}

void FileNodeList::setFileNodeListHeader(const FileNodeListHeader &value) {
  m_fileNodeListHeader = value;
}

std::vector<std::shared_ptr<FileNode>> FileNodeList::getChildren() const {
  return m_children;
}

void FileNodeList::setChildren(
    const std::vector<std::shared_ptr<FileNode>> &value) {
  m_children = value;
}

quint64 FileNodeList::getPaddingLength() const { return m_paddingLength; }

void FileNodeList::setPaddingLength(const quint64 &value) {
  m_paddingLength = value;
}

FileChunkReference64x32 FileNodeList::getNextFragment() const {
  return m_nextFragment;
}

void FileNodeList::setNextFragment(
    const FileChunkReference64x32 &nextFragment) {
  m_nextFragment = nextFragment;
}

} // namespace MSONcommon
