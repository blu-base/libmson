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
  GlobalIdTableEndFNDX(FileNode_SPtr_t parentFileNode)
      : IFileNodeType(std::move(parentFileNode)){};
  virtual ~GlobalIdTableEndFNDX() = default;

  virtual quint64 getSizeInFile() const override { return 0; };
  virtual FileNodeTypeID getType() const override
  {
    return FileNodeTypeID::GlobalIdTableEndFNDX;
  };

private:
  virtual void deserialize(QDataStream& ds) override { Q_UNUSED(ds) };
  virtual void serialize(QDataStream& ds) const override { Q_UNUSED(ds) };
};

} // namespace priv
} // namespace libmson

#endif // GLOBALIDTABLEENDFNDX_H
