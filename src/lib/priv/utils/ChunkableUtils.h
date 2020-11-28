#ifndef CHUNKABLEUTILS_H
#define CHUNKABLEUTILS_H

#include <QtCore/qglobal.h>

#include "../chunkables/Chunkable.h"
#include <list>
#include <memory>
#include <vector>

namespace libmson {
namespace priv {

class FileChunkReference64x32;
class FileChunkReference64;
class FileNodeChunkReference;

enum class FCR_INIT;
enum class FNCR_STP_FORMAT;
enum class FNCR_CB_FORMAT;

typedef std::shared_ptr<class RevisionStoreFile> RevisionStoreFile_SPtr_t;

template <typename Chunkably>
static std::vector<Chunkable_SPtr_t>
castToChunkable(std::vector<std::shared_ptr<Chunkably>> vec);

template <typename Chunkably>
static std::list<Chunkable_SPtr_t>
castToChunkable(std::list<std::shared_ptr<Chunkably>> vec);

quint64
stpFromChunk(RevisionStoreFile_SPtr_t revStoreFile, Chunkable_WPtr_t chunk);

template <typename Chunkably_SPtr_t>
quint64
stpTillIterator(std::list<Chunkably_SPtr_t>& list, Chunkable_WPtr_t chunk);

FileChunkReference64x32 getFcr64x32FromChunk(
    RevisionStoreFile_SPtr_t revStoreFile, Chunkable_WPtr_t chunk,
    FCR_INIT preferedState);

FileChunkReference64 getFcr64FromChunk(
    RevisionStoreFile_SPtr_t revStoreFile, Chunkable_WPtr_t chunk,
    FCR_INIT preferedState);

FileNodeChunkReference getFncrFromChunk(
    RevisionStoreFile_SPtr_t revStoreFile, Chunkable_WPtr_t chunk,
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat, FCR_INIT preferedState);

} // namespace priv
} // namespace libmson


#endif // CHUNKABLEUTILS_H
