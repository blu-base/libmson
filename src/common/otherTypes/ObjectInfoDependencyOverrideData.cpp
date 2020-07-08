#include "ObjectInfoDependencyOverrideData.h"
#include <QDataStream>
#include <QDebug>
ObjectInfoDependencyOverrideData::ObjectInfoDependencyOverrideData()
    : m_c8BitOverrides(), m_c32BitOverrides(), m_crc() {}

QDataStream &operator<<(QDataStream &ds,
                        const ObjectInfoDependencyOverrideData &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds,
                        ObjectInfoDependencyOverrideData &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const ObjectInfoDependencyOverrideData &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

quint32 ObjectInfoDependencyOverrideData::c8BitOverrides() const {
  return m_c8BitOverrides;
}

void ObjectInfoDependencyOverrideData::setC8BitOverrides(
    const quint32 &c8BitOverrides) {
  m_c8BitOverrides = c8BitOverrides;
}

quint32 ObjectInfoDependencyOverrideData::c32BitOverrides() const {
  return m_c32BitOverrides;
}

void ObjectInfoDependencyOverrideData::setC32BitOverrides(
    const quint32 &c32BitOverrides) {
  m_c32BitOverrides = c32BitOverrides;
}

quint32 ObjectInfoDependencyOverrideData::crc() const { return m_crc; }

void ObjectInfoDependencyOverrideData::setCrc(const quint32 &crc) {
  m_crc = crc;
}

std::vector<ObjectInfoDependencyOverride8>
ObjectInfoDependencyOverrideData::Overrides1() const {
  return m_Overrides1;
}

void ObjectInfoDependencyOverrideData::setOverrides1(
    const std::vector<ObjectInfoDependencyOverride8> &Overrides1) {
  m_Overrides1 = Overrides1;
}

std::vector<ObjectInfoDependencyOverride32>
ObjectInfoDependencyOverrideData::Overrides2() const {
  return m_Overrides2;
}

void ObjectInfoDependencyOverrideData::setOverrides2(
    const std::vector<ObjectInfoDependencyOverride32> &Overrides2) {
  m_Overrides2 = Overrides2;
}

void ObjectInfoDependencyOverrideData::deserialize(QDataStream &ds) {
  ds >> m_c8BitOverrides;
  ds >> m_c32BitOverrides;
  ds >> m_crc;

  ObjectInfoDependencyOverride8 temp8;
  for (size_t i{0}; i < m_c8BitOverrides; i++) {
    ds >> temp8;
    m_Overrides1.push_back(temp8);
  }

  ObjectInfoDependencyOverride32 temp32;
  for (size_t i{0}; i < m_c8BitOverrides; i++) {
    ds >> temp32;
    m_Overrides2.push_back(temp32);
  }
}

void ObjectInfoDependencyOverrideData::serialize(QDataStream &ds) const {
  ds << m_c8BitOverrides;
  ds << m_c32BitOverrides;
  ds << m_crc;

  for (size_t i{0}; i < m_c8BitOverrides; i++) {
    ds << m_Overrides1.at(i);
  }

  for (size_t i{0}; i < m_c8BitOverrides; i++) {
    ds << m_Overrides2.at(i);
  }
}

void ObjectInfoDependencyOverrideData::toDebugString(QDebug dbg) const {}
