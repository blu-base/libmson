#ifndef BINARYITEM_H
#define BINARYITEM_H

#include <QByteArray>
#include <QtCore/qglobal.h>

#include "../IStreamable.h"
#include "../commonTypes/CompactUInt64.h"

namespace libmson {
namespace packStore {

/** a ByteArray according to [MS-FSSHTTPB] section 2.2.1.3*/
class BinaryItem : public priv::IStreamable {
private:
  QByteArray m_content;

public:
  BinaryItem();

  quint64 getLength() const;
  void setLength(const quint64& length);
  QByteArray getContent() const;
  void setContent(const QByteArray& content);

  quint64 getSizeInFile() const;

  // IStreamable interface
private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};


} // namespace packStore
} // namespace libmson

#endif // BINARYITEM_H
