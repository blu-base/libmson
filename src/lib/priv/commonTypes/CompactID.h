#ifndef COMPACTID_H
#define COMPACTID_H

#include <QtCore/qglobal.h>

#include "ExtendedGUID.h"

#include "../IStreamable.h"

namespace libmson {
namespace priv {

class CompactID : public IStreamable {
private:
  quint8 m_n;
  quint32 guidIndex; // 24bits used.

  static const quint64 sizeInFile = 4;

public:
  CompactID();
  CompactID(const quint8 n, const quint32 compactEGUID);
  CompactID(const QByteArray& bytes);
  virtual ~CompactID() = default;

  quint8 getN() const;
  void setN(const quint8& value);

  quint32 getGuidIndex() const;
  bool setGuidIndex(const quint32& value);

  //  bool isValid() const;
  bool isNull() const;

  QByteArray toByteArray() const;

  QString toString() const;

  static constexpr quint64 getSizeInFile() { return sizeInFile; };

  friend bool operator==(const CompactID& lhs, const CompactID& rhs) noexcept;
  friend bool operator!=(const CompactID& lhs, const CompactID& rhs) noexcept;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

} // namespace priv
} // namespace libmson

#endif // COMPACTID_H
