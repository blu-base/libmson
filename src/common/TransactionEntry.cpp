#include "TransactionEntry.h"
#include "helper/Helper.h"
namespace MSONcommon {
TransactionEntry::TransactionEntry() : srcID{}, TransactionEntrySwitch{} {}

QDataStream &operator<<(QDataStream &ds, const TransactionEntry &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, TransactionEntry &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const TransactionEntry &obj) {
  obj.toDebugString(dbg);
  return dbg;
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
  dbg.noquote() << "TransactionEntry:  srcID: " << qStringHex(srcID, 8)
                << " transactionEntrySwitch: "
                << qStringHex(TransactionEntrySwitch, 8) << '\n';
}

quint32 TransactionEntry::getSrcID() const { return srcID; }

void TransactionEntry::setSrcID(const quint32 &value) { srcID = value; }

quint32 TransactionEntry::getTransactionEntrySwitch() const {
  return TransactionEntrySwitch;
}

void TransactionEntry::setTransactionEntrySwitch(const quint32 &value) {
  TransactionEntrySwitch = value;
}
} // namespace MSONcommon
