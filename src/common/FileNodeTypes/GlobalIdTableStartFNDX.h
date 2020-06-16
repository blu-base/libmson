#ifndef GLOBALIDTABLESTARTFNDX_H
#define GLOBALIDTABLESTARTFNDX_H

#include <QtCore/qglobal.h>
#include "IFileNodeType.h"

class GlobalIdTableStartFNDX : public IFileNodeType
{
public:
  GlobalIdTableStartFNDX();


  quint8 reserved;

  quint8 getReserved() const;
  void setReserved(const quint8& value);

  // IFileNodeType interface
private:
  void deserialize(QDataStream& ds);
  void serialize(QDataStream& ds) const;
  void toDebugString(QDebug dbg) const;
};

#endif // GLOBALIDTABLESTARTFNDX_H
