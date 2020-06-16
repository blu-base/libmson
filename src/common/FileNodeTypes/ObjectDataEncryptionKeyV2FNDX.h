#ifndef OBJECTDATAENCRYPTIONKEYV2FNDX_H
#define OBJECTDATAENCRYPTIONKEYV2FNDX_H

#include <QtCore/qglobal.h>

#include "../commonTypes/FileNodeChunkReference.h"
#include "IFileNodeType.h"

class ObjectDataEncryptionKeyV2FNDX : public IFileNodeType {
public:
  ObjectDataEncryptionKeyV2FNDX(FNCR_STP_FORMAT stpFormat,
                                FNCR_CB_FORMAT cbFormat);
  ObjectDataEncryptionKeyV2FNDX(quint8 stpFormat, quint8 cbFormat);

  FileNodeChunkReference ref;

  quint64 header;
  quint64 footer;

  QByteArray EncryptionData;

  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &value);

  quint64 getHeader() const;
  void setHeader(const quint64 &value);

  quint64 getFooter() const;
  void setFooter(const quint64 &value);

  QByteArray getEncryptionData() const;
  void setEncryptionData(const QByteArray &value);

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // OBJECTDATAENCRYPTIONKEYV2FNDX_H
