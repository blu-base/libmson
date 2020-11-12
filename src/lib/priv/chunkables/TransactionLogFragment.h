#ifndef TRANSACTIONLOGFRAGMENT_H
#define TRANSACTIONLOGFRAGMENT_H

#include <QtCore/qglobal.h>
#include <vector>

#include "../IStreamable.h"
#include "RevisionStoreChunkContainer.h"

namespace libmson {
namespace priv {

class TransactionEntry;

class TransactionLogFragment : public Chunkable {
private:
  /**
   * @brief An array of TransactionEntry structures.
   * @var sizeTable
   *
   * A transaction MUST add all of its entries to the array sequentially
   * and MUST terminate with a sentinel entry with TransactionEntry.srcID set to
   * 0x00000001.
   */
  std::vector<std::shared_ptr<TransactionEntry>> sizeTable;

  RSChunkContainer_WPtr_t nextFragment;

public:
  TransactionLogFragment();
  virtual ~TransactionLogFragment() = default;

  std::vector<std::shared_ptr<TransactionEntry>> getSizeTable() const;
  void
  setSizeTable(const std::vector<std::shared_ptr<TransactionEntry>>& value);

  RSChunkContainer_WPtr_t getNextFragment() const;
  void setNextFragment(const RSChunkContainer_WPtr_t value);

  quint64 getSizeInFile() const;

  friend class RevisionStoreFileWriter;
  friend class RevisionStoreFileParser;


  // Chunkable interface
  virtual quint64 cb() const override;
  virtual RevisionStoreChunkType getType() const override;
};

class TransactionEntry : public IStreamable {
private:
  quint32 srcID;

  quint32 TransactionEntrySwitch;

public:
  TransactionEntry();

  quint32 getSrcID() const;
  void setSrcID(const quint32& value);
  quint32 getTransactionEntrySwitch() const;
  void setTransactionEntrySwitch(const quint32& value);

  bool isZero() const;

  static quint64 getSizeInFile() { return sizeInFile; }

private:
  virtual void serialize(QDataStream& ds) const override;
  virtual void deserialize(QDataStream& ds) override;

  static const quint64 sizeInFile = 8;
};

} // namespace priv
} // namespace libmson

#endif // TRANSACTIONLOGFRAGMENT_H
