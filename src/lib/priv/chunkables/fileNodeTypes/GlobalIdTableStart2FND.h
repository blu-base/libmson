#ifndef GLOBALIDTABLESTART2FND_H
#define GLOBALIDTABLESTART2FND_H

#include "../../IStreamable.h"
#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

class GlobalIdTableStart2FND
    : public IFileNodeType
    , public IStreamable {
public:
  GlobalIdTableStart2FND(FileNode_WPtr_t parentFileNode)
      : IFileNodeType(parentFileNode){};
  virtual ~GlobalIdTableStart2FND() = default;

  virtual quint64 getSizeInFile() const override { return 0; };

private:
  virtual void deserialize(QDataStream& ds) override{};
  virtual void serialize(QDataStream& ds) const override{};
};

} // namespace priv
} // namespace libmson

#endif // GLOBALIDTABLESTART2FND_H
