#ifndef PAGESIZE_H
#define PAGESIZE_H

#include <QtCore/qglobal.h>

#include "../interfaces/IStreamable.h"

namespace libmson {

/* Prescribed page types used in the PageSize class
 */
enum class PageSizeType : quint32 {
  fitToContent = 0x0,
  us_statement = 0x1,
  ansi_letter  = 0x2,
  ansi_tabloid = 0x3,
  us_legel     = 0x4,
  a3           = 0x5,
  a4           = 0x6,
  a5           = 0x7,
  a6           = 0x8,
  b4           = 0x9,
  b5           = 0x10,
  b6           = 0x11,
  japPostcard  = 0x12,
  indexCard    = 0x13,
  billfold     = 0x14,
  custom       = 0x15,
};


/**
 * @class PageSize
 * @brief Prescribed size of a Page.
 * Represents simple type of [MS-ONE] section 2.3.36.
 *
 * Declares whether page is a fixed, predefined size, or resizes automatically.
 *
 */
class PageSize : public IStreamable {
private:
  quint32 m_type;

public:
  PageSize();
  virtual ~PageSize() = default;

  void setPageType(const PageSizeType& type);
  PageSizeType getPageType() const;

  void setPageTypeValue(const quint32 type);
  quint32 getPageTypeValue() const;

  static QString typeToString(const PageSizeType type);
  static QString typeToString(const quint32 type);


private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

} // namespace libmson

#endif // PAGESIZE_H
