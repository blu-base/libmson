#ifndef PACKAGINGSTART_H
#define PACKAGINGSTART_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "interfaces/IStreamObject.h"
#include <QUuid>


namespace libmson {
namespace fsshttpb {

class DataElementPackage;
typedef std::shared_ptr<DataElementPackage> DataElementPackage_SPtr_t;
typedef std::weak_ptr<DataElementPackage> DataElementPackage_WPtr_t;

class PackagingStart final : public IStreamObject {
private:
  priv::ExtendedGUID m_storageIndex;
  QUuid m_guidCellSchemaId;

public:
  PackagingStart() = default;

  priv::ExtendedGUID getStorageIndex() const;
  void setStorageIndex(const priv::ExtendedGUID& storageIndex);

  QUuid getGuidCellSchemaId() const;
  void setGuidCellSchemaId(QUuid guidCellSchemaId);

  DataElementPackage_WPtr_t getDataElementPackage();
  void setDataElementPackage(DataElementPackage_SPtr_t obj);

  // IStreamObject interface
private:
  virtual quint64 strObjBody_cb() const override;
  virtual quint64 cbNextHeader() const override;

  virtual void deserializeStrObj(QDataStream& ds) override;
  virtual void serializeStrObj(QDataStream& ds) const override;

public:
  virtual StreamObjectType getType() const override
  {
    return StreamObjectType::ONPackageStart;
  }

  virtual void push_back(IStreamObject_SPtr_t& obj) override;
  virtual IStreamObj_It_t
  insert(IStreamObj_It_t pos, const IStreamObject_SPtr_t& value) override;


  // public:
  //  void push_back(DataElementPackage_SPtr_t& obj);
  //  IStreamObj_It_t
  //  insert(IStreamObj_It_t pos, const DataElementPackage_SPtr_t& value);
};

typedef std::shared_ptr<PackagingStart> PackagingStart_SPtr_t;
typedef std::weak_ptr<PackagingStart> PackagingStart_WPtr_t;

} // namespace fsshttpb
} // namespace libmson

#endif // PACKAGINGSTART_H
