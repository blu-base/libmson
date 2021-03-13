#ifndef DATAELEMENTPACKAGE_H
#define DATAELEMENTPACKAGE_H

#include <memory>
#include <QtCore/qglobal.h>

#include "interfaces/IStreamObject.h"

namespace libmson {
namespace fsshttpb {

class DataElement;
typedef std::shared_ptr<DataElement> DataElement_SPtr_t;
typedef std::weak_ptr<DataElement> DataElement_WPtr_t;

class DataElementPackage : public IStreamObject {
private:
  quint8 m_reserved;

public:
  DataElementPackage();

  friend class PackageStoreFileParser;

  std::vector<DataElement_WPtr_t> getObjects();
  std::vector<DataElement_WPtr_t> getDataElements();

  DataElement_WPtr_t at(size_t pos);

  void push_back(DataElement_SPtr_t& obj);
  IStreamObj_It_t
  insert(IStreamObj_It_t pos, const DataElement_SPtr_t& obj);

  // IStreamObject interface
private:
  virtual quint64 strObjBody_cb() const override;
  virtual quint64 cbNextHeader() const override;

  virtual void deserializeStrObj(QDataStream& ds) override;
  virtual void serializeStrObj(QDataStream& ds) const override;

public:
  virtual StreamObjectType getType() const override
  {
    return StreamObjectType::DataElementPackage;
  }

  virtual void push_back(IStreamObject_SPtr_t& obj) override;
  virtual IStreamObj_It_t insert(IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj) override;
};


} // namespace packStore
} // namespace libmson


#endif // DATAELEMENTPACKAGE_H
