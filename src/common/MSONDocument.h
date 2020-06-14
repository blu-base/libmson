#ifndef MSONDOCUMENT_H
#define MSONDOCUMENT_H

#include <QtCore/qglobal.h>

#include <QIODevice>

#include "MSONHeader.h"

class MSONDocument
{


private:
  MSONHeader* m_header;

public:
  MSONDocument();
  ~MSONDocument();



  MSONHeader* header() const;
  void setHeader(MSONHeader* header);
};

#endif // MSONDOCUMENT_H
