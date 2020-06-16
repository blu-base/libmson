#ifndef EXTENDEDGUID_H
#define EXTENDEDGUID_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDebug>
#include <QUuid>

class ExtendedGUID {

private:
  QUuid m_guid;
  quint32 data_n;

public:
  ExtendedGUID();
  ExtendedGUID(const QUuid &guid, const quint32 &n);

  //  operator=(const ExtendedGUID &guid)

  QUuid &getGuid();
  void setGuid(const QUuid &guid);

  quint32 getN() const;
  void setN(const quint32 &n);

  bool isValid() const;
  bool isNull() const;

  //  bool equals(const ExtendedGUID &extGuid) const;

  friend QDataStream &operator<<(QDataStream &ds, const ExtendedGUID &obj);
  ;
  friend QDataStream &operator>>(QDataStream &ds, ExtendedGUID &obj);
  friend QDebug operator<<(QDebug dbg, const ExtendedGUID &obj);
  ;

  friend bool operator==(const ExtendedGUID &lhs,
                         const ExtendedGUID &rhs) noexcept;
  friend bool operator!=(const ExtendedGUID &lhs,
                         const ExtendedGUID &rhs) noexcept;
  friend bool operator<=(const ExtendedGUID &lhs,
                         const ExtendedGUID &rhs) noexcept;
  friend bool operator>=(const ExtendedGUID &lhs,
                         const ExtendedGUID &rhs) noexcept;

private:
  void deserialize(QDataStream &ds);

  void serialize(QDataStream &ds) const;

  void toDebugString(QDebug dbg) const;
};

#endif // EXTENDEDGUID_H
