#ifndef TRANSACTIONLOGFRAGMENT_H
#define TRANSACTIONLOGFRAGMENT_H

#include <QtCore/qglobal.h>
#include <vector>

#include "../IStreamable.h"
#include "Chunkable.h"

namespace libmson {
namespace priv {

class TransactionLogFragment;
typedef std::shared_ptr<TransactionLogFragment> TransactionLogFragment_SPtr_t;
typedef std::weak_ptr<TransactionLogFragment> TransactionLogFragment_WPtr_t;

typedef std::shared_ptr<class TransactionEntry> TransactionEntry_SPtr_t;
typedef std::weak_ptr<class TransactionEntry> TransactionEntry_WPtr_t;

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
  std::vector<TransactionEntry_SPtr_t> m_sizeTable;

  TransactionLogFragment_WPtr_t m_nextFragment;

public:
  TransactionLogFragment(
      const quint64 initialStp = 0, const quint64 initialCb = 0);
  virtual ~TransactionLogFragment() = default;

  std::vector<TransactionEntry_SPtr_t> getSizeTable() const;
  void setSizeTable(const std::vector<TransactionEntry_SPtr_t>& value);

  TransactionLogFragment_WPtr_t getNextFragment() const;
  void setNextFragment(const TransactionLogFragment_WPtr_t value);


  quint8 getPaddingLength() const { return paddingLength; };

  friend class RevisionStoreFileParser;


private:
  virtual quint64 cb() const override;
  virtual RevisionStoreChunkType getType() const override;

  static const quint8 paddingLength = 4;
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
