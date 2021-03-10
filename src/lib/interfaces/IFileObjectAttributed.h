#ifndef IFILEOBJECTATTRIBUTED_H
#define IFILEOBJECTATTRIBUTED_H

#include <QString>
#include <QtCore/qglobal.h>

namespace libmson {

class IFileObjectAttributed {
protected:
  IFileObjectAttributed()          = default;
  virtual ~IFileObjectAttributed() = default;

public:
  virtual QString getFilePath() = 0;
};

} // namespace libmson

#endif // IFILEOBJECTATTRIBUTED_H
