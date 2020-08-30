#ifndef OBJECTGROUPSTARTFND_H
#define OBJECTGROUPSTARTFND_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"

class ObjectGroupStartFND : public IFileNodeType {
private:
  ExtendedGUID m_oid;

public:
  ObjectGroupStartFND();

  ExtendedGUID oid() const;
  void setOid(const ExtendedGUID &oid);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // OBJECTGROUPSTARTFND_H
