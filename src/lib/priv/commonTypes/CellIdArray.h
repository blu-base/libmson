#ifndef CELLIDARRAY_H
#define CELLIDARRAY_H

#include <QtCore/qglobal.h>
#include <vector>

#include "../IStreamable.h"
#include "CellId.h"

namespace libmson {
namespace packStore {

class CellIdArray : public libmson::priv::IStreamable {
private:
  std::vector<CellId> m_elements;

public:
  CellIdArray();

  quint64 getCount() const;

  std::vector<CellId> getElements() const;
  void setElements(const std::vector<CellId>& elements);

  quint64 getSizeInFile() const;

  // IStreamable interface
private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};


} // namespace packStore
} // namespace libmson
#endif // CELLIDARRAY_H
