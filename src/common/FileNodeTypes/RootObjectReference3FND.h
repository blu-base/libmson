#ifndef ROOTOBJECTREFERENCE3FND_H
#define ROOTOBJECTREFERENCE3FND_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"

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
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;

  // IFileNodeType interface
public:
  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;
};

#endif // ROOTOBJECTREFERENCE3FND_H
