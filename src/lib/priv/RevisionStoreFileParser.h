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

  /// parses the header, adds the containers to m_file and returns the pointer
  /// to the header container
  RSChunkContainer_SPtr_t parseRevisionStoreFileHeader(QDataStream& ds);
  RSChunkContainer_SPtr_t parseFileNode(
      QDataStream& ds, const quint64 stp, RSChunkContainer_WPtr_t parent);

  /// parses the FreeChunkListFrragments and adds ChunkContainer to m_file
  void parseFreeChunkListFragments(
      QDataStream& ds, RSChunkContainer_WPtr_t firstFragment);


  RSChunkContainer_SPtr_t
  parseObjectSpaceObjectPropSet(QDataStream& ds, RSChunkContainer_SPtr_t chunk);


  /// parses a fragment. Returns a RSChunkContainer_SPtr_t if there is a next
  /// Fragment specified That RSChunkContainer_SPtr_t is not inserted to any
  /// std::list<RSChunkContainer_SPtr_t>& chunkList. This has to be done by
  /// calling method.
  RSChunkContainer_SPtr_t
  parseFileNodeListFragment(QDataStream& ds, RSChunkContainer_SPtr_t chunk);

  /// parses a fragment tree. Returns a RSChunkContainer_WPtr_t list
  std::vector<RSChunkContainer_WPtr_t>
  parseFileNodeList(QDataStream& ds, RSChunkContainer_WPtr_t firstFragment);


  //  bool
  //  parseFreeChunkListFragment(QDataStream& ds, RSChunkContainer_SPtr_t
  //  chunk);
  bool parseTransactionLogFragment(
      QDataStream& ds, RSChunkContainer_SPtr_t firstFragment);

  void insertChunkSorted(
      std::list<RSChunkContainer_SPtr_t>& chunkList,
      RSChunkContainer_SPtr_t& chunk);
};

} // namespace priv
} // namespace libmson

#endif // REVISIONSTOREFILEPARSER_H
