#ifndef DATAELEMENT_H
#define DATAELEMENT_H

#include <QtCore/qglobal.h>

#include <priv/commonTypes/CompactExtGuid.h>
#include <priv/commonTypes/LongExtGuid.h>

#include "StreamObjectHeader.h"

#include "interfaces/IDataElementBody.h"
#include "interfaces/DataElementType.h"


namespace libmson {
namespace packStore {

class DataElement {
protected:
  CompactExtGuid m_dataElementExtGuid;

  LongExtGuid m_serialNumber;

  quint64 m_dataElementType;

  DataElementBody_SPtr_t m_body;

public:
  DataElement();
  DataElement(
      const CompactExtGuid& dataElementExtGuid, const LongExtGuid& serialNumber,
      const quint64& dataElementType);
  virtual ~DataElement() = default;

  //  virtual DataElementType getType() const = 0;

  CompactExtGuid getDataElementExtGuid() const;
  void setDataElementExtGuid(const CompactExtGuid& dataElementExtGuid);
  LongExtGuid getSerialNumber() const;
  void setSerialNumber(const LongExtGuid& serialNumber);
  quint64 getDataElementType() const;
  void setDataElementType(const quint64& dataElementType);
  DataElementType getDataElementTypeEnum() const;
  void setDataElementType(const DataElementType& dataElementType);
  DataElementBody_SPtr_t getBody() const;
  void setBody(const DataElementBody_SPtr_t& body);

  friend class PackageStoreFileParser;


protected:
};

typedef std::shared_ptr<DataElement> DataElement_SPtr_t;
typedef std::weak_ptr<DataElement> DataElement_WPtr_t;

} // namespace packStore
} // namespace libmson

#endif // DATAELEMENT_H
