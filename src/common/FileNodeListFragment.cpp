#include "FileNodeListFragment.h"
#include "commonTypes/Enums.h"
#include "helper/Helper.h"

#include "DocumentSingleton.h"

namespace MSONcommon {

FileChunkReference64 FileNodeListFragment::ref() const { return m_ref; }

void FileNodeListFragment::setRef(const FileChunkReference64 &ref) {
  m_ref = ref;
}

void FileNodeListFragment::setRef(const FileChunkReference64x32 &ref) {
  m_ref.setCb(ref.cb());
  m_ref.setStp(ref.stp());
}

void FileNodeListFragment::setRef(const FileChunkReference32 &ref) {
  m_ref.setCb(ref.cb());
  m_ref.setStp(ref.stp());
}

void FileNodeListFragment::setRef(const FileNodeChunkReference &ref) {
  m_ref.setCb(ref.cb());
  m_ref.setStp(ref.stp());
}

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

void FileNodeListFragment::deserialize(QDataStream &ds) {
  ds >> m_fnlheader;

  FileNode *fn = nullptr;

  rgFileNodes() = std::vector<FileNode *>();

  quint32 fileNodeCount = UINT32_MAX;

  if (DocumentSingleton::getDoc()->getFileNodeCountMapping().contains(
          m_fnlheader.getFileNodeListID())) {
    fileNodeCount =
        DocumentSingleton::getDoc()
            ->getFileNodeCountMapping()[m_fnlheader.getFileNodeListID()];
  }
  /// \todo this calculation is incorrect, not absolute
  qint64 remainingBytes = m_ref.cb() - 20;
  do {

    fn = new FileNode();

    ds >> *fn;

    if (fn->getFileNodeID() != 0 &&
        fn->getFileNodeID() !=
            static_cast<quint16>(FileNodeTypeID::ChunkTerminatorFND)) {
      m_rgFileNodes.push_back(fn);
      fileNodeCount--;
    } else {
      break;
    }

    /// \todo this calculation is incorrect, not absolutes
    remainingBytes = m_ref.cb() - 20 - (ds.device()->pos() - m_ref.stp());

  } while (remainingBytes > 4 && fileNodeCount > 0);

  if (MSONcommon::DocumentSingleton::getDoc()
          ->getFileNodeCountMapping()
          .contains(m_fnlheader.getFileNodeListID())) {
    MSONcommon::DocumentSingleton::getDoc()
        ->getFileNodeCountMapping()[m_fnlheader.getFileNodeListID()] =
        fileNodeCount;
  }
  /// \todo this calculation is incorrect, not absolutes
  m_paddingLength = m_ref.cb() - 20 - (ds.device()->pos() - m_ref.stp());
  ds.skipRawData(m_paddingLength);

  m_nextFragment = FileChunkReference64x32();

  ds >> m_nextFragment;

  // footer
  ds.skipRawData(8);
}

void FileNodeListFragment::serialize(QDataStream &ds) const {}

void FileNodeListFragment::toDebugString(QDebug dbg) const {
  dbg << "FileNodeListFragment:\n"
      << "FileNodeListHeader:\n"
      << m_fnlheader;

  for (auto *entry : m_rgFileNodes) {
    dbg << *entry << '\n';
  }
}

FileNodeListFragment::FileNodeListFragment(const FileChunkReference64 ref)
    : m_ref{ref}, m_fnlheader{}, m_rgFileNodes{}, m_paddingLength{},
      m_nextFragment() {}

FileNodeListFragment::FileNodeListFragment(const FileChunkReference64x32 ref)
    : m_ref(), m_fnlheader{}, m_rgFileNodes{}, m_paddingLength{},
      m_nextFragment() {
  m_ref.setCb(ref.cb());
  m_ref.setStp(ref.stp());
}

FileNodeListFragment::FileNodeListFragment(const FileChunkReference32 ref)
    : m_ref{}, m_fnlheader{}, m_rgFileNodes{}, m_paddingLength{},
      m_nextFragment() {
  m_ref.setCb(ref.cb());
  m_ref.setStp(ref.stp());
}

FileNodeListFragment::FileNodeListFragment(const FileNodeChunkReference ref)
    : m_ref{}, m_fnlheader{}, m_rgFileNodes{}, m_paddingLength{},
      m_nextFragment() {
  m_ref.setCb(ref.cb());
  m_ref.setStp(ref.stp());
}

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
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, FileNodeListFragment &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const FileNodeListFragment &obj) {
  obj.toDebugString(dbg);
  return dbg;
}
} // namespace MSONcommon
