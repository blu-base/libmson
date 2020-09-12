#ifndef GLOBALIDTABLEENDFNDX_H
#define GLOBALIDTABLEENDFNDX_H

#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace MSONcommon {

class GlobalIdTableEndFNDX : public IFileNodeType {
public:
  GlobalIdTableEndFNDX() = default;

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // GLOBALIDTABLEENDFNDX_H
