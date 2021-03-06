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
  RevisionManifestEndFND(FileNode_SPtr_t parentFileNode)
      : IFileNodeType(std::move(parentFileNode)){};
  virtual ~RevisionManifestEndFND() = default;

  virtual quint64 getSizeInFile() const override { return 0; }
  virtual FileNodeTypeID getType() const override
  {
    return FileNodeTypeID::RevisionManifestEndFND;
  };

private:
  virtual void deserialize(QDataStream& ds) override { Q_UNUSED(ds) };
  virtual void serialize(QDataStream& ds) const override { Q_UNUSED(ds) };
};

} // namespace priv
} // namespace libmson

#endif // REVISIONMANIFESTENDFND_H
