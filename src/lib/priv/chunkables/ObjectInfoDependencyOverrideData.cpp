#include "ObjectInfoDependencyOverrideData.h"

namespace libmson {
namespace priv {

ObjectInfoDependencyOverrideData::ObjectInfoDependencyOverrideData(
    const quint64 initialStp, const quint64 initialCb)
    : Chunkable(initialStp, initialCb), m_c8BitOverrides(), m_c32BitOverrides(),
      m_crc()
{
}


quint32 ObjectInfoDependencyOverrideData::getC8BitOverrides() const
{
  return m_c8BitOverrides;
}

void ObjectInfoDependencyOverrideData::setC8BitOverrides(
    const quint32& c8BitOverrides)
{
  m_isChanged      = true;
  m_c8BitOverrides = c8BitOverrides;
}

quint32 ObjectInfoDependencyOverrideData::getC32BitOverrides() const
{
  return m_c32BitOverrides;
}

void ObjectInfoDependencyOverrideData::setC32BitOverrides(
    const quint32& c32BitOverrides)
{
  m_isChanged       = true;
  m_c32BitOverrides = c32BitOverrides;
}

quint32 ObjectInfoDependencyOverrideData::getCrc() const { return m_crc; }

void ObjectInfoDependencyOverrideData::setCrc(const quint32& crc)
{
  m_isChanged = true;
  m_crc       = crc;
}

std::vector<ObjectInfoDependencyOverride8>
ObjectInfoDependencyOverrideData::getOverrides1() const
{
  return m_Overrides1;
}

void ObjectInfoDependencyOverrideData::setOverrides1(
    const std::vector<ObjectInfoDependencyOverride8>& Overrides1)
{
  m_isChanged  = true;
  m_Overrides1 = Overrides1;
}

std::vector<ObjectInfoDependencyOverride32>
ObjectInfoDependencyOverrideData::getOverrides2() const
{
  return m_Overrides2;
}

void ObjectInfoDependencyOverrideData::setOverrides2(
    const std::vector<ObjectInfoDependencyOverride32>& Overrides2)
{
  m_isChanged  = true;
  m_Overrides2 = Overrides2;
}

const quint64 ObjectInfoDependencyOverrideData::sizeInFileBase = 12;

quint64 ObjectInfoDependencyOverrideData::getSizeInFile() const
{
  return sizeInFileBase +
         m_c8BitOverrides * ObjectInfoDependencyOverride8::sizeInFile +
         m_c32BitOverrides * ObjectInfoDependencyOverride32::sizeInFile;
}

void ObjectInfoDependencyOverrideData::deserialize(QDataStream& ds)
{
  ds >> m_c8BitOverrides;
  ds >> m_c32BitOverrides;
  ds >> m_crc;

  ObjectInfoDependencyOverride8 temp8;
  for (size_t i{0}; i < m_c8BitOverrides; i++) {
    ds >> temp8;
    m_Overrides1.push_back(temp8);
  }

  ObjectInfoDependencyOverride32 temp32;
  for (size_t i{0}; i < m_c32BitOverrides; i++) {
    ds >> temp32;
    m_Overrides2.push_back(temp32);
  }
}

void ObjectInfoDependencyOverrideData::serialize(QDataStream& ds) const
{
  ds << m_c8BitOverrides;
  ds << m_c32BitOverrides;
  ds << m_crc;

  for (size_t i{0}; i < m_c8BitOverrides; i++) {
    ds << m_Overrides1.at(i);
  }

  for (size_t i{0}; i < m_c32BitOverrides; i++) {
    ds << m_Overrides2.at(i);
  }
}

quint64 libmson::priv::ObjectInfoDependencyOverrideData::cb() const
{
  return getSizeInFile();
}

RevisionStoreChunkType ObjectInfoDependencyOverrideData::getType() const
{
  return RevisionStoreChunkType::ObjectInfoDependencyOverrideData;
}

} // namespace priv
} // namespace libmson
