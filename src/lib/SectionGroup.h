#ifndef SECTIONGROUP_H
#define SECTIONGROUP_H

#include <QtCore/qglobal.h>

#include "interfaces/ISection.h"

namespace libmson {

class SectionGroup : public ISection {
public:
  SectionGroup();


  bool isRecycleBin();


  // ISection interface
public:
  virtual bool isUnread() override;

  // IFileObjectAttributed interface
public:
  virtual QString getFilePath() override;

  // IHierarchyObjectAttributed interface
public:
  virtual ObjectID getObjectID() override;
  virtual QString getName() override;
  virtual QDateTime getLastModifiedTime() override;
  virtual bool isCurrentlyViewed() override;
  virtual bool isInRecycleBin() override;

  // INode interface
public:
  virtual INode* getParent() override;
  virtual std::vector<INode_SPtr_t> getChildren() override;
  virtual INodeType type() override;
  virtual std::weak_ptr<Section> getSection() override;



private:
  class Impl;

  std::unique_ptr<Impl> p;
};


typedef std::shared_ptr<SectionGroup> SectionGroup_SPtr_t;
typedef std::weak_ptr<SectionGroup> SectionGroup_WPtr_t;


} // namespace libmson

#endif // SECTIONGROUP_H
