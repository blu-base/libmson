#ifndef ROOTOBJECTREFERENCE2FNDX_H
#define ROOTOBJECTREFERENCE2FNDX_H

#include <QtCore/qglobal.h>

#include "../commonTypes/CompactID.h"
#include "IFileNodeType.h"

class RootObjectReference2FNDX : public IFileNodeType {
private:
  CompactID m_oidRoot;
  quint32 m_RootRole;

public:
  RootObjectReference2FNDX();

  CompactID getOidRoot() const;
  void setOidRoot(const CompactID &value);

  quint32 getRootRole() const;
  void setRootRole(const quint32 &value);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // ROOTOBJECTREFERENCE2FNDX_H
