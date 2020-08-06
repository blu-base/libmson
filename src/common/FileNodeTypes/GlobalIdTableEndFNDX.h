#ifndef GLOBALIDTABLEENDFNDX_H
#define GLOBALIDTABLEENDFNDX_H

#include <QtCore/qglobal.h>
#include "IFileNodeType.h"
class GlobalIdTableEndFNDX : public IFileNodeType
{
public:
  GlobalIdTableEndFNDX();

  // IFileNodeType interface
private:
  void deserialize(QDataStream& ds) override;
  void serialize(QDataStream& ds) const override;
  void toDebugString(QDebug dbg) const override;

  // IFileNodeType interface
public:
  virtual void generateXml(QXmlStreamWriter& xmlWriter) const override;
};

#endif // GLOBALIDTABLEENDFNDX_H
