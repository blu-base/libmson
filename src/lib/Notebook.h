#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include <QtCore/qglobal.h>

#include "interfaces/IFileObjectAttributed.h"
#include "interfaces/IHierarchyObjectAttributed.h"
#include "interfaces/INode.h"

namespace libmson {

class Color;
class ISection;


/**
 * @brief The Section class describes a [MS-ONE] Notebook (.onetoc2)
 * and the respective .one files
 */
class Notebook
    : public INode
    , public IHierarchyObjectAttributed
    , public IFileObjectAttributed {



   Notebook();
public:
  Notebook(QDataStream& ds);
  Notebook(const QString& fileName);
  ~Notebook();


  std::vector<std::shared_ptr<ISection>> getSections();

  QString getNickName();

  Color getColor();


  bool isUnread();


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
  virtual Section getSection() override;


private:
  class Impl;

  std::unique_ptr<Impl> p;
};


} // namespace libmson

#endif // NOTEBOOK_H
