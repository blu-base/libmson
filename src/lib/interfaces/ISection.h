#ifndef ISECTION_H
#define ISECTION_H

#include <QtCore/qglobal.h>

#include "INode.h"
#include "interfaces/IFileObjectAttributed.h"
#include "interfaces/IHierarchyObjectAttributed.h"


namespace libmson {

class Notebook_WPtr_t;


class ISection
    : public INode
    , public IHierarchyObjectAttributed
    , public IFileObjectAttributed {
protected:
  ISection()          = default;
  virtual ~ISection() = default;

public:
  virtual bool isUnread() = 0;


  virtual Notebook_WPtr_t getNotebook() = 0;

  virtual std::vector<std::shared_ptr<ISection>> getSections() = 0;
};

typedef std::shared_ptr<ISection> ISection_SPtr_t;
typedef std::weak_ptr<ISection> ISection_WPtr_t;

} // namespace libmson

#endif // ISECTION_H
