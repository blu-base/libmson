#ifndef GLOBALIDTABLEENTRY2FNDX_H
#define GLOBALIDTABLEENTRY2FNDX_H

#include <QtCore/qglobal.h>

#include "IFileNodeType.h"

namespace libmson{
namespace priv{

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

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;





  static const quint64 sizeInFile = 8;
};

} //namespace priv
} // namespace libmson

#endif // GLOBALIDTABLEENTRY2FNDX_H
