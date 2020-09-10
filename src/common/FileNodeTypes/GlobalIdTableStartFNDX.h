#ifndef GLOBALIDTABLESTARTFNDX_H
#define GLOBALIDTABLESTARTFNDX_H

#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace MSONcommon {
class GlobalIdTableStartFNDX : public IFileNodeType {
private:
  quint8 m_reserved;

public:
  GlobalIdTableStartFNDX();

  quint8 getReserved() const;
  void setReserved(const quint8 &value);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds);
  void serialize(QDataStream &ds) const;
  void toDebugString(QDebug dbg) const;
};

} // namespace MSONcommon
#endif // GLOBALIDTABLESTARTFNDX_H
