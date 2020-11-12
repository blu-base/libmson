#ifndef ENUMS_H
#define ENUMS_H

#include <QtCore/qglobal.h>

namespace libmson {
    namespace priv {









enum class Charset : quint8 {
ANSI_CHARSET = 0,
DEFAULT_CHARSET = 1,
SYMBOL_CHARSET = 2,
MAC_CHARSET = 77,
SHIFTJIS_CHARSET = 128,
HANGUL_CHARSET = 129,
JOHAB_CHARSET = 130,
GB2312_CHARSET = 134,
CHINESEBIG5_CHARSET = 136,
GREEK_CHARSET = 161,
TURKISH_CHARSET = 162,
VIETNAMESE_CHARSET = 163,
HEBREW_CHARSET = 177,
ARABIC_CHARSET = 178,
BALTIC_CHARSET = 186,
RUSSIAN_CHARSET = 204,
THAI_CHARSET = 222,
EASTEUROPE_CHARSET = 238,
OEM_CHARSET = 255,
};

} // namespace priv
} // namespace libmson

#endif // ENUMS_H
