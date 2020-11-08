#ifndef RSFTOXML_H
#define RSFTOXML_H

#include <QtCore/qglobal.h>
#include <QXmlStreamWriter>



static class RSFtoXml {


    QXmlStreamWriter& operator<<(QXmlStreamWriter& stream, const ChunkTerminatorFND& fnd);


};


#endif // RSFTOXML_H
