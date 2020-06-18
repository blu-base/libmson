#include "FileNodeListFragment.h"

quint64 FileNodeListFragment::size() const { return m_size; }

void FileNodeListFragment::setSize(const quint64 &size) { m_size = size; }

FileNodeListHeader FileNodeListFragment::fnlheader() const {
  return m_fnlheader;
}

void FileNodeListFragment::setFnlheader(const FileNodeListHeader &fnlheader) {
  m_fnlheader = fnlheader;
}

std::vector<FileNode *> FileNodeListFragment::rgFileNodes() const {
  return m_rgFileNodes;
}

void FileNodeListFragment::setRgFileNodes(
    const std::vector<FileNode *> &rgFileNods) {
  m_rgFileNodes = rgFileNods;
}

quint64 FileNodeListFragment::paddingLength() const { return m_paddingLength; }

void FileNodeListFragment::setPaddingLength(const quint64 &paddingLength) {
  m_paddingLength = paddingLength;
}

FileChunkReference64x32 FileNodeListFragment::nextFragment() const {
  return m_nextFragment;
}

void FileNodeListFragment::setNextFragment(
    const FileChunkReference64x32 &nextFragment) {
  m_nextFragment = nextFragment;
}

FileNodeListFragment::FileNodeListFragment(const quint64 size)
    : m_size{size}, m_fnlheader{}, m_rgFileNodes{}, m_paddingLength{},
      m_nextFragment() {}

/**
 * @brief FileNodeListFragment::~FileNodeListFragment
 *
 * \todo deleting next fragment likely breaks the whole list, revise
 */
FileNodeListFragment::~FileNodeListFragment() {
  for (auto *fn : m_rgFileNodes) {
    delete fn;
  }
}

QDataStream &operator<<(QDataStream &ds, const FileNodeListFragment &obj) {

  return ds;
}

QDataStream &operator>>(QDataStream &ds, FileNodeListFragment &obj) {

  ds >> obj.m_fnlheader;

  return ds;
}

QDebug operator<<(QDebug dbg, const FileNodeListFragment &obj) {}
