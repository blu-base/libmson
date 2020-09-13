#ifndef COMPACTID_H
#define COMPACTID_H

#include <QtCore/qglobal.h>

#include "ExtendedGUID.h"

#include "../IRevisionStoreFileObject.h"

namespace MSONcommon {

class CompactID : public IRevisionStoreFileObject {
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

  friend bool operator==(const CompactID &lhs, const CompactID &rhs) noexcept;
  friend bool operator!=(const CompactID &lhs, const CompactID &rhs) noexcept;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;
};

} // namespace MSONcommon

#endif // COMPACTID_H
