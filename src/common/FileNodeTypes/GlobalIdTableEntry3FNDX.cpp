#include "GlobalIdTableEntry3FNDX.h"

GlobalIdTableEntry3FNDX::GlobalIdTableEntry3FNDX()
    : iIndexCopyFromStart{0}, cEntriesToCopy{0}, iIndexCopyToStart{0} {}

quint32 GlobalIdTableEntry3FNDX::getIIndexCopyFromStart() const {
  return iIndexCopyFromStart;
}

void GlobalIdTableEntry3FNDX::setIIndexCopyFromStart(const quint32 &value) {
  iIndexCopyFromStart = value;
}

quint32 GlobalIdTableEntry3FNDX::getCEntriesToCopy() const {
  return cEntriesToCopy;
}

void GlobalIdTableEntry3FNDX::setCEntriesToCopy(const quint32 &value) {
  cEntriesToCopy = value;
}

quint32 GlobalIdTableEntry3FNDX::getIIndexCopyToStart() const {
  return iIndexCopyToStart;
}

void GlobalIdTableEntry3FNDX::setIIndexCopyToStart(const quint32 &value) {
  iIndexCopyToStart = value;
}

void GlobalIdTableEntry3FNDX::deserialize(QDataStream &ds) {

  ds >> iIndexCopyFromStart;
  ds >> cEntriesToCopy;
  ds >> iIndexCopyToStart;
}

void GlobalIdTableEntry3FNDX::serialize(QDataStream &ds) const {
  ds << iIndexCopyFromStart;
  ds << cEntriesToCopy;
  ds << iIndexCopyToStart;
}

void GlobalIdTableEntry3FNDX::toDebugString(QDebug dbg) const {
  dbg << " GlobalIdTableEntry3FNDX: \n"
      << " iIndexCopyFromStart: " << iIndexCopyFromStart << '\n'
      << " cEntriesToCopy:      " << cEntriesToCopy << '\n'
      << " iIndexCopyToStart:   " << iIndexCopyToStart << '\n';
}
