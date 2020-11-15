#ifndef OBJECTGROUPSTARTFND_H
#define OBJECTGROUPSTARTFND_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"
namespace libmson {
namespace priv {

class ObjectGroupStartFND
    : public IFileNodeType
    , public IStreamable {
private:
  ExtendedGUID m_oid;

public:
  ObjectGroupStartFND(FileNode_WPtr_t parentFileNode);
  virtual ~ObjectGroupStartFND() = default;

  ExtendedGUID oid() const;
  void setOid(const ExtendedGUID& oid);

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTGROUPSTARTFND_H
