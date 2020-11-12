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
  GlobalIdTableStart2FND(RSChunkContainer_WPtr_t parentFileNode);
  virtual ~GlobalIdTableStart2FND() = default;

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;


  static const quint64 sizeInFile = 0;
};

} // namespace priv
} // namespace libmson

#endif // GLOBALIDTABLESTART2FND_H
