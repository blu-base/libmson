#include "FileNodeListFragment.h"
#include "commonTypes/Enums.h"
#include "helper/Helper.h"

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

std::vector<FileNode> FileNodeListFragment::rgFileNodes() const {
  return m_rgFileNodes;
}

void FileNodeListFragment::setRgFileNodes(
    const std::vector<FileNode> &rgFileNods) {
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

void FileNodeListFragment::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("FileNodeListFragment");

  xmlWriter.writeStartElement("ref");
  m_ref.generateXml(xmlWriter);
  xmlWriter.writeEndElement();

  m_fnlheader.generateXml(xmlWriter);

  xmlWriter.writeStartElement("rgFileNodes");
  for (const auto& entry : m_rgFileNodes) {
    entry.generateXml(xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("paddingLength");
  xmlWriter.writeCharacters(qStringHex(m_paddingLength, 16));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("nextFragment");
  if (!m_nextFragment.is_fcrNil() && !m_nextFragment.is_fcrZero()) {
    m_nextFragment.generateXml(xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();
}

void FileNodeListFragment::deserialize(QDataStream &ds) {
    qInfo() << "FileNodeListFragment pos" << qStringHex(ds.device()->pos(),
    16) << " size: " << qStringHex(m_ref.cb(),16);
  ds >> m_fnlheader;

  quint32 fileNodeCount = UINT32_MAX;

//  if (DocumentSingleton::getDoc()->getFileNodeCountMapping().contains(
//          m_fnlheader.getFileNodeListID())) {
//   fileNodeCount =
//        DocumentSingleton::getDoc()
//            ->getFileNodeCountMapping()[m_fnlheader.getFileNodeListID()];
//   qWarning() << "FileNodeListID " << m_fnlheader.getFileNodeListID() << " found in FileNodeCountMapping. count:" << fileNodeCount;

//  }
  /// \todo this calculation is incorrect, not absolute
  quint64 listSize = 0;
  quint64 remainingBytes = 0;
  do {
    FileNode fn;

    ds >> fn;
    listSize += fn.getFileNodeSize();
    if (fn.getFileNodeID() != 0) {
      m_rgFileNodes.push_back(fn);
      if (fn.getFileNodeTypeID() != FileNodeTypeID::ChunkTerminatorFND) {
        fileNodeCount--;
      } else {
          /// \todo When ChunkTerminator found, is there really no filenode left?
          qWarning() << "ChunkTerminatorFND found";
          break;
      }
    } else {
        qWarning() << "FileNodeListFragment ended early";
        break;
    }

    remainingBytes = m_ref.stp() + m_ref.cb() - ds.device()->pos();
  } while ( (remainingBytes - 20 > 4) && (fileNodeCount > 0));

//  if (MSONcommon::DocumentSingleton::getDoc()
//          ->getFileNodeCountMapping()
//          .contains(m_fnlheader.getFileNodeListID())) {
//    MSONcommon::DocumentSingleton::getDoc()
//        ->getFileNodeCountMapping()[m_fnlheader.getFileNodeListID()] =
//        fileNodeCount;
//  }

//  m_paddingLength = m_ref.cb() - 36 - listSize ;
  m_paddingLength = m_ref.stp() + m_ref.cb() - ds.device()->pos() - 20 ;

//  char* rawBody = new char[m_paddingLength];
//  ds.readRawData(rawBody, m_paddingLength);
//  QByteArray padding = QByteArray(QByteArray::fromRawData(rawBody, m_paddingLength));

  ds.skipRawData(m_paddingLength);

  // Skip to end. Ignore ChunkTerminatorFND
  ds.device()->seek(m_ref.stp() + m_ref.cb() - 20);

  m_nextFragment = FileChunkReference64x32();
  ds >> m_nextFragment;


  // footer
  quint64 temp;
  ds >> temp;
  if (temp != footer_magic_id) {
    qWarning() << "FileNodeListFragment footer invalid";
  }
  qInfo() << "m_paddingLength" << qStringHex(m_paddingLength, 16);
}

void FileNodeListFragment::serialize(QDataStream &ds) const {}

void FileNodeListFragment::toDebugString(QDebug dbg) const {
  dbg << "FileNodeListFragment:\n"
      << "FileNodeListHeader:\n"
      << m_fnlheader;

  for (const auto& entry : m_rgFileNodes) {
    dbg << entry << '\n';
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
//  for (auto *fn : m_rgFileNodes) {
//    delete fn;
//  }
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
