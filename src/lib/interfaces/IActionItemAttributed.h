#ifndef IACTIONITEMATTRIBUTED_H
#define IACTIONITEMATTRIBUTED_H

#include <QDateTime>
#include <QtCore/qglobal.h>


namespace libmson {

class IActionItemAttributed {
protected:
  IActionItemAttributed()          = default;
  virtual ~IActionItemAttributed() = default;

public:
  virtual bool isCompleted() = 0;
  virtual bool isDisabled()  = 0;

  virtual QDateTime getCreationDate()   = 0;
  virtual QDateTime getCompletionDate() = 0;
};
} // namespace libmson


#endif // IACTIONITEMATTRIBUTED_H
