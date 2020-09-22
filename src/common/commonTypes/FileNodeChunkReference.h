#ifndef FILENODECHUNKREFERENCE_H
#define FILENODECHUNKREFERENCE_H

#include <QDataStream>
#include <QDebug>
#include <QtCore/qglobal.h>

#include "IFileChunkReference.h"

namespace MSONcommon {

enum class FNCR_STP_FORMAT {
  UNCOMPRESED_8BYTE = 0,
  UNCOMPRESED_4BYTE = 1,
  COMPRESSED_2BYTE = 2,
  COMPRESSED_4BYTE = 3,
};

enum class FNCR_CB_FORMAT {
  UNCOMPRESED_8BYTE = 1,
  UNCOMPRESED_4BYTE = 0,
  COMPRESSED_1BYTE = 2,
  COMPRESSED_2BYTE = 3,
};

class FileNodeChunkReference : public IFileChunkReference<quint64, quint64> {

public:
  FileNodeChunkReference(FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat);
  FileNodeChunkReference(quint8 stpFormat, quint8 cbFormat);

  virtual ~FileNodeChunkReference() = default;

  bool is_fcrNil() const override;
  bool is_fcrZero() const override;
  void set_fcrNil() override;
  void set_fcrZero() override;
  quint64 stp() const override;
  void setStp(const quint64 &stp) override;
  quint64 cb() const override;
  void setCb(const quint64 &cb) override;

  bool isSTPcompressed();
  bool isCBcompressed();

  quint64 getSizeInFile() const;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;

  FNCR_STP_FORMAT m_stpFormat;
  FNCR_CB_FORMAT m_cbFormat;
};

} // namespace MSONcommon

#endif // FILENODECHUNKREFERENCE_H
