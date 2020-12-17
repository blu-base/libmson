#ifndef CELLMANIFEST_H
#define CELLMANIFEST_H

#include <QtCore/qglobal.h>


#include "DataElement.h"
#include "DataElementBody.h"
#include "streamObjects/CellManifestCurrentRevision.h"

namespace libmson {
namespace packStore {


class CellManifest
    : public DataElementBody
    , public priv::IStreamable {
private:
  streamObj::CellManifestCurrentRevision_SPtr_t m_currentRevision;


public:
  CellManifest();

  streamObj::CellManifestCurrentRevision_SPtr_t getCurrentRevision() const;
  void setCurrentRevision(
      const streamObj::CellManifestCurrentRevision_SPtr_t& currentRevision);

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

typedef std::shared_ptr<CellManifest> CellManifest_SPtr_t;
typedef std::weak_ptr<CellManifest> CellManifest_WPtr_t;


} // namespace packStore
} // namespace libmson

#endif // CELLMANIFEST_H
