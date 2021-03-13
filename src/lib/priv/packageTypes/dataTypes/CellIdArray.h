#ifndef CELLIDARRAY_H
#define CELLIDARRAY_H

#include <QtCore/qglobal.h>
#include <vector>

#include "../../IStreamable.h"
#include "CellId.h"

namespace libmson {
namespace fsshttpb {

class CellIdArray : public libmson::priv::IStreamable {
private:
  std::vector<CellId> m_elements;

public:
  CellIdArray();
  CellIdArray(std::vector<CellId> ids);

  quint64 getCount() const;

  std::vector<CellId> getElements() const;
  void setElements(const std::vector<CellId>& elements);

  quint64 getSizeInFile() const;
  static quint64 getSizeInFile(const std::vector<CellId>& ids);

  // IStreamable interface
private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};


} // namespace fsshttpb
} // namespace libmson
#endif // CELLIDARRAY_H
