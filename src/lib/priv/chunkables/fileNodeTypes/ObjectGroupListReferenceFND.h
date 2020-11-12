#ifndef OBJECTGROUPLISTREFERENCEFND_H
#define OBJECTGROUPLISTREFERENCEFND_H

#include <QtCore/qglobal.h>

#include "../../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"

namespace libmson {
namespace priv {

class ObjectGroupListReferenceFND : public IFileNodeType {
private:
  RSChunkContainer_WPtr_t m_ref;
  ExtendedGUID m_ObjectGroupID;

public:
  ObjectGroupListReferenceFND(RSChunkContainer_WPtr_t parentFileNode);
  virtual ~ObjectGroupListReferenceFND() = default;

  RSChunkContainer_WPtr_t getRef() const;
  void setRef(const RSChunkContainer_WPtr_t& ref);

  ExtendedGUID objectGroupID() const;
  void setObjectGroupID(const ExtendedGUID& objectGroupID);

  virtual quint64 getSizeInFile() const override;

  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;

  // private:
  //  virtual void deserialize(QDataStream &ds) override;
  //  virtual void serialize(QDataStream &ds) const override;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTGROUPLISTREFERENCEFND_H
