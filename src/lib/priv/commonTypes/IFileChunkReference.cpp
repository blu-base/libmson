#include "IFileChunkReference.h"


namespace libmson {
namespace priv {

template <typename S, typename C> S IFileChunkReference<S, C>::stp() const {
  return m_stp;
}

template <typename S, typename C>
void IFileChunkReference<S, C>::setStp(const S &stp) {
  m_stp = stp;
}

template <typename S, typename C> C IFileChunkReference<S, C>::cb() const {
  return m_cb;
}

template <typename S, typename C>
void IFileChunkReference<S, C>::setCb(const C &cb) {
  m_cb = cb;
}

} // namespace priv
} // namespace libmson
