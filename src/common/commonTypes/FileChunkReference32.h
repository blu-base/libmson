#ifndef FILECHUNKREFERENCE32_H
#define FILECHUNKREFERENCE32_H

#include <QtCore/qglobal.h>

#include "IFileChunkReference.h"

namespace MSONcommon {

class FileChunkReference32 : public IFileChunkReference<quint32, quint32> {
public:
  FileChunkReference32() = default;
  FileChunkReference32(FCR_INITTYPE inittype);

  virtual ~FileChunkReference32() = default;

  bool is_fcrNil() const override;
  bool is_fcrZero() const override;
  void set_fcrNil() override;
  void set_fcrZero() override;
  quint32 stp() const override;
  void setStp(const quint32 &stp) override;
  quint32 cb() const override;
  void setCb(const quint32 &cb) override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // FILECHUNKREFERENCE32_H
