#ifndef REVISIONSTOREFILEPARSER_H
#define REVISIONSTOREFILEPARSER_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <memory>

#include "RevisionStoreFile.h"
#include "chunkables/RevisionStoreChunkContainer.h"

namespace libmson {
namespace priv {

class RevisionStoreFileParser {
private:
  QDataStream& m_ds;
  std::shared_ptr<RevisionStoreFile> m_file;

public:
  RevisionStoreFileParser(QDataStream& inputStream);


  std::shared_ptr<RevisionStoreFile> parse();

private:
  // parsers
  bool parseRevisionStoreFileHeader();
  RSChunkContainer_SPtr_t parseFileNode(QDataStream& ds, const quint64 stp, RSChunkContainer_WPtr_t parent);
  bool parseFileNodeListFragment(QDataStream& ds, RSChunkContainer_SPtr_t chunk);
  bool parseFreeChunkListFragment(QDataStream& ds, RSChunkContainer_SPtr_t chunk);
  bool parseTransactionLogFragment(QDataStream& ds, RSChunkContainer_SPtr_t chunk);

  void insertChunkSorted(std::list<RSChunkContainer_SPtr_t>& chunkList, RSChunkContainer_SPtr_t& chunk);
};

} // namespace priv
} // namespace libmson

#endif // REVISIONSTOREFILEPARSER_H
