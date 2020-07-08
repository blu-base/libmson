#ifndef HELPER_H
#define HELPER_H

#include <QString>
#include <QtCore/qglobal.h>

template <class _InIt, class _OutIt, class _Pr>
inline void copy_closed(_InIt _First, _InIt _Last, _OutIt _Dest, _Pr _Pred);

template <class _InIt, class _OutIt, class _Pr>
inline void copy_until(_InIt _First, _InIt _Last, _OutIt _Dest, _Pr _Pred);

template <class T>
QString qStringHex(const T val, const quint8 width)

{
  return QString("0x%1").arg(val, width, 16, QLatin1Char('0'));
}

/**
 * @brief round numToRound up to the nearest multiple
 * @param numToRound
 * @param multiple
 * @return round up value
 *
 * It's used to calculate the padding of m_FileData
 */
quint64 roundUpMultiple(const quint64 numToRound, const quint64 multiple);

#endif // HELPER_H
