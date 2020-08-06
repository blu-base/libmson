#ifndef GLOBALIDTABLESTARTFNDX_H
#define GLOBALIDTABLESTARTFNDX_H

#include <QtCore/qglobal.h>
#include "IFileNodeType.h"

class GlobalIdTableStartFNDX : public IFileNodeType
{
private:
      quint8 m_reserved;
public:
  GlobalIdTableStartFNDX();




  quint8 getReserved() const;
  void setReserved(const quint8& value);

  // IFileNodeType interface
private:
  void deserialize(QDataStream& ds);
  void serialize(QDataStream& ds) const;
  void toDebugString(QDebug dbg) const;

  // IFileNodeType interface
public:
  virtual void generateXml(QXmlStreamWriter& xmlWriter) const override;
};

#endif // GLOBALIDTABLESTARTFNDX_H
