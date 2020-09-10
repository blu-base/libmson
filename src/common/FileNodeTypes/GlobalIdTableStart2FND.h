#ifndef GLOBALIDTABLESTART2FND_H
#define GLOBALIDTABLESTART2FND_H

#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace MSONcommon {
class GlobalIdTableStart2FND : public IFileNodeType {
public:
  GlobalIdTableStart2FND();

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // GLOBALIDTABLESTART2FND_H
