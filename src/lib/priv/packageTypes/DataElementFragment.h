#ifndef DATAELEMENTFRAGMENT_H
#define DATAELEMENTFRAGMENT_H

#include <QtCore/qglobal.h>

#include "DataElement.h"
#include "DataElementBody.h"

namespace libmson {
namespace packStore {

class DataElementFragment
    : public DataElementBody
    , public priv::IStreamable {
private:
  CompactExtGuid m_extendedGuid;
  quint64 m_size;

  quint64 m_fileChunkStart;

  QByteArray m_data;

public:
  DataElementFragment() ;

  CompactExtGuid getExtendedGuid() const;
  void setExtendedGuid(const CompactExtGuid& extendedGuid);
  quint64 getSize() const;
  void setSize(const quint64& size);
  quint64 getFileChunkStart() const;
  void setFileChunkStart(const quint64& fileChunkStart);
  quint64 getFileChunkSize() const;
  QByteArray getData() const;
  void setData(const QByteArray& data);
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

typedef std::shared_ptr<DataElementFragment> DataElementFragment_SPtr_t;
typedef std::weak_ptr<DataElementFragment> DataElementFragment_WPtr_t;

} // namespace packStore
} // namespace libmson

#endif // DATAELEMENTFRAGMENT_H
