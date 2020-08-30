#ifndef GLOBALIDTABLEENDFNDX_H
#define GLOBALIDTABLEENDFNDX_H

#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

class GlobalIdTableEndFNDX : public IFileNodeType {
public:
  GlobalIdTableEndFNDX();

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // GLOBALIDTABLEENDFNDX_H
