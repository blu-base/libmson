#ifndef COLORREF_H
#define COLORREF_H

#include <QDataStream>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QtCore/qglobal.h>

#include "../IRevisionStoreFileObject.h"

namespace MSONcommon {

class ColorRef : public IRevisionStoreFileObject {
private:
  quint32 m_colorVal;

public:
  ColorRef();
  ColorRef(const quint32 colorVal);

  friend QDebug operator<<(QDebug dbg, const ColorRef &obj);



  bool isSpecifiesColor() const;

  quint32 getColorRef() const;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  void toDebugString(QDebug dbg) const;
};

} // namespace MSONcommon

#endif // COLORREF_H
