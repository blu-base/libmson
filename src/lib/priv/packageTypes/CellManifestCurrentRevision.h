#ifndef CELLMANIFESTCURRENTREVISION_H
#define CELLMANIFESTCURRENTREVISION_H

#include <QtCore/qglobal.h>

#include "interfaces/IStreamObject.h"
#include <priv/commonTypes/ExtendedGUID.h>


namespace libmson {
namespace fsshttpb {

class CellManifestCurrentRevision : public IStreamObject {
private:
  priv::ExtendedGUID m_extendedGuid;

public:
  CellManifestCurrentRevision();

  priv::ExtendedGUID getExtendedGuid() const;
  void setExtendedGuid(const priv::ExtendedGUID& extendedGuid);

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

typedef std::shared_ptr<CellManifestCurrentRevision>
    CellManifestCurrentRevision_SPtr_t;
typedef std::weak_ptr<CellManifestCurrentRevision>
    CellManifestCurrentRevision_WPtr_t;

} // namespace packStore
} // namespace libmson

#endif // CELLMANIFESTCURRENTREVISION_H
