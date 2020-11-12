#ifndef GLOBALIDTABLEENDFNDX_H
#define GLOBALIDTABLEENDFNDX_H

#include "../../IStreamable.h"
#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

class GlobalIdTableEndFNDX
    : public IFileNodeType
    , public IStreamable {
public:
  GlobalIdTableEndFNDX(RSChunkContainer_WPtr_t parentFileNode);
  virtual ~GlobalIdTableEndFNDX() = default;

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

} // namespace priv
} // namespace libmson

#endif // GLOBALIDTABLEENDFNDX_H
