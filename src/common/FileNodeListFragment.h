#ifndef FILENODELISTFRAGMENT_H
#define FILENODELISTFRAGMENT_H

#include <QtCore/qglobal.h>

#include "commonTypes/FileChunkReference64x32.h"

class FileNodeListFragment {
private:
  quint64 m_offset;
  quint64 m_size;

  static constexpr const uint64_t footer_magic_id = 0x8BC215C38233BA4B;

  FileChunkReference64x32 *m_next;

public:
  FileNodeListFragment();

  friend QDataStream &operator<<(QDataStream &s,
                                 const FileNodeListFragment &obj);
  friend QDataStream &operator>>(QDataStream &s, FileNodeListFragment &obj);

  friend QDebug operator<<(QDebug dbg, const FileNodeListFragment &obj);
};

#endif // FILENODELISTFRAGMENT_H
