#ifndef GLOBALIDTABLEENTRY2FNDX_H
#define GLOBALIDTABLEENTRY2FNDX_H

#include <QtCore/qglobal.h>

#include "IFileNodeType.h"

class GlobalIdTableEntry2FNDX : public IFileNodeType
{
public:
  GlobalIdTableEntry2FNDX();

  quint32 iIndexMapFrom;

  quint32 iIndexMapTo;

  quint32 getIIndexMapTo() const;
  void setIIndexMapTo(const quint32& value);

  quint32 getIIndexMapFrom() const;
  void setIIndexMapFrom(const quint32& value);

private:
  void deserialize(QDataStream& ds) override;
  void serialize(QDataStream& ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // GLOBALIDTABLEENTRY2FNDX_H
