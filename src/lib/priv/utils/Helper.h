#ifndef HELPER_H
#define HELPER_H

#include <QString>
#include <QtCore/qglobal.h>

//#include "../FileNodeListFragment.h"
#include <vector>

namespace libmson {
namespace priv {

template <class _InIt, class _OutIt, class _Pr>
inline void copy_closed(_InIt _First, _InIt _Last, _OutIt _Dest, _Pr _Pred);

template <class _InIt, class _OutIt, class _Pr>
inline void copy_until(_InIt _First, _InIt _Last, _OutIt _Dest, _Pr _Pred);

template <class T> QString qStringHex(const T val, const quint8 width)

{
  return QString("0x%1").arg(val, width, 16, QLatin1Char('0'));
}

/**
 * @brief round num up to the next full multiple
 * @param num
 * @param multiple
 * @return round up value
 *
 * It's used to calculate the padding of m_FileData, e.g. (10,8) will be round
 * up to 16.
 */
quint64 ceilToMultiple(const quint64 num, const quint64 multiple);

// std::vector<std::shared_ptr<FileNodeListFragment>>
// parseFileNodeListFragments(QDataStream& ds, const FileChunkReference64x32&
// ref);
// std::vector<std::shared_ptr<FileNodeListFragment>>
// parseFileNodeListFragments(QDataStream& ds, const FileNodeChunkReference&
// ref);

} // namespace priv
} // namespace libmson

#endif // HELPER_H
