#ifndef OBJECTDECLARATIONFILEDATA3REFCOUNTFND_H
#define OBJECTDECLARATIONFILEDATA3REFCOUNTFND_H

#include "../commonTypes/CompactID.h"
#include "../commonTypes/StringInStorageBuffer.h"
#include "../properties/JCID.h"

#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace MSONcommon {

class ObjectDeclarationFileData3RefCountFND : public IFileNodeType {
private:
  CompactID m_oid;
  JCID m_jcid;
  quint8 m_cRef;
  StringInStorageBuffer m_FileDataReference;
  StringInStorageBuffer m_Extension;

public:
  ObjectDeclarationFileData3RefCountFND();

  CompactID oid() const;
  void setOid(const CompactID &oid);

  JCID jcid() const;
  void setJcid(const JCID &jcid);

  quint8 cRef() const;
  void setCRef(const quint8 &cRef);

  StringInStorageBuffer FileDataReference() const;
  void setFileDataReference(const StringInStorageBuffer &FileDataReference);

  StringInStorageBuffer Extension() const;
  void setExtension(const StringInStorageBuffer &Extension);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // OBJECTDECLARATIONFILEDATA3REFCOUNTFND_H
