#ifndef FILEDATASTOREOBJECTREFERENCEFND_H
#define FILEDATASTOREOBJECTREFERENCEFND_H

#include "../commonTypes/FileNodeChunkReference.h"
#include "../otherTypes/FileDataStoreObject.h"

#include "IFileNodeType.h"

#include <QUuid>
#include <QtCore/qglobal.h>

namespace libmson{
namespace priv{

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

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;





  static const quint64 sizeOfGUID = 16;
};

} //namespace priv
} // namespace libmson

#endif // FILEDATASTOREOBJECTREFERENCEFND_H
