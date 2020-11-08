#ifndef GLOBALIDTABLEENDFNDX_H
#define GLOBALIDTABLEENDFNDX_H

#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace libmson{
namespace priv{

class GlobalIdTableEndFNDX : public IFileNodeType {
public:
  GlobalIdTableEndFNDX() = default;

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;




};

} //namespace priv
} // namespace libmson

#endif // GLOBALIDTABLEENDFNDX_H
