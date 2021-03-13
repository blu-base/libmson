#ifndef COMPACTEXTGUIDARRAY_H
#define COMPACTEXTGUIDARRAY_H

#include <QtCore/qglobal.h>

#include <vector>

#include "../../IStreamable.h"
#include "../../commonTypes/ExtendedGUID.h"

namespace libmson {
namespace fsshttpb {


class CompactExtGuidArray : public libmson::priv::IStreamable {
  std::vector<priv::ExtendedGUID> m_elements;

public:
  CompactExtGuidArray();
  CompactExtGuidArray(std::vector<priv::ExtendedGUID> guids);

  quint64 getCount() const;

  std::vector<priv::ExtendedGUID> getElements() const;
  void setElements(const std::vector<priv::ExtendedGUID>& elements);

  quint64 getSizeInFile() const;
  static quint64 getSizeInFile(const std::vector<priv::ExtendedGUID>& guids);


  // IStreamable interface
private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};


} // namespace fsshttpb
} // namespace libmson
#endif // COMPACTEXTGUIDARRAY_H
