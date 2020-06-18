#include <QDataStream>
#include <QDebug>

#include "FileNode.h"
#include "FileNodeList.h"

FileNodeList::FileNodeList() {}

FileNodeList::FileNodeList(const FileNodeList &fnl) {}

FileNodeList::~FileNodeList() {
  for (auto p : m_children) {
    delete p;
  }
  m_children.clear();

  delete m_nextFragment;
}

QDataStream &operator<<(QDataStream &ds, const FileNodeList &obj) { return ds; }

QDataStream &operator>>(QDataStream &ds, FileNodeList &obj) {
  // if byte order is big endian, change to little endian
  if (!ds.byteOrder()) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }

  ds >> obj.m_fileNodeListHeader;

  for (size_t i{0}; i < 4; i++) {
    FileNode *node = new FileNode();

    ds >> *node;

    obj.m_children.push_back(node);
  }

  //  node = new FileNode();

  //  ds >> *node;

  //  obj.m_children.push_back(node);

  //  do {

  //  } while (node != 0x0FF)

  //  I_FileNode node;
  //  do {

  //  } while ()

  return ds;
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

FileNodeList &FileNodeList::operator=(const FileNodeList &rhs) {
  if (this == &rhs) {
    return *this;
  }

  for (auto fn : m_children) {
    delete fn;
  }

  for (auto fn : rhs.m_children) {
    m_children.push_back(new FileNode(*fn));
  }

  m_fileNodeListHeader = rhs.m_fileNodeListHeader;
  m_paddingLength = rhs.m_paddingLength;

  delete m_nextFragment;
  m_nextFragment = rhs.m_nextFragment;

  return *this;
}

FileNodeList &FileNodeList::operator=(FileNodeList &&rhs) {
  if (this == &rhs) {
    return *this;
  }

  for (auto fn : m_children) {
    delete fn;
  }

  for (auto fn : rhs.m_children) {
    m_children.push_back(new FileNode(*fn));
    fn = nullptr;
  }

  m_fileNodeListHeader = rhs.m_fileNodeListHeader;
  m_paddingLength = rhs.m_paddingLength;

  delete m_nextFragment;
  m_nextFragment = rhs.m_nextFragment;
  rhs.m_nextFragment = nullptr;

  return *this;
}

FileNodeListHeader FileNodeList::getFileNodeListHeader() const {
  return m_fileNodeListHeader;
}

void FileNodeList::setFileNodeListHeader(const FileNodeListHeader &value) {
  m_fileNodeListHeader = value;
}

std::vector<FileNode *> FileNodeList::getChildren() const { return m_children; }

void FileNodeList::setChildren(const std::vector<FileNode *> &value) {
  m_children = value;
}

quint64 FileNodeList::getPaddingLength() const { return m_paddingLength; }

void FileNodeList::setPaddingLength(const quint64 &value) {
  m_paddingLength = value;
}

FileChunkReference64x32 *FileNodeList::getNextFragment() const {
  return m_nextFragment;
}

void FileNodeList::setNextFragment(FileChunkReference64x32 *nextFragment) {
  m_nextFragment = nextFragment;
}
