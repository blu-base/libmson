#ifndef BODYTEXTALIGNMENT_H
#define BODYTEXTALIGNMENT_H

#include <QtCore/qglobal.h>

#include <QDebug>
#include <QXmlStreamWriter>

#include "../IRevisionStoreFileObject.h"

namespace MSONcommon {

class BodyTextAlignment : public IRevisionStoreFileObject {
private:
  quint32 m_value;

public:
  BodyTextAlignment();

  friend QDebug operator<<(QDebug dbg, const BodyTextAlignment &obj);

  quint32 value() const;
  void setValue(const quint32 val);

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  void toDebugString(QDebug dbg) const;
};

} // namespace MSONcommon

#endif // BODYTEXTALIGNMENT_H
