#ifndef FILEDATASTOREOBJECTREFERENCEFND_H
#define FILEDATASTOREOBJECTREFERENCEFND_H

#include <QtCore/qglobal.h>
#include <QUuid>
#include "../commonTypes/FileNodeChunkReference.h"
#include "IFileNodeType.h"
class FileDataStoreObjectReferenceFND : public IFileNodeType
{
public:
    FileDataStoreObjectReferenceFND(FNCR_STP_FORMAT stpFormat,
                                      FNCR_CB_FORMAT cbFormat);
    FileDataStoreObjectReferenceFND(quint8 stpFormat, quint8 cbFormat);
    ~FileDataStoreObjectReferenceFND();

    FileNodeChunkReference ref;
    QUuid guidReference;


    FileNodeChunkReference getRef() const;
    void setRef(const FileNodeChunkReference& value);

    QUuid getGuidReference() const;
    void setGuidReference(const QUuid& value);

private:
    void deserialize(QDataStream& ds) override;
    void serialize(QDataStream& ds) const override;
    void toDebugString(QDebug dbg) const override;
};

#endif // FILEDATASTOREOBJECTREFERENCEFND_H
