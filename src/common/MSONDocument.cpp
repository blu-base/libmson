#include "MSONDocument.h"

#include <algorithm>

#include <memory>

#include <QDataStream>
#include <QDebug>

#include "helper/Helper.h"

namespace MSONcommon {

QMap<quint32, quint32> &MSONDocument::getFileNodeCountMapping() {
  return FileNodeCountMapping;
}

void MSONDocument::setFileNodeCountMapping(
    const QMap<quint32, quint32> &value) {
  FileNodeCountMapping = value;
}

bool MSONDocument::getIsEncrypted() const { return m_isEncrypted; }

void MSONDocument::setIsEncrypted(bool isEncrypted) {
  m_isEncrypted = isEncrypted;
}

MSONHeader *MSONDocument::getHeader() const { return m_header; }

void MSONDocument::setHeader(MSONHeader *header) { m_header = header; }

std::vector<FreeChunkListFragment *> &MSONDocument::getFreeChunkList() {
  return m_freeChunkList;
}

void MSONDocument::setFreeChunkList(
    const std::vector<FreeChunkListFragment *> &freeChunkList) {
  m_freeChunkList = freeChunkList;
}

std::vector<TransactionLogFragment *> &MSONDocument::getTransactionLog() {
  return m_transactionLog;
}

void MSONDocument::setTransactionLog(
    const std::vector<TransactionLogFragment *> &transactionLog) {
  m_transactionLog = transactionLog;
}

std::vector<FileNodeListFragment *> &MSONDocument::getHashedChunkList() {
  return m_hashedChunkList;
}

void MSONDocument::setHashedChunkList(
    const std::vector<FileNodeListFragment *> &hashedChunkList) {
  m_hashedChunkList = hashedChunkList;
}

RootFileNodeList *MSONDocument::getRootFileNodeList() const {
  return m_rootFileNodeList;
}

void MSONDocument::setRootFileNodeList(
    const RootFileNodeList &rootFileNodeList) {
  m_rootFileNodeList = new RootFileNodeList(rootFileNodeList);
}

std::vector<FileNodeListFragment *> &MSONDocument::getFileNodeList() {
  return m_fileNodeList;
}

void MSONDocument::setFileNodeList(
    const std::vector<FileNodeListFragment *> &fileNodeList) {
  m_fileNodeList = fileNodeList;
}

MSONDocument::MSONDocument()
    : m_isEncrypted{false}, m_header{new MSONHeader()}, m_freeChunkList{},
      m_transactionLog{}, m_hashedChunkList{}, m_rootFileNodeList{},
      m_fileNodeList{} {
  m_header = new MSONHeader();
}

MSONDocument::~MSONDocument() {

  for (auto *fcl : m_freeChunkList) {
    delete fcl;
  }
  for (auto *tl : m_transactionLog) {
    delete tl;
  }

  for (auto *hcl : m_hashedChunkList) {
    delete hcl;
  }

  for (auto *fnl : m_fileNodeList) {
    delete fnl;
  }

  delete m_rootFileNodeList;
}

///**
// * @brief MSONDocument copy constructor
// * @param source
// */
// MSONDocument::MSONDocument(const MSONDocument &source)
//    : m_isEncrypted{source.m_isEncrypted}, m_header{nullptr},
//    m_freeChunkList{},
//      m_transactionLog{}, m_hashedChunkList{}, m_rootFileNodeList{nullptr},
//      m_fileNodeList{} {

//  m_header = new MSONHeader(*source.m_header);

//  // deep copy source.m_freeChunkList
//  m_freeChunkList.resize(source.m_freeChunkList.size());
//  std::transform(source.m_freeChunkList.begin(), source.m_freeChunkList.end(),
//                 m_freeChunkList.begin(), [](FreeChunkListFragment *s) {
//                   return new FreeChunkListFragment(*s);
//                 });

//  // deep copy source.m_transactionLog
//  m_transactionLog.resize(source.m_transactionLog.size());
//  std::transform(source.m_transactionLog.begin(),
//  source.m_transactionLog.end(),
//                 m_transactionLog.begin(), [](TransactionLogFragment *s) {
//                   return new TransactionLogFragment(*s);
//                 });

//  // deep copy source.m_hashedChunkList
//  m_hashedChunkList.resize(source.m_hashedChunkList.size());
//  std::transform(
//      source.m_hashedChunkList.begin(), source.m_hashedChunkList.end(),
//      m_hashedChunkList.begin(),
//      [](FileNodeListFragment *s) { return new FileNodeListFragment(*s); });

//  m_rootFileNodeList = new RootFileNodeList(*source.m_rootFileNodeList);

//  // deep copy source.m_fileNodeList
//  m_fileNodeList.resize(source.m_fileNodeList.size());
//  std::transform(source.m_fileNodeList.begin(), source.m_fileNodeList.end(),
//                 m_fileNodeList.begin(), [](FileNodeListFragment *s) {
//                   return new FileNodeListFragment(*s);
//                 });
//}

///**
// * @brief MSONDocument move constructor
// * @param source
// */
// MSONDocument::MSONDocument(MSONDocument &&source)
//    : m_isEncrypted{source.m_isEncrypted}, m_header{nullptr},
//    m_freeChunkList{},
//      m_transactionLog{}, m_hashedChunkList{}, m_rootFileNodeList{nullptr},
//      m_fileNodeList{} {

//  m_header = source.m_header;
//  source.m_header = nullptr;

//  // move source.m_freeChunkList
//  m_freeChunkList.resize(source.m_freeChunkList.size());
//  std::transform(source.m_freeChunkList.begin(), source.m_freeChunkList.end(),
//                 m_freeChunkList.begin(),
//                 [](FreeChunkListFragment *s) { return s; });
//  std::transform(source.m_freeChunkList.begin(), source.m_freeChunkList.end(),
//                 source.m_freeChunkList.begin(), []() { return nullptr; });

//  // move source.m_transactionLog
//  m_transactionLog.resize(source.m_transactionLog.size());
//  std::transform(source.m_transactionLog.begin(),
//  source.m_transactionLog.end(),
//                 m_transactionLog.begin(),
//                 [](TransactionLogFragment *s) { return s; });
//  std::transform(source.m_transactionLog.begin(),
//  source.m_transactionLog.end(),
//                 source.m_transactionLog.begin(), []() { return nullptr; });

//  // move source.m_hashedChunkList
//  m_hashedChunkList.resize(source.m_hashedChunkList.size());
//  std::transform(source.m_hashedChunkList.begin(),
//                 source.m_hashedChunkList.end(), m_hashedChunkList.begin(),
//                 [](FileNodeListFragment *s) { return s; });
//  std::transform(source.m_hashedChunkList.begin(),
//                 source.m_hashedChunkList.end(),
//                 source.m_hashedChunkList.begin(), []() { return nullptr; });

//  m_rootFileNodeList = new RootFileNodeList(*source.m_rootFileNodeList);
//  source.m_header = nullptr;

//  // movesource.m_fileNodeList
//  m_fileNodeList.resize(source.m_fileNodeList.size());
//  std::transform(source.m_fileNodeList.begin(), source.m_fileNodeList.end(),
//                 m_fileNodeList.begin(),
//                 [](FileNodeListFragment *s) { return s; });
//  std::transform(source.m_fileNodeList.begin(), source.m_fileNodeList.end(),
//                 source.m_fileNodeList.begin(), []() { return nullptr; });
//}

//// copy assignment
// MSONDocument &MSONDocument::operator=(const MSONDocument &rhs) {
//  if (this == &rhs) {
//    return *this;
//  }

//  m_isEncrypted = rhs.m_isEncrypted;

//  m_header = new MSONHeader(*rhs.getHeader());

//  // deep copy rhs.m_freeChunkList
//  m_freeChunkList.resize(rhs.m_freeChunkList.size());
//  std::transform(rhs.m_freeChunkList.begin(), rhs.m_freeChunkList.end(),
//                 m_freeChunkList.begin(), [](FreeChunkListFragment *s) {
//                   return new FreeChunkListFragment(*s);
//                 });

//  // deep copy rhs.m_transactionLog
//  m_transactionLog.resize(rhs.m_transactionLog.size());
//  std::transform(rhs.m_transactionLog.begin(), rhs.m_transactionLog.end(),
//                 m_transactionLog.begin(), [](TransactionLogFragment *s) {
//                   return new TransactionLogFragment(*s);
//                 });

//  // deep copy rhs.m_hashedChunkList
//  m_hashedChunkList.resize(rhs.m_hashedChunkList.size());
//  std::transform(rhs.m_hashedChunkList.begin(), rhs.m_hashedChunkList.end(),
//                 m_hashedChunkList.begin(), [](FileNodeListFragment *s) {
//                   return new FileNodeListFragment(*s);
//                 });

//  m_rootFileNodeList = new RootFileNodeList(*rhs.m_rootFileNodeList);

//  // deep copy rhs.m_fileNodeList
//  m_fileNodeList.resize(rhs.m_fileNodeList.size());
//  std::transform(rhs.m_fileNodeList.begin(), rhs.m_fileNodeList.end(),
//                 m_fileNodeList.begin(), [](FileNodeListFragment *s) {
//                   return new FileNodeListFragment(*s);
//                 });

//  return *this;
//}
//// move assignment
// MSONDocument &MSONDocument::operator=(MSONDocument &&rhs) {

//  if (this == &rhs) {
//    return *this;
//  }

//  m_isEncrypted = rhs.m_isEncrypted;

//  m_header = rhs.m_header;
//  rhs.m_header = nullptr;

//  // move rhs.m_freeChunkList
//  m_freeChunkList.resize(rhs.m_freeChunkList.size());
//  std::transform(rhs.m_freeChunkList.begin(), rhs.m_freeChunkList.end(),
//                 m_freeChunkList.begin(),
//                 [](FreeChunkListFragment *s) { return s; });
//  std::transform(rhs.m_freeChunkList.begin(), rhs.m_freeChunkList.end(),
//                 rhs.m_freeChunkList.begin(), []() { return nullptr; });

//  // move rhs.m_transactionLog
//  m_transactionLog.resize(rhs.m_transactionLog.size());
//  std::transform(rhs.m_transactionLog.begin(), rhs.m_transactionLog.end(),
//                 m_transactionLog.begin(),
//                 [](TransactionLogFragment *s) { return s; });
//  std::transform(rhs.m_transactionLog.begin(), rhs.m_transactionLog.end(),
//                 rhs.m_transactionLog.begin(), []() { return nullptr; });

//  // move rhs.m_hashedChunkList
//  m_hashedChunkList.resize(rhs.m_hashedChunkList.size());
//  std::transform(rhs.m_hashedChunkList.begin(), rhs.m_hashedChunkList.end(),
//                 m_hashedChunkList.begin(),
//                 [](FileNodeListFragment *s) { return s; });
//  std::transform(rhs.m_hashedChunkList.begin(), rhs.m_hashedChunkList.end(),
//                 rhs.m_hashedChunkList.begin(), []() { return nullptr; });

//  m_rootFileNodeList = rhs.m_rootFileNodeList;
//  rhs.m_rootFileNodeList = nullptr;

//  // move rhs.m_fileNodeList
//  m_fileNodeList.resize(rhs.m_fileNodeList.size());
//  std::transform(rhs.m_fileNodeList.begin(), rhs.m_fileNodeList.end(),
//                 m_fileNodeList.begin(),
//                 [](FileNodeListFragment *s) { return s; });
//  std::transform(rhs.m_fileNodeList.begin(), rhs.m_fileNodeList.end(),
//                 rhs.m_fileNodeList.begin(), []() { return nullptr; });

//  return *this;
//}

QDataStream &operator<<(QDataStream &ds, const MSONDocument &obj) {
  ds << *obj.m_header;

  return ds;
}

QDataStream &operator>>(QDataStream &ds, MSONDocument &obj) {

  if (!ds.byteOrder()) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }

  obj.m_header = new MSONHeader();
  ds >> *obj.m_header;

  FileChunkReference64x32 freeChunkRef = obj.m_header->getFcrFreeChunkList();

  // if freeChunks exists deserialize them
  if (!freeChunkRef.is_fcrNil() && !freeChunkRef.is_fcrZero()) {
    do {
      FreeChunkListFragment *fclf =
          new FreeChunkListFragment(freeChunkRef.cb());
      ds.device()->seek(freeChunkRef.stp());
      ds >> *fclf;

      obj.m_freeChunkList.push_back(fclf);

      freeChunkRef = fclf->getFcrNextChunk();
    } while (!freeChunkRef.is_fcrNil() && !freeChunkRef.is_fcrZero());
  }

  FileChunkReference64x32 transLogRef = obj.getHeader()->getFcrTransactionLog();

  do {
    TransactionLogFragment *tlf = new TransactionLogFragment(transLogRef.cb());
    ds.device()->seek(transLogRef.stp());
    ds >> *tlf;

    obj.getTransactionLog().push_back(tlf);
    transLogRef = tlf->getNextFragment();

    for (auto entry : tlf->getSizeTable()) {
      if (entry->getSrcID() != 0x00000001) {

        if (obj.FileNodeCountMapping.contains(entry->getSrcID())) {
          if (obj.FileNodeCountMapping[entry->getSrcID()] <
              entry->getTransactionEntrySwitch()) {
            obj.FileNodeCountMapping[entry->getSrcID()] =
                entry->getTransactionEntrySwitch();
          }

        } else {
          obj.FileNodeCountMapping.insert(entry->getSrcID(),
                                          entry->getTransactionEntrySwitch());
        }
      }

      //      size_t i{0};

      //      while (i < tlf->getSizeTable().size()) {
      //      }
    }

    //    for (size_t i{0}; i < tlf->getSizeTable().size(); i++) {
    //    }

  } while (!transLogRef.is_fcrNil() && !transLogRef.is_fcrZero());

  FileChunkReference64x32 hashChunkRef =
      obj.getHeader()->getFcrHashedChunkList();

  if (!hashChunkRef.is_fcrNil() && !hashChunkRef.is_fcrZero()) {
    do {
      FileNodeListFragment *hcl = new FileNodeListFragment(hashChunkRef);
      ds.device()->seek(hashChunkRef.stp());
      ds >> *hcl;
      hashChunkRef = hcl->nextFragment();
    } while (!hashChunkRef.is_fcrNil() && !hashChunkRef.is_fcrZero());
  }

  if (!obj.getHeader()->getFcrFileNodeListRoot().is_fcrNil() &&
      !obj.getHeader()->getFcrFileNodeListRoot().is_fcrZero()) {

    obj.m_rootFileNodeList =
        new RootFileNodeList(obj.getHeader()->getFcrFileNodeListRoot());
    ds >> *obj.m_rootFileNodeList;
  }

  return ds;
}

void MSONDocument::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.setAutoFormatting(true);
  xmlWriter.writeStartDocument();
  xmlWriter.writeStartElement("MSONDocument");
  xmlWriter.writeAttribute("isEncrypted", m_isEncrypted ? "true" : "false");

  m_header->generateXml(xmlWriter);

  xmlWriter.writeStartElement("freeChunkList");
  for (auto entry : m_freeChunkList) {
    entry->generateXml(xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("transactionLog");
  for (auto entry : m_transactionLog) {
    entry->generateXml(xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("hashedChunkList");
  for (auto entry : m_hashedChunkList) {
    entry->generateXml(xmlWriter);
  }
  xmlWriter.writeEndElement();

  m_rootFileNodeList->generateXml(xmlWriter);

  xmlWriter.writeStartElement("fileNodeList");
  for (auto entry : m_fileNodeList) {
    entry->generateXml(xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("FileNodeCountMapping");
  for (auto entry : FileNodeCountMapping.keys()) {
    xmlWriter.writeStartElement("FileNodeCountMap");
    xmlWriter.writeAttribute("key", qStringHex(entry,8));
    xmlWriter.writeAttribute("value", qStringHex(FileNodeCountMapping[entry],8));
    xmlWriter.writeEndElement();
  }

  xmlWriter.writeEndElement(); // MSONDocument
  xmlWriter.writeEndDocument();
}

QDebug operator<<(QDebug dbg, const MSONDocument &obj) {

  QDebugStateSaver saver(dbg);
  dbg.setAutoInsertSpaces(false);

  dbg << "MSON Document\n";
  dbg << *obj.m_header;

  dbg << "FileNodeCountMapping: ";
  if (obj.FileNodeCountMapping.empty()) {
    dbg << "none mapped\n";
  } else {
    dbg << '\n';
    for (auto key : obj.FileNodeCountMapping) {
      dbg << qStringHex(key, 8) << ", " << obj.FileNodeCountMapping[key]
          << '\n';
    }
  }

  dbg << "FreeChunkList: ";
  if (obj.m_freeChunkList.empty()) {
    dbg << "no free chunks\n";
  } else {
    dbg << '\n';
    for (auto key : obj.m_freeChunkList) {
      dbg << key << '\n';
    }
  }

  dbg << "TransactionLog: ";
  if (obj.m_transactionLog.empty()) {
    dbg << "no transactions\n";
  } else {
    dbg << '\n';
    for (auto entry : obj.m_transactionLog) {
      dbg << *entry << '\n';
    }
  }

  dbg << "HashedChunkList: ";
  if (obj.m_hashedChunkList.empty()) {
    dbg << "no hashed chunks\n";
  } else {
    dbg << '\n';
    for (auto entry : obj.m_hashedChunkList) {
      dbg << *entry << '\n';
    }
  }

  dbg << *obj.m_rootFileNodeList;

  dbg << "File Node List: ";
  if (obj.m_fileNodeList.empty()) {
    dbg << "no file nodes\n";
  } else {
    dbg << '\n';
    for (auto entry : obj.m_fileNodeList) {
      dbg << *entry << '\n';
    }
  }

  return dbg;
}

} // namespace MSONcommon
