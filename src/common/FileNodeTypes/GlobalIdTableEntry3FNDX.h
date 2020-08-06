#ifndef GLOBALIDTABLEENTRY3FNDX_H
#define GLOBALIDTABLEENTRY3FNDX_H

#include <QtCore/qglobal.h>
#include "IFileNodeType.h"


class GlobalIdTableEntry3FNDX : public IFileNodeType
{
private:
    quint32 m_iIndexCopyFromStart;

    quint32 m_cEntriesToCopy;

    quint32 m_iIndexCopyToStart;
public:
  GlobalIdTableEntry3FNDX();





  quint32 getIIndexCopyFromStart() const;
  void setIIndexCopyFromStart(const quint32& value);
  quint32 getCEntriesToCopy() const;
  void setCEntriesToCopy(const quint32& value);
  quint32 getIIndexCopyToStart() const;
  void setIIndexCopyToStart(const quint32& value);

  // IFileNodeType interface
private:
  void deserialize(QDataStream& ds) override;
  void serialize(QDataStream& ds) const override;
  void toDebugString(QDebug dbg) const override;

  // IFileNodeType interface
public:
  virtual void generateXml(QXmlStreamWriter& xmlWriter) const override;
};

#endif // GLOBALIDTABLEENTRY3FNDX_H
