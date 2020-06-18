#ifndef TRANSACTIONLOGFRAGMENT_H
#define TRANSACTIONLOGFRAGMENT_H

#include <vector>
#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDebug>

#include "commonTypes/FileChunkReference64x32.h"
#include "TransactionEntry.h"

class TransactionLogFragment
{
private:
    quint64 m_size;

    /**
     * @brief An array of TransactionEntry structures.
     * @var sizeTable
     *
     * A transaction MUST add all of its entries to the array sequentially
     * and MUST terminate with a sentinel entry with TransactionEntry.srcID set to 0x00000001.
     */
    std::vector<TransactionEntry*> sizeTable;

    FileChunkReference64x32 nextFragment;
public:
  TransactionLogFragment(quint64 size);



  friend QDataStream &operator<<(QDataStream &ds, const TransactionEntry &obj);
  friend QDataStream &operator>>(QDataStream &ds, TransactionEntry &obj);

  friend QDebug operator<<(QDebug dbg, const TransactionEntry &obj);

  std::vector<TransactionEntry*> getSizeTable() const;
  void setSizeTable(const std::vector<TransactionEntry*>& value);

  FileChunkReference64x32 getNextFragment() const;
  void setNextFragment(const FileChunkReference64x32& value);

private:
  void serialize(QDataStream &ds) const;
  void deserialize(QDataStream &ds);

  void toDebugString(QDebug dbg) const;
};

#endif // TRANSACTIONLOGFRAGMENT_H
