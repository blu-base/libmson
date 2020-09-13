#ifndef OBJECTGROUPENDFND_H
#define OBJECTGROUPENDFND_H

#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace MSONcommon {

class ObjectGroupEndFND : public IFileNodeType {
public:
  ObjectGroupEndFND() = default;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;
};

} // namespace MSONcommon

#endif // OBJECTGROUPENDFND_H
