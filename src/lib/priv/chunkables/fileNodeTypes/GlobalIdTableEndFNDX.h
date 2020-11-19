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
  GlobalIdTableEndFNDX(FileNode_WPtr_t parentFileNode)
      : IFileNodeType(std::move(parentFileNode)){};
  virtual ~GlobalIdTableEndFNDX() = default;

  virtual quint64 getSizeInFile() const override { return 0; };

private:
  virtual void deserialize(QDataStream& ds) override{};
  virtual void serialize(QDataStream& ds) const override{};
};

} // namespace priv
} // namespace libmson

#endif // GLOBALIDTABLEENDFNDX_H
