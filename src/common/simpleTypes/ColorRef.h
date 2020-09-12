#ifndef COLORREF_H
#define COLORREF_H

#include <QDataStream>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QtCore/qglobal.h>

#include "../IDeserializable.h"
#include "../ISerializable.h"

namespace MSONcommon {

class ColorRef : public ISerializable, public IDeserializable {
private:
  quint32 m_colorVal;

public:
  ColorRef();
  ColorRef(const quint32 colorVal);


  friend QDebug operator<<(QDebug dbg, const ColorRef &obj);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

  bool isSpecifiesColor() const;

  quint32 getColorRef() const;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const;
};

} // namespace MSONcommon

#endif // COLORREF_H
