#include "MSONDocument.h"

#include <algorithm>

#include <memory>

#include <QDataStream>
#include <QDebug>

#include "helper/Helper.h"

namespace MSONcommon {

QMap<quint32, quint32> &MSONDocument::fileNodeCountMapping() {
  return FileNodeCountMapping;
}

QMap<quint32, quint32> MSONDocument::getFileNodeCountMapping() const{
  return FileNodeCountMapping;
}

void MSONDocument::setFileNodeCountMapping(
    const QMap<quint32, quint32> &value) {
  FileNodeCountMapping = value;
}

bool MSONDocument::isEncrypted() const { return m_isEncrypted; }

void MSONDocument::setIsEncrypted(const bool isEncrypted) {
  m_isEncrypted = isEncrypted;
}

std::shared_ptr<MSONHeader> MSONDocument::getHeader() const { return m_header; }

void MSONDocument::setHeader(std::shared_ptr<MSONHeader> header) { m_header = header; }

std::vector<std::shared_ptr<FreeChunkListFragment>> &MSONDocument::freeChunkList() {
  return m_freeChunkList;
}
std::vector<std::shared_ptr<FreeChunkListFragment>> MSONDocument::getFreeChunkList() const {
  return m_freeChunkList;
}

void MSONDocument::setFreeChunkList(
    const std::vector<std::shared_ptr<FreeChunkListFragment>> &freeChunkList) {
  m_freeChunkList = freeChunkList;
}

std::vector<std::shared_ptr<TransactionLogFragment>> MSONDocument::getTransactionLog() {
  return m_transactionLog;
}

void MSONDocument::setTransactionLog(
    const std::vector<std::shared_ptr<TransactionLogFragment>> &transactionLog) {
  m_transactionLog = transactionLog;
}

std::vector<std::shared_ptr<FileNodeListFragment>> MSONDocument::getHashedChunkList() {
  return m_hashedChunkList;
}

void MSONDocument::setHashedChunkList(
    const std::vector<std::shared_ptr<FileNodeListFragment>> &hashedChunkList) {
  m_hashedChunkList = hashedChunkList;
}

std::shared_ptr<RootFileNodeList> MSONDocument::getRootFileNodeList() const {
  return m_rootFileNodeList;
}

void MSONDocument::setRootFileNodeList(
    const std::shared_ptr<RootFileNodeList> &rootFileNodeList) {
  m_rootFileNodeList = rootFileNodeList;
}

std::vector<std::shared_ptr<FileNodeListFragment>> MSONDocument::getFileNodeList() {
  return m_fileNodeList;
}

void MSONDocument::setFileNodeList(
    const std::vector<std::shared_ptr<FileNodeListFragment>> &fileNodeList) {
  m_fileNodeList = fileNodeList;
}

MSONDocument::MSONDocument()
    : m_isEncrypted{false} {
}

void MSONDocument::serialize(QDataStream& ds) const {
  ds << *m_header;
}

void MSONDocument::deserialize(QDataStream& ds) {
  if (!ds.byteOrder()) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }

  m_header = std::make_shared<MSONHeader>();
  ds >> *m_header;

  // Parsing FreeChunkList
  FileChunkReference64x32 freeChunkRef = m_header->getFcrFreeChunkList();
  if (!freeChunkRef.is_fcrNil() && !freeChunkRef.is_fcrZero()) {
    do {
      std::shared_ptr<FreeChunkListFragment>fclf = std::make_shared<FreeChunkListFragment>(freeChunkRef.cb());
      ds.device()->seek(freeChunkRef.stp());
      ds >> *fclf;

      m_freeChunkList.push_back(fclf);

      freeChunkRef = fclf->getFcrNextChunk();
    } while (!freeChunkRef.is_fcrNil() && !freeChunkRef.is_fcrZero());
  }

  // Parsing TransactionLog
  FileChunkReference64x32 transLogRef = getHeader()->getFcrTransactionLog();
  do {
    std::shared_ptr<TransactionLogFragment> tlf = std::make_shared<TransactionLogFragment>(transLogRef.cb());
    ds.device()->seek(transLogRef.stp());
    ds >> *tlf;

    getTransactionLog().push_back(tlf);
    transLogRef = tlf->getNextFragment();

    for (const auto &entry : tlf->getSizeTable()) {
      if (entry->getSrcID() != 0x00000001) {

        if (FileNodeCountMapping.contains(entry->getSrcID())) {
          if (FileNodeCountMapping[entry->getSrcID()] <
              entry->getTransactionEntrySwitch()) {
            FileNodeCountMapping[entry->getSrcID()] =
                entry->getTransactionEntrySwitch();
          }

        } else {
          FileNodeCountMapping.insert(entry->getSrcID(),
                                          entry->getTransactionEntrySwitch());
        }
      }
    }

  } while (!transLogRef.is_fcrNil() && !transLogRef.is_fcrZero());



  // Parsing RootFileNodeList
  if (!getHeader()->getFcrFileNodeListRoot().is_fcrNil() &&
      !getHeader()->getFcrFileNodeListRoot().is_fcrZero()) {

    m_rootFileNodeList = std::make_shared<RootFileNodeList>(getHeader()->getFcrFileNodeListRoot());
    ds >> *m_rootFileNodeList;



  }

  // Parsing HashedChunkList
  FileChunkReference64x32 hashChunkRef =
      getHeader()->getFcrHashedChunkList();

  if (!hashChunkRef.is_fcrNil() && !hashChunkRef.is_fcrZero()) {
    m_hashedChunkList = parseFileNodeListFragments(ds, hashChunkRef);
  }

  // Filling the GlobalIdentificationTable

}

void MSONDocument::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.setAutoFormatting(true);
  xmlWriter.writeStartDocument();
  xmlWriter.writeStartElement("MSONDocument");
  xmlWriter.writeAttribute("isEncrypted", m_isEncrypted ? "true" : "false");

  xmlWriter << *m_header;

  xmlWriter.writeStartElement("freeChunkList");
  for (const auto& entry : m_freeChunkList) {
    xmlWriter << *entry;
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("transactionLog");
  for (const auto& entry : m_transactionLog) {
    xmlWriter << *entry;
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("hashedChunkList");
  for (const auto& entry : m_hashedChunkList) {
    xmlWriter << *entry;
  }
  xmlWriter.writeEndElement();

  xmlWriter << *m_rootFileNodeList;

  xmlWriter.writeStartElement("fileNodeList");
  for (const auto& entry : m_fileNodeList) {
    xmlWriter << *entry;
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("FileNodeCountMapping");
  for (const auto& entry : FileNodeCountMapping.keys()) {
    xmlWriter.writeStartElement("FileNodeCountMap");
    xmlWriter.writeAttribute("key", qStringHex(entry, 8));
    xmlWriter.writeAttribute("value",
                             qStringHex(FileNodeCountMapping[entry], 8));
    xmlWriter.writeEndElement();
  }

  xmlWriter.writeEndElement(); // MSONDocument
  xmlWriter.writeEndDocument();
}

void MSONDocument::toDebugString(QDebug &dbg) const {

  QDebugStateSaver saver(dbg);
  dbg.setAutoInsertSpaces(false);

  dbg << "MSON Document\n"
      << *m_header;

  dbg << "FileNodeCountMapping: ";
  if (FileNodeCountMapping.empty()) {
    dbg << "none mapped\n";
  } else {
    dbg << '\n';
    for (const auto& key : FileNodeCountMapping) {
      dbg << qStringHex(key, 8) << ", " << FileNodeCountMapping[key]
          << '\n';
    }
  }

  dbg << "FreeChunkList: ";
  if (m_freeChunkList.empty()) {
    dbg << "no free chunks\n";
  } else {
    dbg << '\n';
    for (const auto& key : m_freeChunkList) {
      dbg << *key << '\n';
    }
  }

  dbg << "TransactionLog: ";
  if (m_transactionLog.empty()) {
    dbg << "no transactions\n";
  } else {
    dbg << '\n';
    for (const auto& entry : m_transactionLog) {
      dbg << *entry << '\n';
    }
  }

  dbg << "HashedChunkList: ";
  if (m_hashedChunkList.empty()) {
    dbg << "no hashed chunks\n";
  } else {
    dbg << '\n';
    for (const auto& entry : m_hashedChunkList) {
      dbg << *entry << '\n';
    }
  }

  dbg << *m_rootFileNodeList;

  dbg << "File Node List: ";
  if (m_fileNodeList.empty()) {
    dbg << "no file nodes\n";
  } else {
    dbg << '\n';
    for (const auto& entry : m_fileNodeList) {
      dbg << *entry << '\n';
    }
  }

}

} // namespace MSONcommon
