#include "HierarchyObjectAttributes.h"
namespace libmson {




class HierarchyObjectAttributes::Impl {
public:
  Impl();
  ~Impl();

  QString getName();

  QUuid getObjectID();

  QDateTime getLastModifiedTime();

  bool isCurrentlyViewed();

  bool isInRecycleBin();

private:


};


HierarchyObjectAttributes::HierarchyObjectAttributes() {}

HierarchyObjectAttributes::~HierarchyObjectAttributes() {}

QString HierarchyObjectAttributes::getName() {}

QUuid HierarchyObjectAttributes::getObjectID() {}

QDateTime HierarchyObjectAttributes::getLastModifiedTime() {}

bool HierarchyObjectAttributes::isCurrentlyViewed() {}

bool HierarchyObjectAttributes::isInRecycleBin() {}

}
