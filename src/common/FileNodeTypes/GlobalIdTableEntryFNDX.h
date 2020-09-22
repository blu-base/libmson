#ifndef GLOBALIDTABLEENTRYFNDX_H
#define GLOBALIDTABLEENTRYFNDX_H

#include <QtCore/qglobal.h>

#include <QUuid>

#include "IFileNodeType.h"

namespace MSONcommon {

class GlobalIdTableEntryFNDX : public IFileNodeType {
private:
  quint32 m_index;
  QUuid m_guid;

public:
  GlobalIdTableEntryFNDX();

  quint32 getIndex() const;
  void setIndex(const quint32 &value);

  QUuid getGuid() const;
  void setGuid(const QUuid &value);

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;

  static const quint64 sizeInFile = 20;
};

} // namespace MSONcommon

#endif // GLOBALIDTABLEENTRYFNDX_H
