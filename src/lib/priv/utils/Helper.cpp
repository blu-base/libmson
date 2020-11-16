#include "Helper.h"

namespace libmson {
namespace priv {

template <class _InIt, class _OutIt, class _Pr>
inline void copy_closed(_InIt _First, _InIt _Last, _OutIt _Dest, _Pr _Pred)
{
  _InIt _posTerm = std::find_if(_First, _Last, _Pred);
  if (_posTerm != _Last) {
    _posTerm++;
  }
  std::copy(_First, _posTerm, _Dest);
}

template <class _InIt, class _OutIt, class _Pr>
inline void copy_until(_InIt _First, _InIt _Last, _OutIt _Dest, _Pr _Pred)
{
  _InIt _posTerm = std::find_if(_First, _Last, _Pred);
  std::copy(_First, _posTerm, _Dest);
}

quint64 ceilToMultiple(const quint64 num, const quint64 multiple)
{
  if (multiple == 0) {
    return 0;
  }

  quint64 remainder = num % multiple;
  if (remainder == 0) {
    return num;
  }
  return num + multiple - remainder;
}

//// Parse all fragments and add them to m_fileNodeSequence
// std::vector<std::shared_ptr<FileNodeListFragment>>
// parseFileNodeListFragments(QDataStream &ds,
//                           const FileChunkReference64x32 &ref) {
//  quint64 preLocation = ds.device()->pos();
//  std::vector<std::shared_ptr<FileNodeListFragment>> fragments{};

//  ds.device()->seek(ref.stp());

//  std::shared_ptr<FileNodeListFragment> fragment =
//      std::make_shared<FileNodeListFragment>(ref);

//  ds >> *fragment;
//  fragments.push_back(fragment);

//  auto nextFragmentRef = fragment->getNextFragment();

//  while (!nextFragmentRef.is_fcrNil() && !nextFragmentRef.is_fcrZero()) {
//    std::shared_ptr<FileNodeListFragment> nextFragment =
//        std::make_shared<FileNodeListFragment>(nextFragmentRef);
//    ds.device()->seek(nextFragmentRef.stp());
//    ds >> *nextFragment;

//    nextFragmentRef = nextFragment->getNextFragment();
//    fragments.push_back(nextFragment);
//  }

//  ds.device()->seek(preLocation);
//  return fragments;
//}

// std::vector<std::shared_ptr<FileNodeListFragment>>
// parseFileNodeListFragments(QDataStream &ds, const FileNodeChunkReference
// &ref) {
//  FileChunkReference64x32 tref(ref.stp(), static_cast<quint32>(ref.cb()));

//  return parseFileNodeListFragments(ds, tref);
//}

} // namespace priv
} // namespace libmson
