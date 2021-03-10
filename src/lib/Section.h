#ifndef SECTION_H
#define SECTION_H

#include <QtCore/qglobal.h>
#include <memory>

#include "FormatIdentifier.h"
#include "interfaces/ISection.h"

namespace libmson {

class Color;
class Page;


/**
 * @brief The Section class describes a single OneNote (.one) section
 * as described in [MS-ONE] section 1.3.1
 */
class Section
    : public ISection
    , public std::enable_shared_from_this<Section> {

  Section();

public:
  Color getColor();

  bool isEncrypted();
  bool isLocked();
  bool isReadOnly();
  bool areAllPagesAvailable();
  bool isDeletedPages();


  QUuid getGuid();
  OnFormat getFormat();


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
  virtual INodeType type() override { return INodeType::Section; }
  virtual std::weak_ptr<Section> getSection() override
  {
    return weak_from_this();
  }


private:
  class Impl;

  std::unique_ptr<Impl> p;
};

typedef std::shared_ptr<Section> Section_SPtr_t;
typedef std::weak_ptr<Section> Section_WPtr_t;

} // namespace libmson

#endif // SECTION_H
