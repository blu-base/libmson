#ifndef MSONREADER_H
#define MSONREADER_H

#include <QtCore/qglobal.h>

#include <QIODevice>

class MSONStreamReader
{
public:
  MSONStreamReader();

  MSONStreamReader(QIODevice *device);
  MSONStreamReader(const QByteArray &data);
  MSONStreamReader(const QString &data);
  MSONStreamReader(const char *data);


};

#endif // MSONREADER_H
