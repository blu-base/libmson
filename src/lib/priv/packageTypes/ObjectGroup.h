#ifndef OBJECTGROUPDATADATATYPE_H
#define OBJECTGROUPDATADATATYPE_H

#include <QtCore/qglobal.h>


#include "DataElementBody.h"
#include "streamObjects/DataElementHash.h"
#include "streamObjects/ObjectGroupData.h"
#include "streamObjects/ObjectGroupDeclarations.h"
#include "streamObjects/ObjectGroupMetadataDeclarations.h"

namespace libmson {
namespace packStore {

class ObjectGroup
    : public DataElementBody
    , public priv::IStreamable {
private:
  streamObj::DataElementHash_SPtr_t m_dataElementHash;
  streamObj::ObjectGroupDeclarations_SPtr_t m_objectGroupDeclarations;
  streamObj::ObjectGroupMetadataDeclarations_SPtr_t
      m_objectGroupMetadataDeclarations;
  streamObj::ObjectGroupData_SPtr_t m_objectGroupData;

public:
  ObjectGroup();

  streamObj::DataElementHash_SPtr_t getDataElementHash() const;
  void
  setDataElementHash(const streamObj::DataElementHash_SPtr_t& dataElementHash);
  streamObj::ObjectGroupDeclarations_SPtr_t getObjectGroupDeclarations() const;
  void setObjectGroupDeclarations(
      const streamObj::ObjectGroupDeclarations_SPtr_t& objectGroupDeclarations);
  streamObj::ObjectGroupMetadataDeclarations_SPtr_t
  getObjectGroupMetadataDeclarations() const;
  void setObjectGroupMetadataDeclarations(
      const streamObj::ObjectGroupMetadataDeclarations_SPtr_t&
          objectGroupMetadataDeclarations);
  streamObj::ObjectGroupData_SPtr_t getObjectGroupData() const;
  void
  setObjectGroupData(const streamObj::ObjectGroupData_SPtr_t& objectGroupData);

  // IStreamable interface
private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;

  // DataElementBody interface
protected:
  virtual quint64 cb() const override;

public:
  virtual DataElementType getType() const override;
};

typedef std::shared_ptr<ObjectGroup> ObjectGroup_SPtr_t;
typedef std::weak_ptr<ObjectGroup> ObjectGroup_WPtr_t;

} // namespace packStore
} // namespace libmson

#endif // OBJECTGROUPDATADATATYPE_H
