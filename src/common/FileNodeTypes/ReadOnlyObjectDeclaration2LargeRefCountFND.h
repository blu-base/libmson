#ifndef READONLYOBJECTDECLARATION2LARGEREFCOUNTFND_H
#define READONLYOBJECTDECLARATION2LARGEREFCOUNTFND_H

#include "../commonTypes/FileNodeChunkReference.h"
#include "IFileNodeType.h"
#include "ObjectDeclaration2LargeRefCountFND.h"
#include <QtCore/qglobal.h>

namespace MSONcommon {

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
  virtual ~ReadOnlyObjectDeclaration2LargeRefCountFND() = default;

  FileNodeChunkReference ref() const;
  void setRef(const FileNodeChunkReference &ref);

  ObjectDeclaration2LargeRefCountFND getBase() const;
  void setBase(const ObjectDeclaration2LargeRefCountFND &value);

  QByteArray getMd5hash() const;
  void setMd5hash(const QByteArray &value);

  FNCR_STP_FORMAT getStpFormat() const;

  FNCR_CB_FORMAT getCbFormat() const;

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;

  static const quint64 md5HashSize = 16;
};

} // namespace MSONcommon

#endif // READONLYOBJECTDECLARATION2LARGEREFCOUNTFND_H
