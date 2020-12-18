#ifndef COMPACTUINT64_H
#define COMPACTUINT64_H

#include <QtCore/qglobal.h>

#include "../IStreamable.h"

namespace libmson {
namespace packStore {

class CompactUInt64 : public priv::IStreamable {
private:
  quint64 m_value;

public:
  CompactUInt64();
  CompactUInt64(const quint64& value);

  quint64 getValue() const;
  void setValue(const quint64& value);

  quint64 getSizeInFile() const;

  /** returns the size of a CompactUInt64 it would have with the given value */
  static quint64 getSizeInFile(const quint64& value);

  // IStreamable interface
private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;

  static const uint64_t limit7bit  = 0x01;
  static const uint64_t limit14bit = 0x0080;
  static const uint64_t limit21bit = 0x004000;
  static const uint64_t limit28bit = 0x0200000;
  static const uint64_t limit35bit = 0x010000000;
  static const uint64_t limit42bit = 0x00800000000;
  static const uint64_t limit49bit = 0x0040000000000;
  static const uint64_t limit64bit = 0x0002000000000000;
};


} // namespace packStore
} // namespace libmson
#endif // COMPACTUINT64_H
