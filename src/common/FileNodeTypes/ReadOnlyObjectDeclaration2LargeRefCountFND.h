#ifndef READONLYOBJECTDECLARATION2LARGEREFCOUNTFND_H
#define READONLYOBJECTDECLARATION2LARGEREFCOUNTFND_H

#include "../commonTypes/FileNodeChunkReference.h"
#include "IFileNodeType.h"
#include "ObjectDeclaration2LargeRefCountFND.h"
#include <QtCore/qglobal.h>

class ReadOnlyObjectDeclaration2LargeRefCountFND : public IFileNodeType {
private:
  FNCR_STP_FORMAT m_stpFormat;
  FNCR_CB_FORMAT m_cbFormat;

  ObjectDeclaration2LargeRefCountFND m_base;

  QByteArray m_md5hash;

public:
  ReadOnlyObjectDeclaration2LargeRefCountFND(FNCR_STP_FORMAT stpFormat,
                                             FNCR_CB_FORMAT cbFormat);

  ReadOnlyObjectDeclaration2LargeRefCountFND(quint8 stpFormat, quint8 cbFormat);
  ~ReadOnlyObjectDeclaration2LargeRefCountFND();

  FileNodeChunkReference ref() const;
  void setRef(const FileNodeChunkReference &ref);

  ObjectDeclaration2LargeRefCountFND getBase() const;
  void setBase(const ObjectDeclaration2LargeRefCountFND &value);

  QByteArray getMd5hash() const;
  void setMd5hash(const QByteArray &value);

  FNCR_STP_FORMAT getStpFormat() const;

  FNCR_CB_FORMAT getCbFormat() const;

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // READONLYOBJECTDECLARATION2LARGEREFCOUNTFND_H
