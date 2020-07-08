#ifndef OBJECTGROUPSTARTFND_H
#define OBJECTGROUPSTARTFND_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"
class ObjectGroupStartFND : public IFileNodeType
{
public:
  ObjectGroupStartFND();


  ExtendedGUID m_oid;

  ExtendedGUID oid() const;
  void setOid(const ExtendedGUID &oid);

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // OBJECTGROUPSTARTFND_H
