#ifndef OBJECTGROUPENDFND_H
#define OBJECTGROUPENDFND_H

#include <QtCore/qglobal.h>
#include "IFileNodeType.h"

class ObjectGroupEndFND : public IFileNodeType
{
public:
  ObjectGroupEndFND();

  // IFileNodeType interface
private:
  void deserialize(QDataStream& ds) override;
  void serialize(QDataStream& ds) const override;
  void toDebugString(QDebug dbg) const override;

  // IFileNodeType interface
public:
  virtual void generateXml(QXmlStreamWriter& xmlWriter) const override;
};

#endif // OBJECTGROUPENDFND_H
