#ifndef FILEDATASTOREOBJECTREFERENCEFND_H
#define FILEDATASTOREOBJECTREFERENCEFND_H

#include "../commonTypes/FileNodeChunkReference.h"
#include "../otherTypes/FileDataStoreObject.h"

#include "IFileNodeType.h"

#include <QUuid>
#include <QtCore/qglobal.h>

namespace MSONcommon {

class FileDataStoreObjectReferenceFND : public IFileNodeType {
private:
  FileNodeChunkReference m_ref;
  QUuid m_guidReference;

  FileDataStoreObject m_blob;

public:
  FileDataStoreObjectReferenceFND(FNCR_STP_FORMAT stpFormat,
                                  FNCR_CB_FORMAT cbFormat);
  FileDataStoreObjectReferenceFND(quint8 stpFormat, quint8 cbFormat);
  virtual ~FileDataStoreObjectReferenceFND() = default;

  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &value);

  QUuid getGuidReference() const;
  void setGuidReference(const QUuid &value);

  FileDataStoreObject getFileDataStoreObject() const;
  void setFileDataStoreObject(const FileDataStoreObject &value);

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;
};

} // namespace MSONcommon

#endif // FILEDATASTOREOBJECTREFERENCEFND_H
