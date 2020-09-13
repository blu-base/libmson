#ifndef IFILECHUNKREFERENCE_H
#define IFILECHUNKREFERENCE_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDebug>

#include <QXmlStreamWriter>

#include "../IRevisionStoreFileObject.h"

namespace MSONcommon {

enum FCR_INITTYPE {
  FCRZERO,
  FCRNIL,
};

template <typename S, typename C>
class IFileChunkReference : public IRevisionStoreFileObject {
protected:
  S m_stp;
  C m_cb;

public:
  //    IFileChunkReference();

  virtual bool is_fcrNil() const = 0;
  virtual bool is_fcrZero() const = 0;

  virtual void set_fcrNil() = 0;
  virtual void set_fcrZero() = 0;

  virtual S stp() const = 0;
  virtual void setStp(const S &stp) = 0;

  virtual C cb() const = 0;
  virtual void setCb(const C &cb) = 0;

private:
  /**
   * @brief prints the IFileChunkReference to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  virtual void toDebugString(QDebug dbg) const = 0;

  friend QDebug operator<<(QDebug dbg, const IFileChunkReference &obj) {
    obj.toDebugString(dbg);
    return dbg;
  };
};

} // namespace MSONcommon

#endif // IFILECHUNKREFERENCE_H
