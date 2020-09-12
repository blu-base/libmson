#ifndef FILECHUNKREFERENCE64X32_H
#define FILECHUNKREFERENCE64X32_H

#include "IFileChunkReference.h"
#include <QtCore/qglobal.h>

namespace MSONcommon {

class FileChunkReference64x32 : public IFileChunkReference<quint64, quint32> {
public:
  FileChunkReference64x32();
  FileChunkReference64x32(const quint64 &stp, const quint32 &cb);
  FileChunkReference64x32(FCR_INITTYPE inittype);

  virtual ~FileChunkReference64x32() = default;

  bool is_fcrNil() const override;
  bool is_fcrZero() const override;
  void set_fcrNil() override;
  void set_fcrZero() override;
  quint64 stp() const override;
  void setStp(const quint64 &stp) override;
  quint32 cb() const override;
  void setCb(const quint32 &cb) override;

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // FILECHUNKREFERENCE64X32_H
