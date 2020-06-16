#include "GlobalIdTableEntry2FNDX.h"

GlobalIdTableEntry2FNDX::GlobalIdTableEntry2FNDX()
    : iIndexMapFrom{0}, iIndexMapTo{0} {}

quint32 GlobalIdTableEntry2FNDX::getIIndexMapFrom() const {
  return iIndexMapFrom;
}

void GlobalIdTableEntry2FNDX::setIIndexMapFrom(const quint32 &value) {
  iIndexMapFrom = value;
}

quint32 GlobalIdTableEntry2FNDX::getIIndexMapTo() const { return iIndexMapTo; }

void GlobalIdTableEntry2FNDX::setIIndexMapTo(const quint32 &value) {
  iIndexMapTo = value;
}

void GlobalIdTableEntry2FNDX::deserialize(QDataStream &ds) {
  ds >> iIndexMapFrom;
  ds >> iIndexMapTo;
}

void GlobalIdTableEntry2FNDX::serialize(QDataStream &ds) const {
  ds << iIndexMapFrom;
  ds << iIndexMapTo;
}

void GlobalIdTableEntry2FNDX::toDebugString(QDebug dbg) const {
  dbg << "GlobalIdTableEntry2FNDX: \n"
      << "iIndexMapFrom: " << iIndexMapFrom << " iIndexMapTo: " << iIndexMapTo
      << '\n';
}
