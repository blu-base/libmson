#ifndef CHUNKABLEUTILS_H
#define CHUNKABLEUTILS_H

#include <QtCore/qglobal.h>

#include "../chunkables/Chunkable.h"
#include <list>
#include <memory>
#include <vector>

namespace libmson {
namespace priv {

template <typename Chunkably>
static std::vector<Chunkable_SPtr_t>
castToChunkable(std::vector<std::shared_ptr<Chunkably>> vec);

template <typename Chunkably>
static std::list<Chunkable_SPtr_t>
castToChunkable(std::list<std::shared_ptr<Chunkably>> vec);

} // namespace priv
} // namespace libmson


#endif // CHUNKABLEUTILS_H
