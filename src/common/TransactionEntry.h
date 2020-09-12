#ifndef TRANSACTIONENTRY_H
#define TRANSACTIONENTRY_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDebug>
#include <QXmlStreamWriter>

#include "IDeserializable.h"
#include "ISerializable.h"

namespace MSONcommon {

class TransactionEntry : public ISerializable, public IDeserializable {
private:
  quint32 srcID;

  quint32 TransactionEntrySwitch;

public:
  TransactionEntry();

  quint32 getSrcID() const;
  void setSrcID(const quint32 &value);
  quint32 getTransactionEntrySwitch() const;
  void setTransactionEntrySwitch(const quint32 &value);

  bool isZero() const;

  friend QDebug operator<<(QDebug dbg, const TransactionEntry &obj);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

private:
  virtual void serialize(QDataStream &ds) const override;
  virtual void deserialize(QDataStream &ds) override;

  void toDebugString(QDebug dbg) const;
};

} // namespace MSONcommon

#endif // TRANSACTIONENTRY_H
