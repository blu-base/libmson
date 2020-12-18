#ifndef OBJECTDATABLOB_H
#define OBJECTDATABLOB_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "StreamObject.h"

namespace libmson {
namespace packStore {
namespace streamObj {

class ObjectDataBLOB
    : public StreamObject
    , public libmson::priv::IStreamable {
private:
  QByteArray m_data;

public:
  ObjectDataBLOB() = default;
  QByteArray getData() const;
  void setData(const QByteArray& data);

  // IStreamable interface
private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;

  // StreamObject interface
protected:
  virtual quint64 body_cb() const override;

public:
  virtual StreamObjectType getType() const override;
};


typedef std::shared_ptr<ObjectDataBLOB> ObjectDataBLOB_SPtr_t;
typedef std::weak_ptr<ObjectDataBLOB> ObjectDataBLOB_WPtr_t;


} // namespace streamObj
} // namespace packStore
} // namespace libmson

#endif // OBJECTDATABLOB_H
