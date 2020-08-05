#ifndef OBJECTDECLARATIONFILEDATA3LARGEREFCOUNTFND_H
#define OBJECTDECLARATIONFILEDATA3LARGEREFCOUNTFND_H

#include "../commonTypes/CompactID.h"
#include "../commonTypes/StringInStorageBuffer.h"
#include "../properties/JCID.h"
#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

class ObjectDeclarationFileData3LargeRefCountFND : public IFileNodeType {
private:
  CompactID m_oid;
  JCID m_jcid;

  quint32 m_cRef;

  StringInStorageBuffer m_FileDataReference;
  StringInStorageBuffer m_Extension;

public:
  ObjectDeclarationFileData3LargeRefCountFND();

  CompactID oid() const;
  void setOid(const CompactID &oid);

  JCID jcid() const;
  void setJcid(const JCID &jcid);

  quint32 cRef() const;
  void setCRef(const quint32 &cRef);

  StringInStorageBuffer FileDataReference() const;
  void setFileDataReference(const StringInStorageBuffer &FileDataReference);

  StringInStorageBuffer Extension() const;
  void setExtension(const StringInStorageBuffer &Extension);

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // OBJECTDECLARATIONFILEDATA3LARGEREFCOUNTFND_H