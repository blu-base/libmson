#ifndef LONGEXTGUID_H
#define LONGEXTGUID_H

#include <QUuid>
#include <QtCore/qglobal.h>

#include "../../IStreamable.h"

namespace libmson {
namespace fsshttpb {

/** Represents the Serial Number data type according to [MS-FSSHTTPB]
 * section 2.2.1.9. */
class LongExtGuid : public priv::IStreamable {
private:
  QUuid m_guid;
  quint64 m_serialNumber;

public:
  LongExtGuid();
  LongExtGuid(const QUuid& guid, const quint64& serialNumber);

  // IStreamable interface
  QUuid getGuid() const;
  void setGuid(const QUuid& guid);

  quint64 getSerialNumber() const;
  void setSerialNumber(const quint64& serialNumber);

  quint64 getSizeInFile() const;

  QString toString() const;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

} // namespace fsshttpb
} // namespace libmson

#endif // LONGEXTGUID_H
