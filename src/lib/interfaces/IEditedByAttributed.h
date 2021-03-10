#ifndef IEDITEDBYATTRIBUTED_H
#define IEDITEDBYATTRIBUTED_H

#include <QtCore/qglobal.h>
#include <QDateTime>

namespace libmson {

class IEditedByAttributes {
protected:
  IEditedByAttributes()  = default;
  ~IEditedByAttributes() = default;

public:
  virtual QString getAuthor()             = 0;
  virtual QString getAuthorInitials()     = 0;
  virtual QString getAuthorResolutionID() = 0;

  virtual QString getLastModifiedBy()             = 0;
  virtual QString getLastModifiedByInitials()     = 0;
  virtual QString getLastModifiedByResolutionID() = 0;

  virtual QDateTime getCreationTime() = 0;
};

} // namespace libmson
#endif // IEDITEDBYATTRIBUTED_H
