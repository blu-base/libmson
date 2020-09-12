#ifndef BODYTEXTALIGNMENT_H
#define BODYTEXTALIGNMENT_H

#include <QtCore/qglobal.h>


#include <QDebug>
#include <QXmlStreamWriter>

#include "../IDeserializable.h"
#include "../ISerializable.h"

namespace MSONcommon {

class BodyTextAlignment : public ISerializable, public IDeserializable {
private:
  quint32 m_value;

public:
  BodyTextAlignment();


  friend QDebug operator<<(QDebug dbg, const BodyTextAlignment &obj);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

  quint32 value() const;
  void setValue(const quint32 val);

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  void toDebugString(QDebug dbg) const;
};

} // namespace MSONcommon

#endif // BODYTEXTALIGNMENT_H
