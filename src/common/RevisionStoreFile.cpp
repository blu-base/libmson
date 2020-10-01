#include "RevisionStoreFile.h"

#include <algorithm>

#include <memory>

#include <QDataStream>
#include <QDebug>

#include "helper/Helper.h"

namespace MSONcommon {

QMap<quint32, quint32> &RevisionStoreFile::fileNodeCountMapping() {
  return FileNodeCountMapping;
}

QMap<quint32, quint32> RevisionStoreFile::getFileNodeCountMapping() const {
  return FileNodeCountMapping;
}

void RevisionStoreFile::setFileNodeCountMapping(
    const QMap<quint32, quint32> &value) {
  FileNodeCountMapping = value;
}

bool RevisionStoreFile::isEncrypted() const { return m_isEncrypted; }

void RevisionStoreFile::setIsEncrypted(const bool isEncrypted) {
  m_isEncrypted = isEncrypted;
}

std::shared_ptr<RevisionStoreFileHeader> RevisionStoreFile::getHeader() const { return m_header; }

void RevisionStoreFile::setHeader(std::shared_ptr<RevisionStoreFileHeader> header) {
  m_header = header;
}

std::vector<std::shared_ptr<FreeChunkListFragment>> &
RevisionStoreFile::freeChunkList() {
  return m_freeChunkList;
}
std::vector<std::shared_ptr<FreeChunkListFragment>>
RevisionStoreFile::getFreeChunkList() const {
  return m_freeChunkList;
}

void RevisionStoreFile::setFreeChunkList(
    const std::vector<std::shared_ptr<FreeChunkListFragment>> &freeChunkList) {
  m_freeChunkList = freeChunkList;
}

std::vector<std::shared_ptr<TransactionLogFragment>>
RevisionStoreFile::getTransactionLog() {
  return m_transactionLog;
}

void RevisionStoreFile::setTransactionLog(
    const std::vector<std::shared_ptr<TransactionLogFragment>>
        &transactionLog) {
  m_transactionLog = transactionLog;
}

std::vector<std::shared_ptr<FileNodeListFragment>>
RevisionStoreFile::getHashedChunkList() {
  return m_hashedChunkList;
}

void RevisionStoreFile::setHashedChunkList(
    const std::vector<std::shared_ptr<FileNodeListFragment>> &hashedChunkList) {
  m_hashedChunkList = hashedChunkList;
}

std::shared_ptr<RootFileNodeList> RevisionStoreFile::getRootFileNodeList() const {
  return m_rootFileNodeList;
}

void RevisionStoreFile::setRootFileNodeList(
    const std::shared_ptr<RootFileNodeList> &rootFileNodeList) {
  m_rootFileNodeList = rootFileNodeList;
}

std::vector<std::shared_ptr<FileNodeListFragment>>
RevisionStoreFile::getFileNodeList() {
  return m_fileNodeList;
}

void RevisionStoreFile::setFileNodeList(
    const std::vector<std::shared_ptr<FileNodeListFragment>> &fileNodeList) {
  m_fileNodeList = fileNodeList;
}

RevisionStoreFile::RevisionStoreFile() : m_isEncrypted{false} {}

void RevisionStoreFile::serialize(QDataStream &ds) const { ds << *m_header; }

void RevisionStoreFile::deserialize(QDataStream &ds) {
  if (!ds.byteOrder()) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }

  if (ds.device()->bytesAvailable() >= 1024) {

    m_header = std::make_shared<RevisionStoreFileHeader>();
    ds >> *m_header;

    // Parsing FreeChunkList
    FileChunkReference64x32 freeChunkRef = m_header->getFcrFreeChunkList();
    if (!freeChunkRef.is_fcrNil() && !freeChunkRef.is_fcrZero()) {
      do {
        std::shared_ptr<FreeChunkListFragment> fclf =
            std::make_shared<FreeChunkListFragment>(freeChunkRef.cb());
        ds.device()->seek(freeChunkRef.stp());
        ds >> *fclf;

        m_freeChunkList.push_back(fclf);

        freeChunkRef = fclf->getFcrNextChunk();
      } while (!freeChunkRef.is_fcrNil() && !freeChunkRef.is_fcrZero());
    }

    // Parsing TransactionLog
    FileChunkReference64x32 transLogRef = getHeader()->getFcrTransactionLog();
    quint32 countTransactions = 0;
    while (!transLogRef.is_fcrNil() && !transLogRef.is_fcrZero()) {

      std::shared_ptr<TransactionLogFragment> tlf =
          std::make_shared<TransactionLogFragment>(transLogRef.cb());
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
        } else {
          countTransactions++;
          if (countTransactions == m_header->getCTransactionsInLog()) {
            break;
          } else {
            continue;
          }
        }
      }
      if (countTransactions == m_header->getCTransactionsInLog()) {
        break;
      }
    };

    if (countTransactions != m_header->getCTransactionsInLog()) {
      qWarning() << "Only " << QString::number(countTransactions)
                 << " TransactionLogFragments parsed, but "
                 << QString::number(m_header->getCTransactionsInLog())
                 << " declared.";
    }

    // Parsing RootFileNodeList
    if (!getHeader()->getFcrFileNodeListRoot().is_fcrNil() &&
        !getHeader()->getFcrFileNodeListRoot().is_fcrZero()) {

      m_rootFileNodeList = std::make_shared<RootFileNodeList>(
          getHeader()->getFcrFileNodeListRoot());
      ds >> *m_rootFileNodeList;
    }

    // Parsing HashedChunkList
    FileChunkReference64x32 hashChunkRef = getHeader()->getFcrHashedChunkList();

    if (!hashChunkRef.is_fcrNil() && !hashChunkRef.is_fcrZero()) {
      m_hashedChunkList = parseFileNodeListFragments(ds, hashChunkRef);
    }

    // Filling the GlobalIdentificationTable

  } // if file size >= 1024
  else {
    qFatal("File is too small to be a valid OneStore file format");
  }
}

void RevisionStoreFile::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.setAutoFormatting(true);
  xmlWriter.writeStartDocument();
  xmlWriter.writeStartElement("RevisionStoreFile");
  xmlWriter.writeAttribute("isEncrypted", m_isEncrypted ? "true" : "false");

  xmlWriter << *m_header;

  xmlWriter.writeStartElement("freeChunkList");
  for (const auto &entry : m_freeChunkList) {
    xmlWriter << *entry;
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("transactionLog");
  for (const auto &entry : m_transactionLog) {
    xmlWriter << *entry;
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("hashedChunkList");
  for (const auto &entry : m_hashedChunkList) {
    xmlWriter << *entry;
  }
  xmlWriter.writeEndElement();

  if (!m_header->getFcrFileNodeListRoot().is_fcrNil() &&
      !m_header->getFcrFileNodeListRoot().is_fcrZero()) {
    xmlWriter << *m_rootFileNodeList;
  }

  xmlWriter.writeStartElement("fileNodeList");
  for (const auto &entry : m_fileNodeList) {
    xmlWriter << *entry;
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("FileNodeCountMapping");
  for (const auto &entry : FileNodeCountMapping.keys()) {
    xmlWriter.writeStartElement("FileNodeCountMap");
    xmlWriter.writeAttribute("key", qStringHex(entry, 8));
    xmlWriter.writeAttribute("value",
                             qStringHex(FileNodeCountMapping[entry], 8));
    xmlWriter.writeEndElement();
  }

  xmlWriter.writeEndElement(); // RevisionStoreFile
  xmlWriter.writeEndDocument();
}

void RevisionStoreFile::toDebugString(QDebug &dbg) const {

  QDebugStateSaver saver(dbg);
  dbg.setAutoInsertSpaces(false);

  dbg << "MSON Document\n" << *m_header;

  dbg << "FileNodeCountMapping: ";
  if (FileNodeCountMapping.empty()) {
    dbg << "none mapped\n";
  } else {
    dbg << '\n';
    for (const auto &key : FileNodeCountMapping) {
      dbg << qStringHex(key, 8) << ", " << FileNodeCountMapping[key] << '\n';
    }
  }

  dbg << "FreeChunkList: ";
  if (m_freeChunkList.empty()) {
    dbg << "no free chunks\n";
  } else {
    dbg << '\n';
    for (const auto &key : m_freeChunkList) {
      dbg << *key << '\n';
    }
  }

  dbg << "TransactionLog: ";
  if (m_transactionLog.empty()) {
    dbg << "no transactions\n";
  } else {
    dbg << '\n';
    for (const auto &entry : m_transactionLog) {
      dbg << *entry << '\n';
    }
  }

  dbg << "HashedChunkList: ";
  if (m_hashedChunkList.empty()) {
    dbg << "no hashed chunks\n";
  } else {
    dbg << '\n';
    for (const auto &entry : m_hashedChunkList) {
      dbg << *entry << '\n';
    }
  }

  dbg << *m_rootFileNodeList;

  dbg << "File Node List: ";
  if (m_fileNodeList.empty()) {
    dbg << "no file nodes\n";
  } else {
    dbg << '\n';
    for (const auto &entry : m_fileNodeList) {
      dbg << *entry << '\n';
    }
  }
}

} // namespace MSONcommon
