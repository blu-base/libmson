#ifndef DATAELEMENT_H
#define DATAELEMENT_H

#include <QtCore/qglobal.h>

#include "../commonTypes/CompactExtGuid.h"
#include "../commonTypes/CompactUInt64.h"
#include "../commonTypes/LongExtGuid.h"
#include "DataElementBody.h"
#include "StreamObjectHeader.h"


namespace libmson {
namespace packStore {


enum class DataElementType : uint8_t {
  StorageIndex        = 0x01,
  StorageManifest     = 0x02,
  CellManifest        = 0x03,
  RevisionManifest    = 0x04,
  ObjectGroup         = 0x05,
  DataElementFragment = 0x06,
  ObjectDataBLOB      = 0x0A,
};

class DataElement {
protected:
  CompactExtGuid m_dataElementExtGuid;

  LongExtGuid m_serialNumber;

  CompactUInt64 m_dataElementType;

  DataElementBody_SPtr_t m_body;

public:
  DataElement();
  DataElement(
      const CompactExtGuid& dataElementExtGuid, const LongExtGuid& serialNumber,
      const CompactUInt64& dataElementType);
  virtual ~DataElement() = default;

  //  virtual DataElementType getType() const = 0;

  CompactExtGuid getDataElementExtGuid() const;
  void setDataElementExtGuid(const CompactExtGuid& dataElementExtGuid);
  LongExtGuid getSerialNumber() const;
  void setSerialNumber(const LongExtGuid& serialNumber);
  CompactUInt64 getDataElementType() const;
  void setDataElementType(const CompactUInt64& dataElementType);
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
