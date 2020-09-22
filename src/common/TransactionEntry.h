#ifndef TRANSACTIONENTRY_H
#define TRANSACTIONENTRY_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDebug>
#include <QXmlStreamWriter>

#include "IRevisionStoreFileObject.h"

namespace MSONcommon {

class TransactionEntry : public IRevisionStoreFileObject {
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

  static quint64 getSizeInFile() { return sizeInFile; }

private:
  virtual void serialize(QDataStream &ds) const override;
  virtual void deserialize(QDataStream &ds) override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;

  static const quint64 sizeInFile = 8;
};

} // namespace MSONcommon

#endif // TRANSACTIONENTRY_H
