#ifndef OBJECTGROUPENDFND_H
#define OBJECTGROUPENDFND_H

#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace MSONcommon {

class ObjectGroupEndFND : public IFileNodeType {
public:
  ObjectGroupEndFND();

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // OBJECTGROUPENDFND_H
