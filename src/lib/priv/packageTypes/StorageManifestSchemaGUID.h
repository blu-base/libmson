#ifndef StorageManifestSchema_H
#define StorageManifestSchema_H


#include <QUuid>
#include <QtCore/qglobal.h>

#include "interfaces/IStreamObject.h"

namespace libmson {
namespace fsshttpb {
class StorageManifestSchemaGUID : public IStreamObject {
private:
  QUuid m_guid;

public:
  StorageManifestSchemaGUID()  = default;
  ~StorageManifestSchemaGUID() = default;


  QUuid getGuid() const;
  void setGuid(QUuid guid);

  // IStreamObject interface
protected:
  virtual quint64 strObjBody_cb() const override;
  virtual quint64 cbNextHeader() const override;

public:
  virtual StreamObjectType getType() const override;
  virtual void push_back(IStreamObject_SPtr_t& obj) override;
  virtual IStreamObj_It_t
  insert(IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj) override;

private:
  virtual void deserializeStrObj(QDataStream& ds) override;
  virtual void serializeStrObj(QDataStream& ds) const override;
};

typedef std::shared_ptr<StorageManifestSchemaGUID>
    StorageManifestSchemaGUID_SPtr_t;
typedef std::weak_ptr<StorageManifestSchemaGUID>
    StorageManifestSchemaGUID_WPtr_t;

} // namespace fsshttpb
} // namespace libmson

#endif // StorageManifestSchema_H
