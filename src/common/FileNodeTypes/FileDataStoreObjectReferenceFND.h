#ifndef FILEDATASTOREOBJECTREFERENCEFND_H
#define FILEDATASTOREOBJECTREFERENCEFND_H

#include "../commonTypes/FileNodeChunkReference.h"
#include "../otherTypes/FileDataStoreObject.h"

#include "IFileNodeType.h"

#include <QUuid>
#include <QtCore/qglobal.h>

class FileDataStoreObjectReferenceFND : public IFileNodeType {
private:
  FileNodeChunkReference m_ref;
  QUuid m_guidReference;

  FileDataStoreObject m_blob;

public:
  FileDataStoreObjectReferenceFND(FNCR_STP_FORMAT stpFormat,
                                  FNCR_CB_FORMAT cbFormat);
  FileDataStoreObjectReferenceFND(quint8 stpFormat, quint8 cbFormat);
  ~FileDataStoreObjectReferenceFND();

  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &value);

  QUuid getGuidReference() const;
  void setGuidReference(const QUuid &value);

  FileDataStoreObject getFileDataStoreObject() const;
  void setFileDataStoreObject(const FileDataStoreObject &value);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // FILEDATASTOREOBJECTREFERENCEFND_H
