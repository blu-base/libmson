#ifndef GLOBALIDTABLEENTRYFNDX_H
#define GLOBALIDTABLEENTRYFNDX_H

#include <QtCore/qglobal.h>

#include "IFileNodeType.h"
#include "../commonTypes/ExtendedGUID.h"


class GlobalIdTableEntryFNDX : public IFileNodeType
{
public:
  GlobalIdTableEntryFNDX();

  quint32 index;

  ExtendedGUID guid;

  quint32 getIndex() const;
  void setIndex(const quint32& value);

  ExtendedGUID getGuid() const;
  void setGuid(const ExtendedGUID& value);

private:
  // IFileNodeType interface
  void deserialize(QDataStream& ds) override;
  void serialize(QDataStream& ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // GLOBALIDTABLEENTRYFNDX_H
