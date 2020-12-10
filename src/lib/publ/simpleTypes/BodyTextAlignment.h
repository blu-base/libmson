#ifndef BODYTEXTALIGNMENT_H
#define BODYTEXTALIGNMENT_H

#include <QtCore/qglobal.h>

#include "../../priv/IStreamable.h"

namespace libmson {

/** @class BodyTextAlignment
 * @brief specifies alignment of body text
 *
 * represents simple type according to [MS-ONE] section 2.3.17
 *
 * apperently value must be 0, and must be ignored
 * \todo determine actual usage
 */
class BodyTextAlignment : public priv::IStreamable {
private:
  quint32 m_value;

public:
  BodyTextAlignment();
  BodyTextAlignment(const quint32 val);

  quint32 getValue() const;
  void setValue(const quint32 val);

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

} // namespace libmson

#endif // BODYTEXTALIGNMENT_H
