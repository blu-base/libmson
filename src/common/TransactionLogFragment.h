#ifndef TRANSACTIONLOGFRAGMENT_H
#define TRANSACTIONLOGFRAGMENT_H

#include <QtCore/qglobal.h>
#include <vector>

#include <QDataStream>
#include <QDebug>
#include <QXmlStreamWriter>

#include "IDeserializable.h"
#include "ISerializable.h"
#include "TransactionEntry.h"
#include "commonTypes/FileChunkReference64x32.h"

namespace MSONcommon {
class TransactionLogFragment : public ISerializable, public IDeserializable {
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

  friend QDebug operator<<(QDebug dbg, const TransactionLogFragment &obj);

  std::vector<std::shared_ptr<TransactionEntry>> getSizeTable() const;
  void
  setSizeTable(const std::vector<std::shared_ptr<TransactionEntry>> &value);

  FileChunkReference64x32 getNextFragment() const;
  void setNextFragment(const FileChunkReference64x32 &value);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

private:
  virtual void serialize(QDataStream &ds) const override;
  virtual void deserialize(QDataStream &ds) override;

  void toDebugString(QDebug dbg) const;
};

} // namespace MSONcommon

#endif // TRANSACTIONLOGFRAGMENT_H
