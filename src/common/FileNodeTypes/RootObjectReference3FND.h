#ifndef ROOTOBJECTREFERENCE3FND_H
#define ROOTOBJECTREFERENCE3FND_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"

class RootObjectReference3FND : public IFileNodeType {
public:
  RootObjectReference3FND();

  ExtendedGUID oidRoot;
  quint32 RootRole;

  // IFileNodeType interface
  ExtendedGUID getOidRoot() const;
  void setOidRoot(const ExtendedGUID &value);

  quint32 getRootRole() const;
  void setRootRole(const quint32 &value);

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // ROOTOBJECTREFERENCE3FND_H
