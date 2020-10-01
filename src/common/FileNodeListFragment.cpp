#include "FileNodeListFragment.h"
#include "commonTypes/Enums.h"
#include "helper/Helper.h"

#include "DocumentManager.h"
#include "RevisionStoreFile.h"

namespace MSONcommon {

FileChunkReference64 FileNodeListFragment::getRef() const { return m_ref; }

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

FileNodeListHeader FileNodeListFragment::getFnlheader() const {
  return m_fnlheader;
}

void FileNodeListFragment::setFnlheader(const FileNodeListHeader &fnlheader) {
  m_fnlheader = fnlheader;
}

std::vector<std::shared_ptr<FileNode>>
FileNodeListFragment::rgFileNodes() const {
  return m_rgFileNodes;
}

void FileNodeListFragment::setRgFileNodes(
    const std::vector<std::shared_ptr<FileNode>> &rgFileNodes) {
  m_rgFileNodes = rgFileNodes;
}

quint64 FileNodeListFragment::paddingLength() const { return m_paddingLength; }

void FileNodeListFragment::setPaddingLength(const quint64 &paddingLength) {
  m_paddingLength = paddingLength;
}

FileChunkReference64x32 FileNodeListFragment::getNextFragment() const {
  return m_nextFragment;
}

void FileNodeListFragment::setNextFragment(
    const FileChunkReference64x32 &nextFragment) {
  m_nextFragment = nextFragment;
}

quint64 FileNodeListFragment::getSizeInFile() const {
  quint64 size = m_fnlheader.getSizeInFile();

  /// \todo use std::accumulate
  for (const auto &entry : m_rgFileNodes) {
    size += entry->getSizeInFile();
  }

  size += paddingLength();

  size += m_ref.getSizeInFile();
  size += sizeof(footer_magic_id);

  return size;
}

void FileNodeListFragment::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("FileNodeListFragment");
  xmlWriter.writeAttribute("fileNodeListID",
                           QString::number(m_fnlheader.getFileNodeListID()));
  xmlWriter.writeAttribute("nFragmentSequence",
                           QString::number(m_fnlheader.getNFragmentSequence()));

  xmlWriter.writeAttribute("stp", qStringHex(m_ref.stp(), 16));
  xmlWriter.writeAttribute("cb", qStringHex(m_ref.cb(), 16));

  //  xmlWriter.writeStartElement("ref");
  //  xmlWriter << m_ref;
  //  xmlWriter.writeEndElement();

  //  xmlWriter << m_fnlheader;

  xmlWriter.writeStartElement("rgFileNodes");
  for (const auto &entry : m_rgFileNodes) {
    xmlWriter << *entry;
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("paddingLength");
  xmlWriter.writeCharacters(qStringHex(m_paddingLength, 16));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("nextFragment");
  if (!m_nextFragment.is_fcrNil() && !m_nextFragment.is_fcrZero()) {
    xmlWriter << m_nextFragment;
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();
}

void FileNodeListFragment::deserialize(QDataStream &ds) {
  //  qInfo() << "FileNodeListFragment pos" << qStringHex(ds.device()->pos(),
  //  16)
  //          << " size: " << qStringHex(m_ref.cb(), 16);
  quint64 origLocation = ds.device()->pos();

  if(ds.device()->size() < (qint64)m_ref.stp()) {
    qFatal("Reached end of file stream. Could not parse FileNodeListFragment");
  }
  ds.device()->seek(m_ref.stp());

  if(ds.device()->bytesAvailable() < (qint64)m_ref.cb()) {
    qFatal("Reached end of file stream. Cannot parse next FileNodeListFragment.");
  }

  ds >> m_fnlheader;

  quint32 fileNodeCount = UINT32_MAX;

  // Get Document pointer to check whether fileNodeCount has been preset.
  std::shared_ptr<RevisionStoreFile> doc = DocumentManager::getDocument(ds);

  if (doc->getFileNodeCountMapping().contains(
          m_fnlheader.getFileNodeListID())) {
    fileNodeCount =
        doc->getFileNodeCountMapping()[m_fnlheader.getFileNodeListID()];
  }

  quint64 remainingBytes = 0;
  do {
    auto fn = std::make_shared<FileNode>();

    ds >> *fn;

    if (fn->getFileNodeID() != 0) {
      m_rgFileNodes.push_back(fn);
      if (fn->getFileNodeTypeID() != FileNodeTypeID::ChunkTerminatorFND) {
        fileNodeCount--;
      } else {
        /// \todo When ChunkTerminator found, is there really no filenode left?
        //        qWarning() << "ChunkTerminatorFND found";
        break;
      }
    } else {
      //      qWarning() << "FileNodeListFragment ended early";
      break;
    }

    remainingBytes = m_ref.stp() + m_ref.cb() - ds.device()->pos();
  } while ((remainingBytes - 20 > 4) && (fileNodeCount > 0));

  if (doc->getFileNodeCountMapping().contains(
          m_fnlheader.getFileNodeListID())) {
    doc->getFileNodeCountMapping()[m_fnlheader.getFileNodeListID()] =
        fileNodeCount;
  }

  //  if (MSONcommon::DocumentSingleton::getDoc()
  //          ->getFileNodeCountMapping()
  //          .contains(m_fnlheader.getFileNodeListID())) {
  //    MSONcommon::DocumentSingleton::getDoc()
  //        ->getFileNodeCountMapping()[m_fnlheader.getFileNodeListID()] =
  //        fileNodeCount;
  //  }

  //  m_paddingLength = m_ref.cb() - 36 - listSize ;
  m_paddingLength = m_ref.stp() + m_ref.cb() - ds.device()->pos() - 20;

  // Skip to end. Ignore ChunkTerminatorFND
  ds.device()->seek(m_ref.stp() + m_ref.cb() - 20);

  m_nextFragment = FileChunkReference64x32();
  ds >> m_nextFragment;

  // footer
  quint64 temp;
  ds >> temp;
  if (temp != footer_magic_id) {
    //    qWarning() << "FileNodeListFragment footer invalid";
  }
  //  qInfo() << "m_paddingLength" << qStringHex(m_paddingLength, 16);
  ds.device()->seek(origLocation);
}

void FileNodeListFragment::serialize(QDataStream &ds) const {}

void FileNodeListFragment::toDebugString(QDebug &dbg) const {
  dbg << "FileNodeListFragment:\n"
      << "FileNodeListHeader:\n"
      << m_fnlheader;

  for (const auto &entry : m_rgFileNodes) {
    dbg << *entry << '\n';
  }
}

FileNodeListFragment::FileNodeListFragment()
    : m_ref{}, m_fnlheader{}, m_rgFileNodes{}, m_paddingLength{},
      m_nextFragment() {}

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

} // namespace MSONcommon
