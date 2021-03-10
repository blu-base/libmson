#ifndef PAGE_H
#define PAGE_H

#include <QDateTime>
#include <QtCore/qglobal.h>

#include "interfaces/ICascadedTextAttributed.h"
#include "interfaces/IHierarchyObjectAttributed.h"
#include "interfaces/INode.h"

namespace libmson {

class Page
    : public INode
    , public IHierarchyObjectAttributed
    , public ICascadedTextAttributed {
public:
  Page();


  // TagDef
  // QuickStyleDef
  // XPSFile
  // Meta
  // MediaPlaylist
  // PageSettings
  // Title

  // std::vector<std::shared_ptr<PageContent>> Outline
  // std::vector<std::shared_ptr<PageContent>> Image
  // std::vector<std::shared_ptr<PageContent>> InkDrawing
  // std::vector<std::shared_ptr<PageContent>> InsertedFile
  // std::vector<std::shared_ptr<PageContent>> MediaFile
  // std::vector<std::shared_ptr<PageContent>> FutureObject


  QDateTime getDateTime(); // creation Time?
  // selected
  bool isSubPage();
  quint8 getPageLevel();
  bool isCollapsed();
  bool isUnread();
  bool isIndexed();

  bool hasFutureContent();

  QString getStationaryName();


  // INode interface
public:
  virtual INode* getParent() override;
  virtual std::vector<INode_SPtr_t> getChildren() override;
  virtual INodeType type() override;
  virtual Section getSection() override;


  // ICascadedTextAttributed interface
public:
  virtual QString getStyle() override;
  virtual quint32 getQuickStyleIndex() override;
  virtual QString getLang() override;

  // IHierarchyObjectAttributed interface
public:
  virtual ObjectID getObjectID() override;
  virtual QString getName() override;
  virtual QDateTime getLastModifiedTime() override;
  virtual bool isCurrentlyViewed() override;
  virtual bool isInRecycleBin() override;

private:
  class Impl;

  std::unique_ptr<Impl> p;
};


typedef std::shared_ptr<Page> Page_SPtr_t;
typedef std::weak_ptr<Page> Page_WPtr_t;


} // namespace libmson

#endif // PAGE_H
