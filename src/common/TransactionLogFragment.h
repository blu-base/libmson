#ifndef TRANSACTIONLOGFRAGMENT_H
#define TRANSACTIONLOGFRAGMENT_H

#include <QtCore/qglobal.h>
#include <vector>

#include <QDataStream>
#include <QDebug>
#include <QXmlStreamWriter>

#include "IRevisionStoreFileObject.h"
#include "TransactionEntry.h"
#include "commonTypes/FileChunkReference64x32.h"

namespace MSONcommon {
class TransactionLogFragment : public IRevisionStoreFileObject {
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
  std::vector<std::shared_ptr<TransactionEntry>> sizeTable;

  FileChunkReference64x32 nextFragment;

public:
  TransactionLogFragment(quint64 size);
  ~TransactionLogFragment() = default;

  std::vector<std::shared_ptr<TransactionEntry>> getSizeTable() const;
  void
  setSizeTable(const std::vector<std::shared_ptr<TransactionEntry>> &value);

  FileChunkReference64x32 getNextFragment() const;
  void setNextFragment(const FileChunkReference64x32 &value);

  quint64 getSizeInFile() const;

private:
  virtual void serialize(QDataStream &ds) const override;
  virtual void deserialize(QDataStream &ds) override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;
};

} // namespace MSONcommon

#endif // TRANSACTIONLOGFRAGMENT_H
