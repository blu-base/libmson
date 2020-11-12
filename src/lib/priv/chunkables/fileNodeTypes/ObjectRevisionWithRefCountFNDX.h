#ifndef OBJECTREVISIONWITHREFCOUNTFNDX_H
#define OBJECTREVISIONWITHREFCOUNTFNDX_H

#include <QtCore/qglobal.h>

#include "../../commonTypes/CompactID.h"
#include "../ObjectSpaceObjectPropSet.h"

#include "IFileNodeType.h"

namespace libmson {
namespace priv {

class ObjectRevisionWithRefCountFNDX : public IFileNodeType {
private:
  RSChunkContainer_WPtr_t m_ref;
  CompactID m_oid;
  bool m_fHasOidReferences;
  bool m_fHasOsidReferences;
  quint8 m_cRef;

public:
  ObjectRevisionWithRefCountFNDX(RSChunkContainer_WPtr_t parentFileNode);
  virtual ~ObjectRevisionWithRefCountFNDX() = default;

  RSChunkContainer_WPtr_t getRef() const;
  void setRef(const RSChunkContainer_WPtr_t value);

  CompactID getOid() const;
  void setOid(const CompactID& value);

  quint8 getCRef() const;
  void setCRef(const quint8& value);

  bool getFHasOidReferences() const;
  void setFHasOidReferences(bool value);

  bool getFHasOsidReferences() const;
  void setFHasOsidReferences(bool value);

  std::shared_ptr<ObjectSpaceObjectPropSet> getPropSet() const;

  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;

  virtual quint64 getSizeInFile() const override;

private:
  //  virtual void deserialize(QDataStream& ds) override;
  //  virtual void serialize(QDataStream& ds) const override;


  static const quint64 sizeInFileBase = 5;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTREVISIONWITHREFCOUNTFNDX_H
