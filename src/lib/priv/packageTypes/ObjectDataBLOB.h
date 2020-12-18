#ifndef OBJECTDATABLOBDATAELEMENT_H
#define OBJECTDATABLOBDATAELEMENT_H

#include <QtCore/qglobal.h>


#include "DataElement.h"
#include "DataElementBody.h"
#include "streamObjects/ObjectDataBLOB.h"

namespace libmson {
namespace packStore {

class ObjectDataBLOB
    : public DataElementBody
    , public priv::IStreamable {
private:
  streamObj::ObjectDataBLOB_SPtr_t m_object;

public:
  ObjectDataBLOB();
  streamObj::ObjectDataBLOB_SPtr_t getObject() const;
  void setObject(const streamObj::ObjectDataBLOB_SPtr_t& object);

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

typedef std::shared_ptr<ObjectDataBLOB> ObjectDataBLOB_SPtr_t;
typedef std::weak_ptr<ObjectDataBLOB> ObjectDataBLOB_WPtr_t;

} // namespace packStore
} // namespace libmson

#endif // OBJECTDATABLOBDATAELEMENT_H
