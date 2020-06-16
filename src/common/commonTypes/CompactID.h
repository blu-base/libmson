#ifndef COMPACTID_H
#define COMPACTID_H

#include <QtCore/qglobal.h>

#include "ExtendedGUID.h"

class CompactID {
private:
  uint8_t n;
  uint32_t guidIndex; // 24bits used.

  // \todo weak pointer?
  ExtendedGUID *eguid;

public:
  CompactID();
  CompactID(ExtendedGUID *guid);
  CompactID(const uint8_t n, const uint32_t compactEGUID);
  CompactID(const uint8_t n, const uint32_t compactEGUID, ExtendedGUID *guid);
  CompactID(const QByteArray &bytes);
  ~CompactID();

  uint8_t getN() const;
  void setN(const uint8_t &value);

  uint32_t getGuidIndex() const;
  bool setGuidIndex(const uint32_t &value);

  ExtendedGUID *getExtendedGUID() const;
  void setExtendedGUID(ExtendedGUID *const eguid);

  bool isValid() const;
  bool isNull() const;

  QByteArray toByteArray() const;

  QString toString() const;

  friend QDataStream &operator<<(QDataStream &s, const CompactID &obj);
  friend QDataStream &operator>>(QDataStream &s, CompactID &obj);

  friend QDebug operator<<(QDebug dbg, const CompactID &obj);

  friend bool operator==(const CompactID &lhs, const CompactID &rhs) noexcept;
  friend bool operator!=(const CompactID &lhs, const CompactID &rhs) noexcept;
};

#endif // COMPACTID_H
