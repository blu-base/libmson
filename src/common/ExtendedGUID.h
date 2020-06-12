#ifndef EXTENDEDGUID_H
#define EXTENDEDGUID_H

#include <QtCore/qglobal.h>

#include <QUuid>

class ExtendedGUID : public QUuid
{


private:

public:
  uint32_t data_n;

  ExtendedGUID();
  ExtendedGUID(const QUuid &guid, const ulong &n);
  ExtendedGUID(const QByteArray &text);
  ExtendedGUID(const QString &text,const ulong &n);
  ExtendedGUID(const char * &text, ulong n);
  ExtendedGUID(uint32_t l, uint16_t w1, uint16_t w2, uint8_t b[8], uint32_t n);
  ExtendedGUID(uint32_t l, uint16_t w1, uint16_t w2, uint8_t b1, uint8_t b2, uint8_t b3,
               uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7, uint8_t b8, uint32_t n);
  //  operator=(const ExtendedGUID &guid)

  QUuid getGuid() const;
  void setGuid(const QUuid& guid);

  uint32_t getN() const;
  void setN(const uint32_t& n);

  bool isValid() const;
  bool isNull() const;

  //  bool equals(const ExtendedGUID &extGuid) const;

  QByteArray toByteArray() const;
  QByteArray toByteArray(QUuid::StringFormat mode) const;
  QByteArray toRfc4122() const;

  static ExtendedGUID fromString(QStringView string) noexcept;
  static ExtendedGUID fromString(QLatin1String string) noexcept;
  static ExtendedGUID fromRfc4122(const QByteArray & uuid);
  QString toString() const;
  QString toString(QUuid::StringFormat mode) const;

  bool operator>(const ExtendedGUID &other) const noexcept;
  bool operator<(const ExtendedGUID &other) const noexcept;


  friend QDataStream& operator<<(QDataStream& s, const ExtendedGUID& obj);
  friend QDataStream& operator>>(QDataStream& s, ExtendedGUID& obj);

  friend QDebug operator<<(QDebug dbg, const ExtendedGUID& obj);

  friend bool operator==(const ExtendedGUID& lhs, const ExtendedGUID& rhs) noexcept;
  friend bool operator!=(const ExtendedGUID& lhs, const ExtendedGUID& rhs) noexcept;
  friend bool operator<=(const ExtendedGUID& lhs, const ExtendedGUID& rhs) noexcept;
  friend bool operator>=(const ExtendedGUID& lhs, const ExtendedGUID& rhs) noexcept;


};

#endif // EXTENDEDGUID_H
