#ifndef OBJECTGROUPSTARTFND_H
#define OBJECTGROUPSTARTFND_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"

namespace MSONcommon {

class ObjectGroupStartFND : public IFileNodeType {
private:
  ExtendedGUID m_oid;

public:
  ObjectGroupStartFND();

  ExtendedGUID oid() const;
  void setOid(const ExtendedGUID &oid);


private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;
};

} // namespace MSONcommon

#endif // OBJECTGROUPSTARTFND_H
