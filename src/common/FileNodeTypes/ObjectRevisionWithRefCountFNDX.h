#ifndef OBJECTREVISIONWITHREFCOUNTFNDX_H
#define OBJECTREVISIONWITHREFCOUNTFNDX_H

#include <QtCore/qglobal.h>

#include "../commonTypes/CompactID.h"
#include "../commonTypes/FileNodeChunkReference.h"
#include "../otherTypes/ObjectSpaceObjectPropSet.h"
#include "IFileNodeType.h"

class ObjectRevisionWithRefCountFNDX : public IFileNodeType {
private:
    FileNodeChunkReference m_ref;

    CompactID m_oid;


    bool m_fHasOidReferences;
    bool m_fHasOsidReferences;

    quint8 m_cRef;

    ObjectSpaceObjectPropSet m_blob;
public:
  ObjectRevisionWithRefCountFNDX(FNCR_STP_FORMAT stpFormat,
                                 FNCR_CB_FORMAT cbFormat);
  ObjectRevisionWithRefCountFNDX(quint8 stpFormat, quint8 cbFormat);
  ~ObjectRevisionWithRefCountFNDX();



  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &value);
  CompactID getOid() const;
  void setOid(const CompactID &value);
  quint8 getCRef() const;
  void setCRef(const quint8 &value);
  bool getFHasOidReferences() const;
  void setFHasOidReferences(bool value);
  bool getFHasOsidReferences() const;
  void setFHasOsidReferences(bool value);

  ObjectSpaceObjectPropSet getPropSet() const;
  void setPropSet(const ObjectSpaceObjectPropSet &value);

  // IFileNodeType interface
private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;

  // IFileNodeType interface
public:
  virtual void generateXml(QXmlStreamWriter& xmlWriter) const override;
};

#endif // OBJECTREVISIONWITHREFCOUNTFNDX_H
