#ifndef TRANSACTIONENTRY_H
#define TRANSACTIONENTRY_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDebug>
#include <QXmlStreamWriter>
namespace MSONcommon {
class TransactionEntry {
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

  friend QDataStream &operator<<(QDataStream &ds, const TransactionEntry &obj);
  friend QDataStream &operator>>(QDataStream &ds, TransactionEntry &obj);

  friend QDebug operator<<(QDebug dbg, const TransactionEntry &obj);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

private:
  void serialize(QDataStream &ds) const;
  void deserialize(QDataStream &ds);

  void toDebugString(QDebug dbg) const;
};
} // namespace MSONcommon
#endif // TRANSACTIONENTRY_H
