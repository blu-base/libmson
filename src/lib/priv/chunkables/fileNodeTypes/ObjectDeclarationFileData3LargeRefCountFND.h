#ifndef OBJECTDECLARATIONFILEDATA3LARGEREFCOUNTFND_H
#define OBJECTDECLARATIONFILEDATA3LARGEREFCOUNTFND_H

#include "../../IStreamable.h"
#include "../../commonTypes/CompactID.h"
#include "../../commonTypes/StringInStorageBuffer.h"
#include "../../propertyTypes/JCID.h"
#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

class ObjectDeclarationFileData3LargeRefCountFND
    : public IFileNodeType
    , public IStreamable {
private:
  CompactID m_oid;
  JCID m_jcid;
  quint32 m_cRef;
  StringInStorageBuffer m_FileDataReference;
  StringInStorageBuffer m_Extension;

public:
  ObjectDeclarationFileData3LargeRefCountFND(
      RSChunkContainer_WPtr_t parentFileNode);
  virtual ~ObjectDeclarationFileData3LargeRefCountFND() = default;

  CompactID oid() const;
  void setOid(const CompactID& oid);

  JCID jcid() const;
  void setJcid(const JCID& jcid);

  quint32 cRef() const;
  void setCRef(const quint32& cRef);

  StringInStorageBuffer FileDataReference() const;
  void setFileDataReference(const StringInStorageBuffer& FileDataReference);

  StringInStorageBuffer Extension() const;
  void setExtension(const StringInStorageBuffer& Extension);

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTDECLARATIONFILEDATA3LARGEREFCOUNTFND_H
