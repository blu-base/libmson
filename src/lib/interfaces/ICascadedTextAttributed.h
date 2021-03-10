#ifndef ICASCADEDTEXTATTRIBUTED_H
#define ICASCADEDTEXTATTRIBUTED_H

#include <QtCore/qglobal.h>

namespace libmson {

class ICascadedTextAttributed
{
protected:
  ICascadedTextAttributed()          = default;
  virtual ~ICascadedTextAttributed() = default;

public:
  virtual QString getStyle()           = 0;
  virtual quint32 getQuickStyleIndex() = 0;

  /** \brief return lang in ISO 639 format
   */
  virtual QString getLang()            = 0;
};

}

#endif // ICASCADEDTEXTATTRIBUTED_H
