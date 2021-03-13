#ifndef STREAMOBJECTHEADEREND_H
#define STREAMOBJECTHEADEREND_H

#include <memory>

#include <QtCore/qglobal.h>


#include "../IStreamable.h"
#include "interfaces/StreamObjectTypes.h"

namespace libmson {
namespace fsshttpb {

class StreamObjectHeaderEnd : public priv::IStreamable {
private:
  StreamObjectType m_type;


public:
  StreamObjectHeaderEnd();
  StreamObjectHeaderEnd(StreamObjectType type);
  StreamObjectType getType() const;

  quint64 getSizeInFile() const;
  static quint64 getSizeInFile(StreamObjectType type);

  friend class IStreamObject;
  friend class StreamObjectHeader;
  friend class PackageStoreFileParser;

  // IStreamable interface
private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};


} // namespace fsshttpb
} // namespace libmson

#endif // STREAMOBJECTHEADEREND_H
