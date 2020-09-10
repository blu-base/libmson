#ifndef COMPACTID_H
#define COMPACTID_H

#include <QtCore/qglobal.h>

#include "ExtendedGUID.h"

namespace MSONcommon {

class CompactID {
private:
  quint8 m_n;
  quint32 guidIndex; // 24bits used.

  // \todo weak pointer?
  ExtendedGUID *eguid;

public:
  CompactID();
  CompactID(ExtendedGUID *guid);
  CompactID(const quint8 m_n, const quint32 compactEGUID);
  CompactID(const quint8 m_n, const quint32 compactEGUID, ExtendedGUID *guid);
  CompactID(const QByteArray &bytes);
  ~CompactID();

  quint8 getN() const;
  void setN(const quint8 &value);

  quint32 getGuidIndex() const;
  bool setGuidIndex(const quint32 &value);

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

  void generateXml(QXmlStreamWriter &xmlWriter) const;

private:
  void deserialize(QDataStream &ds);
  void serialize(QDataStream &ds) const;
  void toDebugString(QDebug dbg) const;
};

} // namespace MSONcommon

#endif // COMPACTID_H
