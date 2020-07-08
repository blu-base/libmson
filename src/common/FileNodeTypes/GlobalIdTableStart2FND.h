#ifndef GLOBALIDTABLESTART2FND_H
#define GLOBALIDTABLESTART2FND_H

#include <QtCore/qglobal.h>
#include "IFileNodeType.h"
class GlobalIdTableStart2FND : public IFileNodeType
{
public:
  GlobalIdTableStart2FND();

  // IFileNodeType interface
private:
  void deserialize(QDataStream& ds) override;
  void serialize(QDataStream& ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // GLOBALIDTABLESTART2FND_H
