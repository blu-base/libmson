#ifndef EXTENDEDGUID_H
#define EXTENDEDGUID_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDebug>
#include <QUuid>
#include <QXmlStreamWriter>

#include "../IDeserializable.h"
#include "../ISerializable.h"

namespace MSONcommon {

class ExtendedGUID : public ISerializable, public IDeserializable {
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

  QString toString() const;

  //  bool equals(const ExtendedGUID &extGuid) const;

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

  void generateXml(QXmlStreamWriter &xmlWriter) const;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  void toDebugString(QDebug dbg) const;
};

} // namespace MSONcommon

#endif // EXTENDEDGUID_H
