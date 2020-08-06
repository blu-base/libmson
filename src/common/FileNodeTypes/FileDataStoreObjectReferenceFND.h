#ifndef FILEDATASTOREOBJECTREFERENCEFND_H
#define FILEDATASTOREOBJECTREFERENCEFND_H

#include <QtCore/qglobal.h>
#include <QUuid>
#include "../commonTypes/FileNodeChunkReference.h"
#include "IFileNodeType.h"
class FileDataStoreObjectReferenceFND : public IFileNodeType
{
private:
    FileNodeChunkReference m_ref;
    QUuid m_guidReference;

public:
    FileDataStoreObjectReferenceFND(FNCR_STP_FORMAT stpFormat,
                                      FNCR_CB_FORMAT cbFormat);
    FileDataStoreObjectReferenceFND(quint8 stpFormat, quint8 cbFormat);
    ~FileDataStoreObjectReferenceFND();



    FileNodeChunkReference getRef() const;
    void setRef(const FileNodeChunkReference& value);

    QUuid getGuidReference() const;
    void setGuidReference(const QUuid& value);

private:
    void deserialize(QDataStream& ds) override;
    void serialize(QDataStream& ds) const override;
    void toDebugString(QDebug dbg) const override;

    // IFileNodeType interface
public:
    virtual void generateXml(QXmlStreamWriter& xmlWriter) const override;
};

#endif // FILEDATASTOREOBJECTREFERENCEFND_H
