#ifndef COLORREF_H
#define COLORREF_H

#include <QDataStream>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QtCore/qglobal.h>

class ColorRef {
private:
  quint32 m_colorVal;

public:
  ColorRef();
  ColorRef(const quint32 colorVal);

  friend QDataStream &operator<<(QDataStream &ds, const ColorRef &obj);
  friend QDataStream &operator>>(QDataStream &ds, ColorRef &obj);

  friend QDebug operator<<(QDebug dbg, const ColorRef &obj);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

  bool isSpecifiesColor() const;

  quint32 getColorRef() const;

private:
  void deserialize(QDataStream &ds);
  void serialize(QDataStream &ds) const;
  void toDebugString(QDebug dbg) const;
};

#endif // COLORREF_H
