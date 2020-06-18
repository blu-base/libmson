#ifndef HELPER_H
#define HELPER_H

#include <QtCore/qglobal.h>
#include <QString>

template <class _InIt, class _OutIt, class _Pr>
inline void copy_closed(_InIt _First, _InIt _Last, _OutIt _Dest, _Pr _Pred);

template <class _InIt, class _OutIt, class _Pr>
inline void copy_until(_InIt _First, _InIt _Last, _OutIt _Dest, _Pr _Pred);



template <typename T>
QString qStringHex(const T value,const quint8 width);



#endif // HELPER_H
