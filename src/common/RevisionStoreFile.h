#ifndef REVISIONSTOREFILE_H
#define REVISIONSTOREFILE_H

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

#include "IRevisionStoreFileObject.h"

namespace MSONcommon {

class RevisionStoreFile : public IRevisionStoreFileObject {

private:
  QMap<quint32, quint32> FileNodeCountMapping;

  bool m_isEncrypted;

  std::shared_ptr<MSONHeader> m_header;

  std::vector<std::shared_ptr<FreeChunkListFragment>> m_freeChunkList;
  std::vector<std::shared_ptr<TransactionLogFragment>> m_transactionLog;
  std::vector<std::shared_ptr<FileNodeListFragment>> m_hashedChunkList;

  std::shared_ptr<RootFileNodeList> m_rootFileNodeList;

  std::vector<std::shared_ptr<FileNodeListFragment>> m_fileNodeList;

  QMap<quint32, QUuid> globalIdenficationTable;

  // tika copies
  std::vector<ExtendedGUID> revisionListOrder;
  //  QMap<ExtendedGUID, Revision> revisionMap;
  QMap<ExtendedGUID, FileNodeChunkReference> revisionManifestLists;
  QMap<ExtendedGUID, FileNodeChunkReference> guidToRef;
  QMap<ExtendedGUID, FileNode> guidToObject;

  QMap<ExtendedGUID, std::pair<quint32, ExtendedGUID>> revisionRoleMap;
  ExtendedGUID currentRevision;

public:
  RevisionStoreFile();
  ~RevisionStoreFile() = default;

  QMap<quint32, quint32> &fileNodeCountMapping();
  QMap<quint32, quint32> getFileNodeCountMapping() const;
  void setFileNodeCountMapping(const QMap<quint32, quint32> &value);

  bool isEncrypted() const;
  void setIsEncrypted(const bool isEncrypted);

  std::shared_ptr<MSONHeader> getHeader() const;
  void setHeader(std::shared_ptr<MSONHeader> header);

  std::vector<std::shared_ptr<FreeChunkListFragment>> &freeChunkList();
  std::vector<std::shared_ptr<FreeChunkListFragment>> getFreeChunkList() const;
  void setFreeChunkList(
      const std::vector<std::shared_ptr<FreeChunkListFragment>> &freeChunkList);

  std::vector<std::shared_ptr<TransactionLogFragment>> getTransactionLog();
  void
  setTransactionLog(const std::vector<std::shared_ptr<TransactionLogFragment>>
                        &transactionLog);

  std::vector<std::shared_ptr<FileNodeListFragment>> getHashedChunkList();
  void
  setHashedChunkList(const std::vector<std::shared_ptr<FileNodeListFragment>>
                         &hashedChunkList);

  std::shared_ptr<RootFileNodeList> getRootFileNodeList() const;
  void setRootFileNodeList(
      const std::shared_ptr<RootFileNodeList> &rootFileNodeList);

  std::vector<std::shared_ptr<FileNodeListFragment>> getFileNodeList();
  void setFileNodeList(
      const std::vector<std::shared_ptr<FileNodeListFragment>> &fileNodeList);

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;
};

} // namespace MSONcommon

#endif // REVISIONSTOREFILE_H
