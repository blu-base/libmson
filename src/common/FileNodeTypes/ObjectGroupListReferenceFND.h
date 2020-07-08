#ifndef OBJECTGROUPLISTREFERENCEFND_H
#define OBJECTGROUPLISTREFERENCEFND_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "../commonTypes/FileNodeChunkReference.h"
#include "IFileNodeType.h"

class ObjectGroupListReferenceFND : public IFileNodeType {
private:
  FileNodeChunkReference mRef;

  ExtendedGUID mObjectGroupID;

public:
  ObjectGroupListReferenceFND(FNCR_STP_FORMAT stpFormat,
                              FNCR_CB_FORMAT cbFormat);
  ObjectGroupListReferenceFND(quint8 stpFormat, quint8 cbFormat);
  ~ObjectGroupListReferenceFND();

  FileNodeChunkReference ref() const;
  void setRef(const FileNodeChunkReference &ref);

  ExtendedGUID objectGroupID() const;
  void setObjectGroupID(const ExtendedGUID &objectGroupID);

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // OBJECTGROUPLISTREFERENCEFND_H
