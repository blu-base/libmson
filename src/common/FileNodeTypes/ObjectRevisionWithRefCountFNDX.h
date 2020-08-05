#ifndef OBJECTREVISIONWITHREFCOUNTFNDX_H
#define OBJECTREVISIONWITHREFCOUNTFNDX_H

#include <QtCore/qglobal.h>

#include "../commonTypes/CompactID.h"
#include "../commonTypes/FileNodeChunkReference.h"
#include "IFileNodeType.h"

class ObjectRevisionWithRefCountFNDX : public IFileNodeType {
public:
  ObjectRevisionWithRefCountFNDX(FNCR_STP_FORMAT stpFormat,
                                 FNCR_CB_FORMAT cbFormat);
  ObjectRevisionWithRefCountFNDX(quint8 stpFormat, quint8 cbFormat);
  ~ObjectRevisionWithRefCountFNDX();

  FileNodeChunkReference ref;

  CompactID oid;

  quint8 cRef;
  bool fHasOidReferences;
  bool fHasOsidReferences;

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

  // IFileNodeType interface
private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // OBJECTREVISIONWITHREFCOUNTFNDX_H