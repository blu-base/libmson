#ifndef FILECHUNKREFERENCE64_H
#define FILECHUNKREFERENCE64_H

#include <QtCore/qglobal.h>

#include "IFileChunkReference.h"


namespace libmson {
namespace priv {

class FileChunkReference64 : public IFileChunkReference<quint64, quint64> {
private:
  static const quint64 sizeInFile = 16;

public:
  FileChunkReference64() = default;
  FileChunkReference64(const quint64 &stp, const quint64 &cb);
  FileChunkReference64(FCR_INIT inittype);

  virtual ~FileChunkReference64() = default;

  bool is_fcrNil() const override;
  bool is_fcrZero() const override;
  void set_fcrNil() override;
  void set_fcrZero() override;
  quint64 stp() const override;
  void setStp(const quint64 &stp) override;
  quint64 cb() const override;
  void setCb(const quint64 &cb) override;

  static quint64 getSizeInFile();

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

};

} // namespace priv
} // namespace libmson

#endif // FILECHUNKREFERENCE64_H
