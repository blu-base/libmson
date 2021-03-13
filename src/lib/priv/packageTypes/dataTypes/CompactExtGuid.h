#ifndef COMPACTEXTGUID_H
#define COMPACTEXTGUID_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/ExtendedGUID.h"

namespace libmson {
namespace fsshttpb {

/** used to store information of the used width of CompactExtGuid*/
enum class CompactExtGuidWidth : int8_t {
  /** represents ExtendedGUID of [MS-FSSHTTPB] section 2.2.1.7.1. It has a
     width of 1 byte. It can only contain
     {{00000000-0000-0000-0000-000000000000},0}
   */
  CompressedNull = 0,
  /** represents ExtendedGUID of [MS-FSSHTTPB] section 2.2.1.7.2. It has a
     width of 17 byte.*/
  CompressedN5Bit = 1,
  /** represents ExtendedGUID of [MS-FSSHTTPB] section 2.2.1.7.3. It has a
     width of 18 byte.*/
  CompressedN10Bit = 2,
  /** represents ExtendedGUID of [MS-FSSHTTPB] section 2.2.1.7.4. It has a
     width of 19 byte.*/
  CompressedN17Bit = 3,
  /** represents ExtendedGUID of [MS-FSSHTTPB] section 2.2.1.7.5. It has a
     width of 21 byte.*/
  Uncompressed = 4,

  /** is used to select widthType depending on the variable n*/
  Auto = -1
};

/** Data Type representing [MS-FSSHTTPB] section 2.2.1.7. */
class CompactExtGuid : public priv::IStreamable {
private:
  priv::ExtendedGUID m_base;
  CompactExtGuidWidth m_type;


public:
  CompactExtGuid();

  /**By default(CompactExtGuidWidth::Auto) the CompactExtGuidWidth will be
   * selected depending on the set guid and n. If the specified
   * CompactExtGuidWidth is not wide enough to accommodate the specified n, then
   * a suitable CompactExtGuidWidth will be selected---ignoring the given type
   * input. If the specified width type is larger than necessary for the
   * specified n, the type will not be changed
   */
  CompactExtGuid(
      const QUuid& guid, const quint32& n,
      const CompactExtGuidWidth& type = CompactExtGuidWidth::Auto);

  /**By default(CompactExtGuidWidth::Auto) the CompactExtGuidWidth will be
   * selected depending on the set guid and n. If the specified
   * CompactExtGuidWidth is not wide enough to accommodate the specified n, then
   * a suitable CompactExtGuidWidth will be selected---ignoring the given type
   * input. If the specified width type is larger than necessary for the
   * specified n, the type will not be changed
   */
  CompactExtGuid(
      const priv::ExtendedGUID& extGUID,
      const CompactExtGuidWidth& type = CompactExtGuidWidth::Auto);

  QUuid getGuid() const;
  void setGuid(const QUuid& guid);

  quint32 getN() const;
  /** sets the variable n. Will update CompactExtGuidWidth when n does not fit
   * into current width type. It will not decrease the width, only enlarge it if
   * necessary. */
  void setN(const quint32& n);

  CompactExtGuidWidth getWidthType() const;

  /** Will update CompactExtGuidWidth. When n does not fit into
   * specified width type it will use the next best(larger) width type.*/
  void setWidthType(const CompactExtGuidWidth& type);

  QString toString() const;

  priv::ExtendedGUID getExtendedGUID() const;

  friend bool
  operator==(const CompactExtGuid& lhs, const CompactExtGuid& rhs) noexcept;
  friend bool
  operator!=(const CompactExtGuid& lhs, const CompactExtGuid& rhs) noexcept;
  friend bool
  operator<=(const CompactExtGuid& lhs, const CompactExtGuid& rhs) noexcept;
  friend bool
  operator>=(const CompactExtGuid& lhs, const CompactExtGuid& rhs) noexcept;
  friend bool
  operator<(const CompactExtGuid& lhs, const CompactExtGuid& rhs) noexcept;
  friend bool
  operator>(const CompactExtGuid& lhs, const CompactExtGuid& rhs) noexcept;

  uint64_t getSizeInFile() const;
  static uint64_t getSizeInFile(const priv::ExtendedGUID& guid);

  static QString typeToString(const CompactExtGuidWidth& type);

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;

  void
  setSuggestedTypeOrMinimalWidthType(const CompactExtGuidWidth& requestedType);

  static CompactExtGuidWidth
  determineMinimalWidthType(const priv::ExtendedGUID& guid);
};

} // namespace fsshttpb
} // namespace libmson

#endif // COMPACTEXTGUID_H
