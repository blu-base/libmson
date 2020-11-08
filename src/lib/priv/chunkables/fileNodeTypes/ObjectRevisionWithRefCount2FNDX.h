#ifndef OBJECTREVISIONWITHREFCOUNT2FNDX_H
#define OBJECTREVISIONWITHREFCOUNT2FNDX_H

#include <QtCore/qglobal.h>

#include "../../commonTypes/CompactID.h"
#include "../../commonTypes/FileNodeChunkReference.h"
#include "../../objectTypes/ObjectSpaceObjectPropSet.h"

#include "IFileNodeType.h"

namespace libmson{
namespace priv{

class ObjectRevisionWithRefCount2FNDX : public IFileNodeType {
private:
  FileNodeChunkReference m_ref;

  CompactID m_oid;

  bool m_fHasOidReferences;
  bool m_fHasOsidReferences;

  quint32 m_cRef;

  ObjectSpaceObjectPropSet m_blob;

public:
  ObjectRevisionWithRefCount2FNDX(FNCR_STP_FORMAT stpFormat,
                                  FNCR_CB_FORMAT cbFormat);
  ObjectRevisionWithRefCount2FNDX(quint8 stpFormat, quint8 cbFormat);

  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &value);

  CompactID getOid() const;
  void setOid(const CompactID &value);

  bool getFHasOidReferences() const;
  void setFHasOidReferences(bool value);

  bool getFHasOsidReferences() const;
  void setFHasOsidReferences(bool value);

  quint32 getCRef() const;
  void setCRef(const quint32 &value);

  ObjectSpaceObjectPropSet getPropSet() const;
  void setPropSet(const ObjectSpaceObjectPropSet &value);

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;





  static const quint64 sizeInFileBase = 12;
};

} //namespace priv
} // namespace libmson

#endif // OBJECTREVISIONWITHREFCOUNT2FNDX_H
