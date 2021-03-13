#ifndef DATAELEMENTHASH_H
#define DATAELEMENTHASH_H

#include <QtCore/qglobal.h>


#include "interfaces/IStreamObject.h"

namespace libmson {
namespace fsshttpb {

class DataElementHash : public IStreamObject {
private:
  quint64 m_scheme;
  QByteArray m_data;

public:
  DataElementHash();
  quint64 getScheme() const;
  void setScheme(const quint64 scheme);

  QByteArray getData() const;
  void setData(const QByteArray& data);

  // IStreamObject interface
protected:
  virtual quint64 strObjBody_cb() const override;
  virtual quint64 cbNextHeader() const override;

public:
  virtual StreamObjectType getType() const override;
  virtual void push_back(IStreamObject_SPtr_t& obj) override;
  virtual IStreamObj_It_t
  insert(IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj) override;

private:
  virtual void deserializeStrObj(QDataStream& ds) override;
  virtual void serializeStrObj(QDataStream& ds) const override;
};

typedef std::shared_ptr<DataElementHash> DataElementHash_SPtr_t;
typedef std::weak_ptr<DataElementHash> DataElementHash_WPtr_t;


} // namespace fsshttpb
} // namespace libmson

#endif // DATAELEMENTHASH_H
