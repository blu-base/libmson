#include "GlobalIdTableStartFNDX.h"

GlobalIdTableStartFNDX::GlobalIdTableStartFNDX() : reserved{0} {}

quint8 GlobalIdTableStartFNDX::getReserved() const { return reserved; }

void GlobalIdTableStartFNDX::setReserved(const quint8 &value) {
  reserved = value;
}

void GlobalIdTableStartFNDX::deserialize(QDataStream &ds) { ds >> reserved; }

void GlobalIdTableStartFNDX::serialize(QDataStream &ds) const {
  ds << reserved;
}

void GlobalIdTableStartFNDX::toDebugString(QDebug dbg) const {
  dbg << " GloalIdTableStartFNDX: reserved: " << reserved << '\n';
}
