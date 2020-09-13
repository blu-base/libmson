#ifndef ROOTOBJECTREFERENCE3FND_H
#define ROOTOBJECTREFERENCE3FND_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"

namespace MSONcommon {

class RootObjectReference3FND : public IFileNodeType {
private:
  ExtendedGUID m_oidRoot;
  quint32 m_RootRole;

public:
  RootObjectReference3FND();

  // IFileNodeType interface
  ExtendedGUID getOidRoot() const;
  void setOidRoot(const ExtendedGUID &value);

  quint32 getRootRole() const;
  void setRootRole(const quint32 &value);

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;
};

} // namespace MSONcommon

#endif // ROOTOBJECTREFERENCE3FND_H
