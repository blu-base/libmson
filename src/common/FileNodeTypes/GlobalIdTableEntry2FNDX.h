#ifndef GLOBALIDTABLEENTRY2FNDX_H
#define GLOBALIDTABLEENTRY2FNDX_H

#include <QtCore/qglobal.h>

#include "IFileNodeType.h"

class GlobalIdTableEntry2FNDX : public IFileNodeType {
private:
  quint32 m_iIndexMapFrom;
  quint32 m_iIndexMapTo;

public:
  GlobalIdTableEntry2FNDX();

  quint32 getIIndexMapTo() const;
  void setIIndexMapTo(const quint32 &value);

  quint32 getIIndexMapFrom() const;
  void setIIndexMapFrom(const quint32 &value);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // GLOBALIDTABLEENTRY2FNDX_H
