#ifndef CELLID_H
#define CELLID_H

#include <QtCore/qglobal.h>

#include "../IStreamable.h"
#include "CompactExtGuid.h"


namespace libmson {
namespace packStore {

class CellId : public priv::IStreamable
{
private:
  CompactExtGuid m_exguid1;
  CompactExtGuid m_exguid2;

public:
  CellId();
  CellId(const CompactExtGuid& exguid1, const CompactExtGuid& exguid2);
  CompactExtGuid getExguid1() const;
  void setExguid1(const CompactExtGuid& exguid1);
  CompactExtGuid getExguid2() const;
  void setExguid2(const CompactExtGuid& exguid2);

  // IStreamable interface
private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};



} // namespace packStore
} // namespace libmson

#endif // CELLID_H
