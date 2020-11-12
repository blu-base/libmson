#include "RevisionStoreChunkContainer.h"

#include "FreeChunkListFragment.h"
#include "RevisionStoreFileHeader.h"

namespace libmson {
namespace priv {

bool RevisionStoreChunkContainer::isParsed() const { return m_isParsed; }

void RevisionStoreChunkContainer::setIsParsed(bool value) { m_isParsed = value; }

RevisionStoreChunkContainer::RevisionStoreChunkContainer(
    std::shared_ptr<Chunkable> chunkable, const quint64 initialLocationInFile, const quint64 initialCb)
    : m_initialStp(initialLocationInFile), m_initialCb(initialCb), m_chunkable(chunkable), m_isParsed(false)
{
}

std::shared_ptr<Chunkable> RevisionStoreChunkContainer::getContent() { return m_chunkable; }

RevisionStoreChunkType RevisionStoreChunkContainer::getType() { return m_chunkable->getType(); }

quint64 RevisionStoreChunkContainer::getInitialStp() const { return m_initialStp; }

quint64 RevisionStoreChunkContainer::getInitialCb() const { return m_initialCb; }


} // namespace priv
} // namespace libmson
