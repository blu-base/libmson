#include "ChunkableUtils.h"

namespace libmson {
namespace priv {

template <typename Chunkably>
std::vector<Chunkable_SPtr_t>
castToChunkable(std::vector<std::shared_ptr<Chunkably>> vec)
{
  return std::transform(
      vec.begin(), vec.end(), vec.begin(), [](Chunkably c) -> Chunkable_SPtr_t {
        return std::static_pointer_cast<Chunkable>(c);
      });
}


template <typename Chunkably>
std::list<Chunkable_SPtr_t>
castToChunkable(std::list<std::shared_ptr<Chunkably>> vec)
{
  return std::transform(
      vec.begin(), vec.end(), vec.begin(), [](Chunkably c) -> Chunkable_SPtr_t {
        return std::static_pointer_cast<Chunkable>(c);
      });
}


} // namespace priv
} // namespace libmson
