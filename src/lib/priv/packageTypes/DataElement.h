#ifndef DATAELEMENT_H
#define DATAELEMENT_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "dataTypes/LongExtGuid.h"
#include "interfaces/DataElementType.h"
#include "interfaces/IStreamObject.h"


namespace libmson {
namespace fsshttpb {

class DataElement : public IStreamObject {
protected:
  priv::ExtendedGUID m_dataElementExtGuid;

  LongExtGuid m_serialNumber;

  quint64 m_dataElementType;

//  DataElementBody_SPtr_t m_body;

public:
  DataElement();
  DataElement(
      const priv::ExtendedGUID& dataElementExtGuid,
      const LongExtGuid& serialNumber,
      const quint64& dataElementType);
  virtual ~DataElement() = default;

  //  virtual DataElementType getType() const = 0;

  priv::ExtendedGUID getDataElementExtGuid() const;
  void setDataElementExtGuid(const priv::ExtendedGUID& dataElementExtGuid);
  LongExtGuid getSerialNumber() const;
  void setSerialNumber(const LongExtGuid& serialNumber);
  quint64 getDataElementType() const;
  void setDataElementType(const quint64& dataElementType);
  DataElementType getDataElementTypeEnum() const;
  void setDataElementType(const DataElementType& dataElementType);
//  DataElementBody_SPtr_t getBody() const;
//  void setBody(const DataElementBody_SPtr_t& body);

  QString dataElementTypeToString();
  static QString dataElementTypeToString(DataElementType type);

  friend class PackageStoreFileParser;

  // IStreamObject interface
protected:
  virtual quint64 strObjBody_cb() const override;
  virtual quint64 cbNextHeader() const override;

public:
  virtual StreamObjectType getType() const override
  {
    return StreamObjectType::DataElement;
  }
  virtual void push_back(IStreamObject_SPtr_t& obj) override;
  virtual IStreamObj_It_t
  insert(IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj) override;

private:
  virtual void deserializeStrObj(QDataStream& ds) override;
  virtual void serializeStrObj(QDataStream& ds) const override;


  // Data Element body parsers
private:
  void parseCellManifest(QDataStream& ds);
  void parseDataElementFragment(QDataStream& ds);
  void parseObjectBlob(QDataStream& ds);
  void parseObjectGroup(QDataStream& ds);
  void parseRevisionManifest(QDataStream& ds);
  void parseStorageIndex(QDataStream& ds);
  void parseStorageManifest(QDataStream& ds);
};

typedef std::shared_ptr<DataElement> DataElement_SPtr_t;
typedef std::weak_ptr<DataElement> DataElement_WPtr_t;

} // namespace fsshttpb
} // namespace libmson

#endif // DATAELEMENT_H
