#ifndef DATAELEMENTHASH_H
#define DATAELEMENTHASH_H

#include <QtCore/qglobal.h>


#include "../../IStreamable.h"
#include "../../commonTypes/BinaryItem.h"
#include "StreamObject.h"


namespace libmson {
namespace packStore {
namespace streamObj {


class DataElementHash
    : public StreamObject
    , public priv::IStreamable {
private:
  quint64 m_scheme;
  BinaryItem m_data;

public:
  DataElementHash();
  quint64 getScheme() const;
  void setScheme(const quint64& scheme);

  BinaryItem getData() const;
  void setData(const BinaryItem& data);

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

typedef std::shared_ptr<DataElementHash> DataElementHash_SPtr_t;
typedef std::weak_ptr<DataElementHash> DataElementHash_WPtr_t;


} // namespace streamObj
} // namespace packStore
} // namespace libmson

#endif // DATAELEMENTHASH_H
