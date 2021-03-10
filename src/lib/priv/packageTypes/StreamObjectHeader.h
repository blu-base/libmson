#ifndef STREAMOBJECTHEADER_H
#define STREAMOBJECTHEADER_H

#include <memory>

#include <QtCore/qglobal.h>

#include "../IStreamable.h"
#include "StreamObjectTypes.h"
#include "StreamObjectHeaderEnd.h" // keep for convenience

namespace libmson {
namespace packStore {

class StreamObjectHeaderEnd;

class StreamObjectHeader : public priv::IStreamable {
public:
  StreamObjectHeader();
  StreamObjectHeader(const StreamObjectType& type, const uint64_t& length);

  StreamObjectType getType() const;
  void setType(const StreamObjectType& type);

  uint64_t getLength() const;
  void setLength(const uint64_t& length);

  std::shared_ptr<StreamObjectHeaderEnd> getEnd() const;
  void setEnd(const std::shared_ptr<StreamObjectHeaderEnd>& end);

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

  static QString typeToString(const StreamObjectType& type);


private:
  StreamObjectType m_type;
  uint64_t m_length;

  std::shared_ptr<StreamObjectHeaderEnd> m_end;

  // IStreamable interface
private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

typedef std::shared_ptr<StreamObjectHeader> StreamObjectHeader_SPtr_t;
typedef std::weak_ptr<StreamObjectHeader> StreamObjectHeader_WPtr_t;

} // namespace packStore
} // namespace libmson

#endif // STREAMOBJECTHEADER_H
