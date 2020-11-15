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
  ObjectSpaceObjectPropSet_WPtr_t m_ref;
  CompactID m_oid;
  bool m_fHasOidReferences;
  bool m_fHasOsidReferences;
  quint8 m_cRef;

public:
  ObjectRevisionWithRefCountFNDX(FileNode_WPtr_t parentFileNode);
  virtual ~ObjectRevisionWithRefCountFNDX() = default;

  ObjectSpaceObjectPropSet_WPtr_t getRef() const;
  void setRef(const ObjectSpaceObjectPropSet_WPtr_t value);

  CompactID getOid() const;
  void setOid(const CompactID& value);

  quint8 getCRef() const;
  void setCRef(const quint8& value);

  bool getFHasOidReferences() const;
  void setFHasOidReferences(bool value);

  bool getFHasOsidReferences() const;
  void setFHasOsidReferences(bool value);

  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;

  virtual quint64 getSizeInFile() const override;

private:
  static const quint64 sizeInFileBase = 5;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTREVISIONWITHREFCOUNTFNDX_H
