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
  ObjectDeclarationFileData3LargeRefCountFND(FileNode_SPtr_t parentFileNode);
  virtual ~ObjectDeclarationFileData3LargeRefCountFND() = default;

  CompactID getOid() const;
  void setOid(const CompactID& oid);

  JCID getJcid() const;
  void setJcid(const JCID& jcid);

  quint32 getCRef() const;
  void setCRef(const quint32& cRef);

  StringInStorageBuffer getFileDataReference() const;
  void setFileDataReference(const StringInStorageBuffer& FileDataReference);

  StringInStorageBuffer getExtension() const;
  void setExtension(const StringInStorageBuffer& Extension);

  virtual quint64 getSizeInFile() const override;
  virtual FileNodeTypeID getType() const override
  {
    return FileNodeTypeID::ObjectDeclarationFileData3LargeRefCountFND;
  };

  friend class RevisionStoreFileParser;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTDECLARATIONFILEDATA3LARGEREFCOUNTFND_H
