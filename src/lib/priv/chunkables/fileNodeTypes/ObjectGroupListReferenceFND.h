#ifndef OBJECTGROUPLISTREFERENCEFND_H
#define OBJECTGROUPLISTREFERENCEFND_H

#include <QtCore/qglobal.h>

#include "../../commonTypes/ExtendedGUID.h"
#include "../../commonTypes/FileNodeChunkReference.h"

#include "IFileNodeType.h"

namespace libmson{
namespace priv{

class ObjectGroupListReferenceFND : public IFileNodeType {
private:
  FileNodeChunkReference m_ref;
  ExtendedGUID m_ObjectGroupID;

public:
  ObjectGroupListReferenceFND(FNCR_STP_FORMAT stpFormat,
                              FNCR_CB_FORMAT cbFormat);
  ObjectGroupListReferenceFND(quint8 stpFormat, quint8 cbFormat);
  ~ObjectGroupListReferenceFND() = default;

  FileNodeChunkReference ref() const;
  void setRef(const FileNodeChunkReference &ref);

  ExtendedGUID objectGroupID() const;
  void setObjectGroupID(const ExtendedGUID &objectGroupID);

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;




};

} //namespace priv
} // namespace libmson

#endif // OBJECTGROUPLISTREFERENCEFND_H
