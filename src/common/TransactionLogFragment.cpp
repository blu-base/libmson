#include "TransactionLogFragment.h"

TransactionLogFragment::TransactionLogFragment(quint64 size) : m_size{size} {}

FileChunkReference64x32 TransactionLogFragment::getNextFragment() const {
  return nextFragment;
}

void TransactionLogFragment::setNextFragment(
    const FileChunkReference64x32 &value) {
  nextFragment = value;
}

void TransactionLogFragment::deserialize(QDataStream &ds) {
  quint64 num_entries = (m_size - 12) / 8;

  for (size_t i{0}; i < num_entries; i++) {
    TransactionEntry *entry = new TransactionEntry;
    ds >> *entry;
    getSizeTable().push_back(entry);
  }

  ds >> nextFragment;
}

void TransactionLogFragment::serialize(QDataStream &ds) const {

  for (auto *te : sizeTable) {
    ds << te;
  }
  ds << nextFragment;
}

void TransactionLogFragment::toDebugString(QDebug dbg) const {
  dbg << "TransactionLogFragment: size: "
      << QString("0x%1").arg(m_size, 16, 16, QLatin1Char('0')) << '\n'
      << " nextFragment: " << nextFragment;
  for (auto *te : sizeTable) {
    dbg << te << '\n';
  }
}

QDataStream &operator<<(QDataStream &ds, const TransactionEntry &obj) {}

QDataStream &operator>>(QDataStream &ds, TransactionEntry &obj) {}

QDebug operator<<(QDebug dbg, const TransactionEntry &obj) {}

std::vector<TransactionEntry *> TransactionLogFragment::getSizeTable() const {
  return sizeTable;
}

void TransactionLogFragment::setSizeTable(
    const std::vector<TransactionEntry *> &value) {
  sizeTable = value;
}
