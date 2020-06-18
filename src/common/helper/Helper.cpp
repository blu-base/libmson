#include "Helper.h"

template <class _InIt, class _OutIt, class _Pr>
inline void copy_closed(_InIt _First, _InIt _Last, _OutIt _Dest, _Pr _Pred)
{
    _InIt _posTerm = std::find_if(_First, _Last, _Pred);
    if (_posTerm != _Last ) { _posTerm++; }
    std::copy(_First,_posTerm,_Dest);
}

template <class _InIt, class _OutIt, class _Pr>
inline void copy_until(_InIt _First, _InIt _Last, _OutIt _Dest, _Pr _Pred)
{
    _InIt _posTerm = std::find_if(_First, _Last, _Pred);
    std::copy(_First,_posTerm,_Dest);
}

template<typename T>
QString qStringHex(const T val,const quint8 width)
{
    return QString("0x%1").arg(val,width,16,QLatin1Char('0'));
}
