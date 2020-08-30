#ifndef FILEDATASTORELISTREFERENCEFND_H
#define FILEDATASTORELISTREFERENCEFND_H

#include <QtCore/qglobal.h>

#include "../FileNodeListFragment.h"
#include "../commonTypes/FileNodeChunkReference.h"

#include "IFileNodeType.h"

class FileDataStoreListReferenceFND : public IFileNodeType {
private:
  FileNodeChunkReference m_ref;

  MSONcommon::FileNodeListFragment m_StoreList;

public:
  FileDataStoreListReferenceFND(FNCR_STP_FORMAT stpFormat,
                                FNCR_CB_FORMAT cbFormat);
  FileDataStoreListReferenceFND(quint8 stpFormat, quint8 cbFormat);
  ~FileDataStoreListReferenceFND();

  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &value);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // FILEDATASTORELISTREFERENCEFND_H
