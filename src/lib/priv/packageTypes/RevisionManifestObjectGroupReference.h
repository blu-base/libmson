#ifndef REVISIONMANIFESTOBJECTGROUPREFERENCE_H
#define REVISIONMANIFESTOBJECTGROUPREFERENCE_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "interfaces/IStreamObject.h"


namespace libmson {
namespace fsshttpb {

class RevisionManifestObjectGroupReference : public IStreamObject {
private:
  priv::ExtendedGUID m_objectGroup;

public:
  RevisionManifestObjectGroupReference();

  priv::ExtendedGUID getObjectGroup() const;
  void setObjectGroup(const priv::ExtendedGUID& objectGroup);

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

typedef std::shared_ptr<RevisionManifestObjectGroupReference>
    RevisionManifestObjectGroupReference_SPtr_t;
typedef std::weak_ptr<RevisionManifestObjectGroupReference>
    RevisionManifestObjectGroupReference_WPtr_t;


} // namespace fsshttpb
} // namespace libmson
#endif // REVISIONMANIFESTOBJECTGROUPREFERENCE_H
