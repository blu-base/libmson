#ifndef ROOTOBJECTREFERENCE2FNDX_H
#define ROOTOBJECTREFERENCE2FNDX_H

#include <QtCore/qglobal.h>

#include "../commonTypes/CompactID.h"
#include "IFileNodeType.h"

class RootObjectReference2FNDX : public IFileNodeType {
public:
  RootObjectReference2FNDX();

  CompactID oidRoot;
  quint32 RootRole;

  CompactID getOidRoot() const;
  void setOidRoot(const CompactID &value);

  quint32 getRootRole() const;
  void setRootRole(const quint32 &value);

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // ROOTOBJECTREFERENCE2FNDX_H
