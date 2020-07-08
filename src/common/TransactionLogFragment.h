#ifndef TRANSACTIONLOGFRAGMENT_H
#define TRANSACTIONLOGFRAGMENT_H

#include <QtCore/qglobal.h>
#include <vector>

#include <QDataStream>
#include <QDebug>

#include "TransactionEntry.h"
#include "commonTypes/FileChunkReference64x32.h"
namespace MSONcommon {
class TransactionLogFragment {
private:
  quint64 m_size;

  /**
   * @brief An array of TransactionEntry structures.
   * @var sizeTable
   *
   * A transaction MUST add all of its entries to the array sequentially
   * and MUST terminate with a sentinel entry with TransactionEntry.srcID set to
   * 0x00000001.
   */
  std::vector<TransactionEntry *> sizeTable;

  FileChunkReference64x32 nextFragment;

public:
  TransactionLogFragment(quint64 size);
  ~TransactionLogFragment();

  friend QDataStream &operator<<(QDataStream &ds,
                                 const TransactionLogFragment &obj);
  friend QDataStream &operator>>(QDataStream &ds, TransactionLogFragment &obj);

  friend QDebug operator<<(QDebug dbg, const TransactionLogFragment &obj);

  std::vector<TransactionEntry *> getSizeTable() const;
  void setSizeTable(const std::vector<TransactionEntry *> &value);

  FileChunkReference64x32 getNextFragment() const;
  void setNextFragment(const FileChunkReference64x32 &value);

private:
  void serialize(QDataStream &ds) const;
  void deserialize(QDataStream &ds);

  void toDebugString(QDebug dbg) const;
};
} // namespace MSONcommon
#endif // TRANSACTIONLOGFRAGMENT_H
