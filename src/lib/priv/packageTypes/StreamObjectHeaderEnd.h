#ifndef STREAMOBJECTHEADEREND_H
#define STREAMOBJECTHEADEREND_H

#include <memory>

#include <QtCore/qglobal.h>


#include "../IStreamable.h"
#include "StreamObjectTypes.h"

namespace libmson {
namespace packStore {

class StreamObjectHeader;

class StreamObjectHeaderEnd : public priv::IStreamable {
private:
  std::weak_ptr<StreamObjectHeader> m_parent;

public:
  StreamObjectHeaderEnd(const std::shared_ptr<StreamObjectHeader>& parent);

  quint64 getSizeInFile() const;
  static quint64 getSizeInFile(const StreamObjectType& type);
  // IStreamable interface
private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

typedef std::shared_ptr<StreamObjectHeaderEnd> StreamObjectHeaderEnd_SPtr_t;
typedef std::weak_ptr<StreamObjectHeaderEnd> StreamObjectHeaderEnd_WPtr_t;

} // namespace packStore
} // namespace libmson

#endif // STREAMOBJECTHEADEREND_H
