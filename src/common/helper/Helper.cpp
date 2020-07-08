#include "Helper.h"

template <class _InIt, class _OutIt, class _Pr>
inline void copy_closed(_InIt _First, _InIt _Last, _OutIt _Dest, _Pr _Pred) {
  _InIt _posTerm = std::find_if(_First, _Last, _Pred);
  if (_posTerm != _Last) {
    _posTerm++;
  }
  std::copy(_First, _posTerm, _Dest);
}

template <class _InIt, class _OutIt, class _Pr>
inline void copy_until(_InIt _First, _InIt _Last, _OutIt _Dest, _Pr _Pred) {
  _InIt _posTerm = std::find_if(_First, _Last, _Pred);
  std::copy(_First, _posTerm, _Dest);
}

quint64 roundUpMultiple(const quint64 numToRound, const quint64 multiple) {
  if (multiple == 0)
    return numToRound;

  quint64 remainder = numToRound % multiple;
  if (remainder == 0) {
    return numToRound;
  } else {
    return numToRound + multiple - remainder;
  }
}
