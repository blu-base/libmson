#ifndef HIERARCHYOBJECTATTRIBUTES_H
#define HIERARCHYOBJECTATTRIBUTES_H

#include <QtCore/qglobal.h>
#include <memory>

#include <QUuid>
#include <QDateTime>

namespace libmson {

class HierarchyObjectAttributes {
public:
  HierarchyObjectAttributes();
  ~HierarchyObjectAttributes();

  QString getName();

  // void setName(const QString& name);

  QUuid getObjectID();

  QDateTime getLastModifiedTime();

  bool isCurrentlyViewed();

  bool isInRecycleBin();

private:
  class Impl;

  std::unique_ptr<Impl> p;
};

} // namespace libmson

#endif // HIERARCHYOBJECTATTRIBUTES_H
