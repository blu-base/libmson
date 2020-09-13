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

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;
};

} // namespace MSONcommon

#endif // GLOBALIDTABLESTARTFNDX_H
