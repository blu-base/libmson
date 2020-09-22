#ifndef READONLYOBJECTDECLARATION2REFCOUNTFND_H
#define READONLYOBJECTDECLARATION2REFCOUNTFND_H

#include "IFileNodeType.h"
#include "ObjectDeclaration2RefCountFND.h"
#include <QtCore/qglobal.h>

namespace MSONcommon {

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
  virtual ~ReadOnlyObjectDeclaration2RefCountFND() = default;

  FileNodeChunkReference ref() const;
  void setRef(const FileNodeChunkReference &ref);
  ObjectDeclaration2RefCountFND getBase() const;
  void setBase(const ObjectDeclaration2RefCountFND &value);

  QByteArray getMd5hash() const;
  void setMd5hash(const QByteArray &value);

  FNCR_CB_FORMAT getCbFormat() const;

  FNCR_STP_FORMAT getStpFormat() const;

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;

  static const quint64 md5HashSize = 16;
};

} // namespace MSONcommon

#endif // READONLYOBJECTDECLARATION2REFCOUNTFND_H
