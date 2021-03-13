#ifndef REVISIONMANIFESTSTREAMOBJ_H
#define REVISIONMANIFESTSTREAMOBJ_H

#include <QtCore/qglobal.h>

#include "interfaces/IStreamObject.h"
#include <priv/commonTypes/ExtendedGUID.h>

namespace libmson {
namespace fsshttpb {


class RevisionManifest : public IStreamObject {
private:
  priv::ExtendedGUID m_revisionId;
  priv::ExtendedGUID m_baseRevisionId;

public:
  RevisionManifest();
  priv::ExtendedGUID getRevisionId() const;
  void setRevisionId(const priv::ExtendedGUID& revisionId);
  priv::ExtendedGUID getBaseRevisionId() const;
  void setBaseRevisionId(const priv::ExtendedGUID& baseRevisionId);

  // IStreamObject interface
protected:
  virtual quint64 strObjBody_cb() const override;
  virtual quint64 cbNextHeader() const override;

public:
  virtual StreamObjectType getType() const override;
  virtual void push_back(IStreamObject_SPtr_t& obj) override;
  virtual IStreamObj_It_t insert(IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj) override;

private:
  virtual void deserializeStrObj(QDataStream& ds) override;
  virtual void serializeStrObj(QDataStream& ds) const override;
};


typedef std::shared_ptr<RevisionManifest> RevisionManifest_SPtr_t;
typedef std::weak_ptr<RevisionManifest> RevisionManifest_WPtr_t;


} // namespace fsshttpb
} // namespace libmson


#endif // REVISIONMANIFESTSTREAMOBJ_H
