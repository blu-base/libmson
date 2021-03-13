#ifndef REVISIONMANIFESTROOTDECLARE_H
#define REVISIONMANIFESTROOTDECLARE_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "interfaces/IStreamObject.h"

namespace libmson {
namespace fsshttpb {


class RevisionManifestRootDeclare : public IStreamObject {
private:
  priv::ExtendedGUID m_root;
  priv::ExtendedGUID m_object;

  // indicates whether the member variables are optional (not used)s
  bool m_set = false;

public:
  RevisionManifestRootDeclare();

  priv::ExtendedGUID getRootGUID() const;
  void setRootGUID(const priv::ExtendedGUID& root);
  priv::ExtendedGUID getObjectGUID() const;
  void setObjectGUID(const priv::ExtendedGUID& object);

  bool isSet() const { return m_set; };
  void set(bool isSet) { m_set = isSet; };

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

typedef std::shared_ptr<RevisionManifestRootDeclare>
    RevisionManifestRootDeclare_SPtr_t;
typedef std::weak_ptr<RevisionManifestRootDeclare>
    RevisionManifestRootDeclare_WPtr_t;


} // namespace fsshttpb
} // namespace libmson
#endif // REVISIONMANIFESTROOTDECLARE_H
