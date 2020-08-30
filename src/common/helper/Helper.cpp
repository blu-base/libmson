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

// Parse all fragments and add them to m_fileNodeSequence
std::vector<MSONcommon::FileNodeListFragment>
parseFileNodeListFragments(QDataStream &ds, FileChunkReference64x32 &ref) {
  quint64 preLocation = ds.device()->pos();
  std::vector<MSONcommon::FileNodeListFragment> fragments{};

  ds.device()->seek(ref.stp());


  MSONcommon::FileNodeListFragment fragment(ref);

  ds >> fragment;
  fragments.push_back(fragment);

  FileChunkReference64x32 nextFragmentRef = fragment.nextFragment();

  while (!nextFragmentRef.is_fcrNil() && !nextFragmentRef.is_fcrZero()) {
    MSONcommon::FileNodeListFragment nextFragment(nextFragmentRef);
    ds.device()->seek(nextFragmentRef.stp());
    ds >> nextFragment;

    nextFragmentRef = nextFragment.nextFragment();
    fragments.push_back(nextFragment);
  }

  ds.device()->seek(preLocation);
  return fragments;
}

std::vector<MSONcommon::FileNodeListFragment>
parseFileNodeListFragments(QDataStream &ds, FileNodeChunkReference &ref) {
  FileChunkReference64x32 tref(ref.stp(), static_cast<quint32>(ref.cb()));

  return parseFileNodeListFragments(ds, tref);
}
