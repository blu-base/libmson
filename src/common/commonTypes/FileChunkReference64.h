#ifndef FILECHUNKREFERENCE64_H
#define FILECHUNKREFERENCE64_H

#include <QtCore/qglobal.h>

#include "IFileChunkReference.h"

namespace MSONcommon {

class FileChunkReference64 : public IFileChunkReference<quint64, quint64> {
public:
  FileChunkReference64() = default;
  FileChunkReference64(FCR_INITTYPE inittype);

  virtual ~FileChunkReference64() = default;

  bool is_fcrNil() const override;
  bool is_fcrZero() const override;
  void set_fcrNil() override;
  void set_fcrZero() override;
  quint64 stp() const override;
  void setStp(const quint64 &stp) override;
  quint64 cb() const override;
  void setCb(const quint64 &cb) override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // FILECHUNKREFERENCE64_H
