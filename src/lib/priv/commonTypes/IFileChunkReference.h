#ifndef IFILECHUNKREFERENCE_H
#define IFILECHUNKREFERENCE_H

#include "../IStreamable.h"

#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

enum class FCR_INIT {
  ZERO,
  NIL,
};

template <typename S, typename C>
class IFileChunkReference : public IStreamable {
protected:
  S m_stp;
  C m_cb;

public:
  //    IFileChunkReference();

  virtual bool is_fcrNil() const  = 0;
  virtual bool is_fcrZero() const = 0;

  virtual void set_fcrNil()  = 0;
  virtual void set_fcrZero() = 0;

  virtual S stp() const             = 0;
  virtual void setStp(const S& stp) = 0;

  virtual C cb() const            = 0;
  virtual void setCb(const C& cb) = 0;
};

} // namespace priv
} // namespace libmson

#endif // IFILECHUNKREFERENCE_H
