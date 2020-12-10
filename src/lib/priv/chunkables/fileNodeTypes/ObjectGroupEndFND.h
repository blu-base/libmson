#ifndef OBJECTGROUPENDFND_H
#define OBJECTGROUPENDFND_H

#include "../../IStreamable.h"
#include "IFileNodeType.h"
#include <QtCore/qglobal.h>
namespace libmson {
namespace priv {

class ObjectGroupEndFND
    : public IFileNodeType
    , public IStreamable {
public:
  ObjectGroupEndFND(FileNode_SPtr_t parentFileNode)
      : IFileNodeType(std::move(parentFileNode)){};
  virtual ~ObjectGroupEndFND() = default;

  virtual quint64 getSizeInFile() const override { return 0; }
  virtual FileNodeTypeID getType() const override
  {
    return FileNodeTypeID::ObjectGroupEndFND;
  };

private:
  virtual void deserialize(QDataStream& ds) override{};
  virtual void serialize(QDataStream& ds) const override{};
};

} // namespace priv
} // namespace libmson

#endif // OBJECTGROUPENDFND_H
