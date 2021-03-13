#ifndef DATAELEMENTFRAGMENT_H
#define DATAELEMENTFRAGMENT_H

#include <QtCore/qglobal.h>

#include "interfaces/IStreamObject.h"
#include <priv/commonTypes/ExtendedGUID.h>

namespace libmson {
namespace fsshttpb {

class DataElementFragment : public IStreamObject {
private:
  priv::ExtendedGUID m_extendedGuid;

  quint64 m_size;

  quint64 m_fileChunkStart;

  QByteArray m_data;

public:
  DataElementFragment();

  priv::ExtendedGUID getExtendedGuid() const;
  void setExtendedGuid(const priv::ExtendedGUID& extendedGuid);
  quint64 getSize() const;
  void setSize(const quint64& size);
  quint64 getFileChunkStart() const;
  void setFileChunkStart(const quint64& fileChunkStart);
  quint64 getFileChunkSize() const;
  QByteArray getData() const;
  void setData(const QByteArray& data);

  // IStreamObject interface
protected:
  virtual quint64 strObjBody_cb() const override;
  virtual quint64 cbNextHeader() const override;

public:
  virtual StreamObjectType getType() const override
  {
    return StreamObjectType::DataElementFragment;
  }
  virtual void push_back(IStreamObject_SPtr_t& obj) override;
  virtual IStreamObj_It_t insert(IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj) override;

private:
  virtual void deserializeStrObj(QDataStream& ds) override;
  virtual void serializeStrObj(QDataStream& ds) const override;
};

typedef std::shared_ptr<DataElementFragment> DataElementFragment_SPtr_t;
typedef std::weak_ptr<DataElementFragment> DataElementFragment_WPtr_t;

} // namespace fsshttpb
} // namespace libmson

#endif // DATAELEMENTFRAGMENT_H
