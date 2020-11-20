#ifndef FILECHUNKREFERENCE32_H
#define FILECHUNKREFERENCE32_H

#include <QtCore/qglobal.h>

#include "IFileChunkReference.h"

namespace libmson {
namespace priv {

class FileChunkReference32 : public IFileChunkReference<quint32, quint32> {
private:
  static const quint64 sizeInFile = 8;

public:
  FileChunkReference32() = default;
  FileChunkReference32(FCR_INIT inittype);

  virtual ~FileChunkReference32() = default;

  bool is_fcrNil() const override;
  bool is_fcrZero() const override;
  void set_fcrNil() override;
  void set_fcrZero() override;
  quint32 stp() const override;
  void setStp(const quint32 &stp) override;
  quint32 cb() const override;
  void setCb(const quint32 &cb) override;

  static constexpr quint64 getSizeInFile() { return sizeInFile; };

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;
};

} // namespace priv
} // namespace libmson

#endif // FILECHUNKREFERENCE32_H
