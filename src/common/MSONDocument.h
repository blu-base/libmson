#ifndef MSONDOCUMENT_H
#define MSONDOCUMENT_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDebug>
#include <QIODevice>

#include "FileNodeList.h"
#include "MSONHeader.h"

namespace MSONcommon {

class MSONDocument {

private:
  MSONHeader *m_header;

  FileNodeList m_fnlRoot;

public:
  MSONDocument();
  ~MSONDocument();

  friend QDataStream &operator<<(QDataStream &ds, const MSONDocument &obj);
  friend QDataStream &operator>>(QDataStream &ds, MSONDocument &obj);

  friend QDebug operator<<(QDebug dbg, const MSONDocument &obj);

  MSONHeader header() const;
  //  void setHeader(MSONHeader header);
  FileNodeList fnlRoot() const;
  void setFnlRoot(const FileNodeList &fnlRoot);
};

#endif // MSONDOCUMENT_H

}
