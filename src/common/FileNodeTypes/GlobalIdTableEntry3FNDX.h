#ifndef GLOBALIDTABLEENTRY3FNDX_H
#define GLOBALIDTABLEENTRY3FNDX_H

#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace MSONcommon {
class GlobalIdTableEntry3FNDX : public IFileNodeType {
private:
  quint32 m_iIndexCopyFromStart;
  quint32 m_cEntriesToCopy;
  quint32 m_iIndexCopyToStart;

public:
  GlobalIdTableEntry3FNDX();

  quint32 getIIndexCopyFromStart() const;
  void setIIndexCopyFromStart(const quint32 &value);

  quint32 getCEntriesToCopy() const;
  void setCEntriesToCopy(const quint32 &value);

  quint32 getIIndexCopyToStart() const;
  void setIIndexCopyToStart(const quint32 &value);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // GLOBALIDTABLEENTRY3FNDX_H
