#ifndef OBJECTDECLARATIONFILEDATA3REFCOUNTFND_H
#define OBJECTDECLARATIONFILEDATA3REFCOUNTFND_H

#include "../../IStreamable.h"
#include "../../commonTypes/CompactID.h"
#include "../../commonTypes/StringInStorageBuffer.h"
#include "../../propertyTypes/JCID.h"
#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

class ObjectDeclarationFileData3RefCountFND
    : public IFileNodeType
    , public IStreamable {
private:
  CompactID m_oid;
  JCID m_jcid;
  quint8 m_cRef;
  StringInStorageBuffer m_FileDataReference;
  StringInStorageBuffer m_Extension;

public:
  ObjectDeclarationFileData3RefCountFND(FileNode_SPtr_t parentFileNode);
  virtual ~ObjectDeclarationFileData3RefCountFND() = default;

  CompactID getOid() const;
  void setOid(const CompactID& oid);

  JCID getJcid() const;
  void setJcid(const JCID& jcid);

  quint8 getCRef() const;
  void setCRef(const quint8& cRef);

  StringInStorageBuffer getFileDataReference() const;
  void setFileDataReference(const StringInStorageBuffer& FileDataReference);

  StringInStorageBuffer getExtension() const;
  void setExtension(const StringInStorageBuffer& Extension);

  virtual quint64 getSizeInFile() const override;
  virtual FileNodeTypeID getType() const override
  {
    return FileNodeTypeID::ObjectDeclarationFileData3RefCountFND;
  };

  friend class RevisionStoreFileParser;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTDECLARATIONFILEDATA3REFCOUNTFND_H
