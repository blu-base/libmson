#include "TransactionEntry.h"

TransactionEntry::TransactionEntry() {}

QDataStream &operator<<(QDataStream &ds, const TransactionEntry &obj) {
  obj.serialize(ds);
}

QDataStream &operator>>(QDataStream &ds, TransactionEntry &obj) {
    obj.deserialize(ds);
}

QDebug operator<<(QDebug dbg, const TransactionEntry &obj) {
    obj.toDebugString(dbg);
}

void TransactionEntry::serialize(QDataStream &ds) const {
  ds << srcID;
  ds << TransactionEntrySwitch;
}

void TransactionEntry::deserialize(QDataStream &ds) {
  ds >> srcID;
  ds >> TransactionEntrySwitch;
}

void TransactionEntry::toDebugString(QDebug dbg) const {
  dbg.noquote() << "TransactionEntry:  srcID: "
                << QString("0x%1").arg(srcID, 8, 16, QLatin1Char('0'))
                << " transactionEntrySwitch: "
                << QString("0x%1").arg(TransactionEntrySwitch, 8, 16,
                                       QLatin1Char('0'))
                << '\n';
}

quint32 TransactionEntry::getSrcID() const { return srcID; }

void TransactionEntry::setSrcID(const quint32 &value) { srcID = value; }

quint32 TransactionEntry::getTransactionEntrySwitch() const {
  return TransactionEntrySwitch;
}

void TransactionEntry::setTransactionEntrySwitch(const quint32 &value) {
  TransactionEntrySwitch = value;
}
