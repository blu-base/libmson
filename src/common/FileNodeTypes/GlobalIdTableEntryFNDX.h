#ifndef GLOBALIDTABLEENTRYFNDX_H
#define GLOBALIDTABLEENTRYFNDX_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"

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

private:
  // IFileNodeType interface
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;

  // IFileNodeType interface
public:
  virtual void generateXml(QXmlStreamWriter& xmlWriter) const override;
};

#endif // GLOBALIDTABLEENTRYFNDX_H
