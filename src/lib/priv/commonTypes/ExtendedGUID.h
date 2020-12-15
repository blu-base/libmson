#ifndef EXTENDEDGUID_H
#define EXTENDEDGUID_H

#include <QtCore/qglobal.h>

#include "../IStreamable.h"
#include <QUuid>


namespace libmson {
namespace priv {

class ExtendedGUID : public IStreamable {
private:
  QUuid m_guid;
  quint32 data_n;

  static const quint64 sizeInFile = 20;

public:
  ExtendedGUID();
  ExtendedGUID(const QUuid& guid, const quint32& n);

  //  operator=(const ExtendedGUID &guid)

  QUuid getGuid() const;
  void setGuid(const QUuid& guid);

  quint32 getN() const;
  void setN(const quint32& n);

  bool isValid() const;
  bool isNull() const;

  QString toString() const;

  friend bool
  operator==(const ExtendedGUID& lhs, const ExtendedGUID& rhs) noexcept;
  friend bool
  operator!=(const ExtendedGUID& lhs, const ExtendedGUID& rhs) noexcept;
  friend bool
  operator<=(const ExtendedGUID& lhs, const ExtendedGUID& rhs) noexcept;
  friend bool
  operator>=(const ExtendedGUID& lhs, const ExtendedGUID& rhs) noexcept;
  friend bool
  operator<(const ExtendedGUID& lhs, const ExtendedGUID& rhs) noexcept;
  friend bool
  operator>(const ExtendedGUID& lhs, const ExtendedGUID& rhs) noexcept;

  static constexpr quint64 getSizeInFile() { return sizeInFile; };

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};


} // namespace priv
} // namespace libmson

#endif // EXTENDEDGUID_H
