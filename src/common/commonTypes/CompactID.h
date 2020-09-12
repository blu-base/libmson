#ifndef COMPACTID_H
#define COMPACTID_H

#include <QtCore/qglobal.h>

#include "ExtendedGUID.h"

#include "../IDeserializable.h"
#include "../ISerializable.h"

namespace MSONcommon {

class CompactID : public ISerializable, public IDeserializable {
private:
  quint8 m_n;
  quint32 guidIndex; // 24bits used.

public:
  CompactID();
  CompactID(const quint8 m_n, const quint32 compactEGUID);
  CompactID(const QByteArray &bytes);
  virtual ~CompactID() = default;

  quint8 getN() const;
  void setN(const quint8 &value);

  quint32 getGuidIndex() const;
  bool setGuidIndex(const quint32 &value);

  //  bool isValid() const;
  bool isNull() const;

  QByteArray toByteArray() const;

  QString toString() const;

  friend QDebug operator<<(QDebug dbg, const CompactID &obj);

  friend bool operator==(const CompactID &lhs, const CompactID &rhs) noexcept;
  friend bool operator!=(const CompactID &lhs, const CompactID &rhs) noexcept;

  void generateXml(QXmlStreamWriter &xmlWriter) const;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  void toDebugString(QDebug dbg) const;
};

} // namespace MSONcommon

#endif // COMPACTID_H
