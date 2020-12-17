#ifndef REVISIONMANIFESTDATAELEMENT_H
#define REVISIONMANIFESTDATAELEMENT_H


#include <QtCore/qglobal.h>

#include "../commonTypes/CompactExtGuid.h"
#include "DataElement.h"
#include "DataElementBody.h"
#include "streamObjects/RevisionManifest.h"
#include "streamObjects/RevisionManifestObjectGroupReference.h"
#include "streamObjects/RevisionManifestRootDeclare.h"

namespace libmson {
namespace packStore {

class RevisionManifest
    : public DataElementBody
    , public priv::IStreamable {
private:
  streamObj::RevisionManifest_SPtr_t m_revisionManifest;

  std::vector<streamObj::RevisionManifestRootDeclare_SPtr_t> m_rootDeclares;
  std::vector<streamObj::RevisionManifestObjectGroupReference_SPtr_t>
      m_objectGroups;

public:
  RevisionManifest();

  streamObj::RevisionManifest_SPtr_t getRevisionManifest() const;
  void setRevisionManifest(
      const streamObj::RevisionManifest_SPtr_t& revisionManifest);


  std::vector<streamObj::RevisionManifestRootDeclare_SPtr_t>
  getRootDeclares() const;
  void setRootDeclares(
      const std::vector<streamObj::RevisionManifestRootDeclare_SPtr_t>&
          rootDeclares);
  std::vector<streamObj::RevisionManifestObjectGroupReference_SPtr_t>
  getObjectGroups() const;
  void setObjectGroups(
      const std::vector<streamObj::RevisionManifestObjectGroupReference_SPtr_t>&
          objectGroups);

  // IStreamable interface
private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;

  // DataElementBody interface
protected:
  virtual quint64 cb() const override;

public:
  virtual DataElementType getType() const override;
};


typedef std::weak_ptr<RevisionManifest> RevisionManifest_WPtr_t;
typedef std::shared_ptr<RevisionManifest> RevisionManifest_SPtr_t;

} // namespace packStore
} // namespace libmson
#endif // REVISIONMANIFESTDATAELEMENT_H
