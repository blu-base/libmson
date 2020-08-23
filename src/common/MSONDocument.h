#ifndef MSONDOCUMENT_H
#define MSONDOCUMENT_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDebug>
#include <QIODevice>
#include <QXmlStreamWriter>

#include <vector>

#include "FileNodeList.h"
#include "MSONHeader.h"

#include "FileNodeListFragment.h"
#include "FreeChunkListFragment.h"
#include "RootFileNodeList.h"
#include "TransactionLogFragment.h"

#include "commonTypes/ExtendedGUID.h"
#include "commonTypes/FileNodeChunkReference.h"

namespace MSONcommon {

class MSONDocument {

private:
  QMap<quint32, quint32> FileNodeCountMapping;

  bool m_isEncrypted;

  MSONHeader *m_header;

  std::vector<FreeChunkListFragment *> m_freeChunkList;
  std::vector<TransactionLogFragment *> m_transactionLog;
  std::vector<FileNodeListFragment *> m_hashedChunkList;


  RootFileNodeList *m_rootFileNodeList;

  std::vector<FileNodeListFragment *> m_fileNodeList;

  QMap<quint32, QUuid> globalIdenficationTable;


  // tika copies
  std::vector<ExtendedGUID> revisionListOrder;
//  QMap<ExtendedGUID, Revision> revisionMap;
  QMap<ExtendedGUID, FileNodeChunkReference> revisionManifestLists;
  QMap<ExtendedGUID, FileNodeChunkReference> guidToRef;

  QMap<ExtendedGUID, std::pair<quint32, ExtendedGUID>> revisionRoleMap;
  ExtendedGUID currentRevision;

public:
  MSONDocument();
  ~MSONDocument();

  //  MSONDocument(const MSONDocument &source); // copy constructor
  //  MSONDocument(MSONDocument &&source);      // move constructor

  //  MSONDocument &operator=(const MSONDocument &rhs); // copy assignment
  //  MSONDocument &operator=(MSONDocument &&rhs);      // move assignment

  friend QDataStream &operator<<(QDataStream &ds, const MSONDocument &obj);
  friend QDataStream &operator>>(QDataStream &ds, MSONDocument &obj);

  friend QDebug operator<<(QDebug dbg, const MSONDocument &obj);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

  QMap<quint32, quint32> &getFileNodeCountMapping();
  void setFileNodeCountMapping(const QMap<quint32, quint32> &value);
  bool getIsEncrypted() const;
  void setIsEncrypted(bool isEncrypted);
  MSONHeader *getHeader() const;
  void setHeader(MSONHeader *header);
  std::vector<FreeChunkListFragment *> &getFreeChunkList();
  void
  setFreeChunkList(const std::vector<FreeChunkListFragment *> &freeChunkList);
  std::vector<TransactionLogFragment *> &getTransactionLog();
  void setTransactionLog(
      const std::vector<TransactionLogFragment *> &transactionLog);
  std::vector<FileNodeListFragment *> &getHashedChunkList();
  void setHashedChunkList(
      const std::vector<FileNodeListFragment *> &hashedChunkList);
  RootFileNodeList *getRootFileNodeList() const;
  void setRootFileNodeList(const RootFileNodeList &rootFileNodeList);
  std::vector<FileNodeListFragment *> &getFileNodeList();
  void setFileNodeList(const std::vector<FileNodeListFragment *> &fileNodeList);



};
} // namespace MSONcommon
#endif // MSONDOCUMENT_H
