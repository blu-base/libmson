#ifndef CHARSET_H
#define CHARSET_H

#include <QtCore/qglobal.h>

#include "../../priv/IStreamable.h"

namespace libmson {

/** List of charactersets according to [MS-ONE] section 2.3.55
 */
enum class CHARSET : quint8 {
  ANSI        = 0,
  DEFAULT     = 1,
  SYMBOL      = 2,
  MAC         = 77,
  SHIFTJIS    = 128,
  HANGUL      = 129,
  JOHAB       = 130,
  GB2312      = 134,
  CHINESEBIG5 = 136,
  GREEK       = 161,
  TURKISH     = 162,
  VIETNAMESE  = 163,
  HEBREW      = 177,
  ARABIC      = 178,
  BALTIC      = 186,
  RUSSIAN     = 204,
  THAI        = 222,
  EASTEUROPE  = 238,
  OEM         = 255,
};

/** @class Charset
 * @brief specifies character set of paragraph referencing this instance
 *
 * represents the simply type according to [MS-ONE] section 2.3.55
 *
 */
class Charset : public priv::IStreamable {
private:
  CHARSET m_charset;
public:
  Charset();
  Charset(const CHARSET charset);



  // IStreamable interface
  CHARSET getCharset() const;
  void setCharset(const CHARSET& charset);

  QString toString() const;
  static QString toString(const CHARSET& charset);


private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};



} // namespace libmson


#endif // CHARSET_H
