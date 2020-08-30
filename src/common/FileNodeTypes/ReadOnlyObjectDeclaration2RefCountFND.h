#ifndef READONLYOBJECTDECLARATION2REFCOUNTFND_H
#define READONLYOBJECTDECLARATION2REFCOUNTFND_H

#include "IFileNodeType.h"
#include "ObjectDeclaration2RefCountFND.h"
#include <QtCore/qglobal.h>

class ReadOnlyObjectDeclaration2RefCountFND : public IFileNodeType {
private:
  FNCR_STP_FORMAT m_stpFormat;
  FNCR_CB_FORMAT m_cbFormat;
  ObjectDeclaration2RefCountFND m_base;

  QByteArray m_md5hash;

public:
  ReadOnlyObjectDeclaration2RefCountFND(FNCR_STP_FORMAT stpFormat,
                                        FNCR_CB_FORMAT cbFormat);

  ReadOnlyObjectDeclaration2RefCountFND(quint8 stpFormat, quint8 cbFormat);
  ~ReadOnlyObjectDeclaration2RefCountFND();

  FileNodeChunkReference ref() const;
  void setRef(const FileNodeChunkReference &ref);
  ObjectDeclaration2RefCountFND getBase() const;
  void setBase(const ObjectDeclaration2RefCountFND &value);

  QByteArray getMd5hash() const;
  void setMd5hash(const QByteArray &value);

  FNCR_CB_FORMAT getCbFormat() const;

  FNCR_STP_FORMAT getStpFormat() const;

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // READONLYOBJECTDECLARATION2REFCOUNTFND_H
