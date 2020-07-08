#include "GlobalIdTableEntryFNDX.h"

GlobalIdTableEntryFNDX::GlobalIdTableEntryFNDX() : index{0}, guid() {}

QUuid GlobalIdTableEntryFNDX::getGuid() const { return guid; }

void GlobalIdTableEntryFNDX::setGuid(const QUuid &value) { guid = value; }

quint32 GlobalIdTableEntryFNDX::getIndex() const { return index; }

void GlobalIdTableEntryFNDX::setIndex(const quint32 &value) { index = value; }

void GlobalIdTableEntryFNDX::deserialize(QDataStream &ds) {
  ds >> index;
  ds >> guid;
}

void GlobalIdTableEntryFNDX::serialize(QDataStream &ds) const {
  ds << index;
  ds << guid;
}

void GlobalIdTableEntryFNDX::toDebugString(QDebug dbg) const {
  dbg << " GlobalIdTableEntryFNDX: \n"
      << " Index: " << index << '\n'
      << " GUID:  " << guid << '\n';
}
