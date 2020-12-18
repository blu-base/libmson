#ifndef COMPACTEXTGUIDARRAY_H
#define COMPACTEXTGUIDARRAY_H

#include <QtCore/qglobal.h>

#include <vector>

#include "../IStreamable.h"
#include "CompactExtGuid.h"

namespace libmson {
namespace packStore {


class CompactExtGuidArray : public libmson::priv::IStreamable {
  std::vector<CompactExtGuid> m_elements;

public:
  CompactExtGuidArray();

  quint64 getCount() const;

  std::vector<CompactExtGuid> getElements() const;
  void setElements(const std::vector<CompactExtGuid>& elements);

  quint64 getSizeInFile() const;


  // IStreamable interface
private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};


} // namespace packStore
} // namespace libmson
#endif // COMPACTEXTGUIDARRAY_H
