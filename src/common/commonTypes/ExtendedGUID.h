#ifndef EXTENDEDGUID_H
#define EXTENDEDGUID_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDebug>
#include <QUuid>
#include <QXmlStreamWriter>

#include "../IRevisionStoreFileObject.h"

namespace MSONcommon {

class ExtendedGUID : public IRevisionStoreFileObject {
private:
  QUuid m_guid;
  quint32 data_n;

  static const quint64 sizeInFile = 20;

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

  friend bool operator==(const ExtendedGUID &lhs,
                         const ExtendedGUID &rhs) noexcept;
  friend bool operator!=(const ExtendedGUID &lhs,
                         const ExtendedGUID &rhs) noexcept;
  friend bool operator<=(const ExtendedGUID &lhs,
                         const ExtendedGUID &rhs) noexcept;
  friend bool operator>=(const ExtendedGUID &lhs,
                         const ExtendedGUID &rhs) noexcept;

  static constexpr quint64 getSizeInFile() { return sizeInFile; };

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;
};

} // namespace MSONcommon

#endif // EXTENDEDGUID_H
