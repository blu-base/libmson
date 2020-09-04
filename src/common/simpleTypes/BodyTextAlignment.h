#ifndef BODYTEXTALIGNMENT_H
#define BODYTEXTALIGNMENT_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDebug>
#include <QXmlStreamWriter>

class BodyTextAlignment {
private:
  quint32 m_value;

public:
  BodyTextAlignment();

  friend QDataStream &operator<<(QDataStream &ds, const BodyTextAlignment &obj);
  friend QDataStream &operator>>(QDataStream &ds, BodyTextAlignment &obj);

  friend QDebug operator<<(QDebug dbg, const BodyTextAlignment &obj);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

  quint32 value() const;
  void setValue(const quint32 val);

private:
  void deserialize(QDataStream &ds);
  void serialize(QDataStream &ds) const;
  void toDebugString(QDebug dbg) const;
};

#endif // BODYTEXTALIGNMENT_H
