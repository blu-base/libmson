#include "ObjectInfoDependencyOverridesFND.h"

ObjectInfoDependencyOverridesFND::ObjectInfoDependencyOverridesFND(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : ref(stpFormat, cbFormat) {}

ObjectInfoDependencyOverridesFND::ObjectInfoDependencyOverridesFND(
    quint8 stpFormat, quint8 cbFormat)
    : ref(stpFormat, cbFormat) {}

ObjectInfoDependencyOverridesFND::~ObjectInfoDependencyOverridesFND() {}

ObjectInfoDependencyOverrideData
ObjectInfoDependencyOverridesFND::getData() const {
  return data;
}

void ObjectInfoDependencyOverridesFND::setData(
    const ObjectInfoDependencyOverrideData &value) {
  data = value;
}

FileNodeChunkReference ObjectInfoDependencyOverridesFND::getRef() const {
  return ref;
}

void ObjectInfoDependencyOverridesFND::setRef(
    const FileNodeChunkReference &value) {
  ref = value;
}

/**
 * @brief ObjectInfoDependencyOverridesFND::deserialize
 * @param ds
 *
 * \todo check if device/seek stuff is working
 */
void ObjectInfoDependencyOverridesFND::deserialize(QDataStream &ds) {
  ds >> ref;

  if (ref.is_fcrNil()) {
    //        ds >> data;
  } else {
    quint64 currentloc = ds.device()->pos();
    ds.device()->seek(ref.stp());
    //        ds >> data;
    ds.device()->seek(currentloc);
  }
}

/**
 * @brief ObjectInfoDependencyOverridesFND::serialize
 * @param ds
 *
 * \todo likely contains bugs
 * \todo ObjectInfoDependencyOverrideData is not yet parsed.
 */
void ObjectInfoDependencyOverridesFND::serialize(QDataStream &ds) const {
  ds << ref;

  if (ref.is_fcrNil()) {
    //        ds << data;
  } else {
    quint64 currentloc = ds.device()->pos();
    ds.device()->seek(ref.stp());
    //        ds << data;
    ds.device()->seek(currentloc);
  }
}

void ObjectInfoDependencyOverridesFND::toDebugString(QDebug dbg) const {
  dbg << " ObjectInfoDependencyOverridesFND:\n"
      << " ref: "
      << ref
      //        << "data: " << data
      << '\n';
}
