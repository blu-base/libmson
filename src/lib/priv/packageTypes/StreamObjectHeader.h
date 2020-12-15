#ifndef STREAMOBJECTHEADER_H
#define STREAMOBJECTHEADER_H

#include <memory>

#include <QtCore/qglobal.h>

#include "../IStreamable.h"
#include "StreamObjectHeaderEnd.h"
#include "StreamObjectTypes.h"

namespace libmson {
namespace packStore {

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
