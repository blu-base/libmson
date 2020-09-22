#ifndef FILEDATASTORELISTREFERENCEFND_H
#define FILEDATASTORELISTREFERENCEFND_H

#include <QtCore/qglobal.h>

#include "../FileNodeListFragment.h"
#include "../commonTypes/FileNodeChunkReference.h"

#include "IFileNodeType.h"

namespace MSONcommon {

class FileDataStoreListReferenceFND : public IFileNodeType {
private:
  FileNodeChunkReference m_ref;

  FileNodeListFragment m_StoreList;

public:
  FileDataStoreListReferenceFND(FNCR_STP_FORMAT stpFormat,
                                FNCR_CB_FORMAT cbFormat);
  FileDataStoreListReferenceFND(quint8 stpFormat, quint8 cbFormat);
  virtual ~FileDataStoreListReferenceFND() = default;

  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &value);

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;

};

} // namespace MSONcommon

#endif // FILEDATASTORELISTREFERENCEFND_H
