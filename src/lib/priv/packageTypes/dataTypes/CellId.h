#ifndef CELLID_H
#define CELLID_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/ExtendedGUID.h"


namespace libmson {
namespace fsshttpb {

class CellId : public priv::IStreamable {
private:
  priv::ExtendedGUID m_exguid1;
  priv::ExtendedGUID m_exguid2;

public:
  CellId();
  CellId(const priv::ExtendedGUID& exguid1, const priv::ExtendedGUID& exguid2);
  priv::ExtendedGUID getExguid1() const;
  void setExguid1(const priv::ExtendedGUID& exguid1);
  priv::ExtendedGUID getExguid2() const;
  void setExguid2(const priv::ExtendedGUID& exguid2);

  quint64 getSizeInFile() const;
  static quint64 getSizeInFile(
      const priv::ExtendedGUID& exguid1, const priv::ExtendedGUID& exguid2);


  friend bool operator==(const CellId& lhs, const CellId& rhs) noexcept;
  friend bool operator!=(const CellId& lhs, const CellId& rhs) noexcept;

  // IStreamable interface
private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};


} // namespace fsshttpb
} // namespace libmson

#endif // CELLID_H
