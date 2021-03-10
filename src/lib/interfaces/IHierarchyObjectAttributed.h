#ifndef IHIERARCHYOBJECTATTRIBUTED_H
#define IHIERARCHYOBJECTATTRIBUTED_H

#include <QtCore/qglobal.h>
#include <QUuid>
#include <QDateTime>

namespace libmson {

class ObjectID;

class IHierarchyObjectAttributed {
protected:
  IHierarchyObjectAttributed()          = default;
  virtual ~IHierarchyObjectAttributed() = default;

public:
  virtual ObjectID getObjectID() = 0;
  virtual QString getName()   = 0;

  virtual QDateTime getLastModifiedTime()= 0;

  virtual bool isCurrentlyViewed()= 0;
  virtual bool isInRecycleBin()= 0;

};

}


#endif // IHIERARCHYOBJECTATTRIBUTED_H
