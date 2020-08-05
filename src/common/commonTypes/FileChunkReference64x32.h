#ifndef FILECHUNKREFERENCE64X32_H
#define FILECHUNKREFERENCE64X32_H

#include <QtCore/qglobal.h>
#include "IFileChunkReference.h"

class FileChunkReference64x32 : public IFileChunkReference<quint64,quint32>
{
public:
  FileChunkReference64x32();

  FileChunkReference64x32(FCR_INITTYPE inittype);
  virtual ~FileChunkReference64x32();

  // IFileChunkReference interface
  bool is_fcrNil() const override;
  bool is_fcrZero() const override;
  void set_fcrNil() override;
  void set_fcrZero() override;
  quint64 stp() const override;
  void setStp(const quint64& stp) override;
  quint32 cb() const override;
  void setCb(const quint32& cb) override;

  void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream& ds) override;
  void serialize(QDataStream& ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // FILECHUNKREFERENCE64X32_H