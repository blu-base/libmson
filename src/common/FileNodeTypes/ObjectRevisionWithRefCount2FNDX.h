#ifndef OBJECTREVISIONWITHREFCOUNT2FNDX_H
#define OBJECTREVISIONWITHREFCOUNT2FNDX_H

#include <QtCore/qglobal.h>

#include "../commonTypes/CompactID.h"
#include "../commonTypes/FileNodeChunkReference.h"
#include "IFileNodeType.h"

class ObjectRevisionWithRefCount2FNDX : public IFileNodeType {
private:

    FileNodeChunkReference m_ref;

    CompactID m_oid;

    bool m_fHasOidReferences;
    bool m_fHasOsidReferences;

    quint32 m_cRef;


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

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;

  // IFileNodeType interface
public:
  virtual void generateXml(QXmlStreamWriter& xmlWriter) const override;
};

#endif // OBJECTREVISIONWITHREFCOUNT2FNDX_H
