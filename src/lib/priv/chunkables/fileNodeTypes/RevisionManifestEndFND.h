#ifndef REVISIONMANIFESTENDFND_H
#define REVISIONMANIFESTENDFND_H

#include "../../IStreamable.h"
#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

class RevisionManifestEndFND
    : public IFileNodeType
    , public IStreamable {
public:
  RevisionManifestEndFND(FileNode_WPtr_t parentFileNode)
      : IFileNodeType(std::move(parentFileNode)){};
  virtual ~RevisionManifestEndFND() = default;

  virtual quint64 getSizeInFile() const override { return 0; }

private:
  virtual void deserialize(QDataStream& ds) override{};
  virtual void serialize(QDataStream& ds) const override{};
};

} // namespace priv
} // namespace libmson

#endif // REVISIONMANIFESTENDFND_H
