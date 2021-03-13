#ifndef STREAMOBJECTHEADER_H
#define STREAMOBJECTHEADER_H

#include <memory>

#include <QtCore/qglobal.h>

#include "../IStreamable.h"
#include "StreamObjectHeaderEnd.h" // keep for convenience
#include "interfaces/StreamObjectTypes.h"

namespace libmson {
namespace fsshttpb {

class StreamObjectHeader : public priv::IStreamable {
public:
  StreamObjectHeader();
  StreamObjectHeader(const StreamObjectType& type, const uint64_t& length);

  StreamObjectType getType() const;
  void setType(const StreamObjectType& type);

  uint64_t getLength() const;
  void setLength(const uint64_t& length);

  StreamObjectHeaderEnd getEnd() const;

  quint64 getSizeInFile() const;

  /** computes size a StreamObjectHeader would have with the given parameters
   * length, and type.
   * @var length specifies the sizeInFile the StreamObjectHeader would
   * reference.
   * @var type specifies the type of data the StreamObjectHeader would
   * reference.
   */
  static quint64
  getSizeInFile(const quint64& length, const StreamObjectType& type);

private:
  StreamObjectType m_type;
  uint64_t m_length;

  // IStreamable interface
private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

} // namespace fsshttpb
} // namespace libmson

#endif // STREAMOBJECTHEADER_H
