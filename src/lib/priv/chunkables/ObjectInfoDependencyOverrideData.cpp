#include "ObjectInfoDependencyOverrideData.h"

namespace libmson {
namespace priv {

ObjectInfoDependencyOverrideData::ObjectInfoDependencyOverrideData(
    const quint64 initialStp, const quint64 initialCb)
    : Chunkable(initialStp, initialCb), m_c8BitOverrides(), m_c32BitOverrides(),
      m_crc()
{
}


quint32 ObjectInfoDependencyOverrideData::c8BitOverrides() const
{
  return m_c8BitOverrides;
}

void ObjectInfoDependencyOverrideData::setC8BitOverrides(
    const quint32& c8BitOverrides)
{
  m_isChanged      = true;
  m_c8BitOverrides = c8BitOverrides;
}

quint32 ObjectInfoDependencyOverrideData::c32BitOverrides() const
{
  return m_c32BitOverrides;
}

void ObjectInfoDependencyOverrideData::setC32BitOverrides(
    const quint32& c32BitOverrides)
{
  m_isChanged       = true;
  m_c32BitOverrides = c32BitOverrides;
}

quint32 ObjectInfoDependencyOverrideData::crc() const { return m_crc; }

void ObjectInfoDependencyOverrideData::setCrc(const quint32& crc)
{
  m_isChanged = true;
  m_crc       = crc;
}

std::vector<ObjectInfoDependencyOverride8>
ObjectInfoDependencyOverrideData::Overrides1() const
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
ObjectInfoDependencyOverrideData::Overrides2() const
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

// void ObjectInfoDependencyOverrideData::toDebugString(QDebug &dbg) const {}

// void ObjectInfoDependencyOverrideData::writeLowLevelXml(
//    QXmlStreamWriter &xmlWriter) const {
//  xmlWriter.writeStartElement("ObjectInfoDependencyOverrideData");

//  xmlWriter.writeStartElement("c8BitOverrides");
//  xmlWriter.writeCharacters(QString::number(m_c8BitOverrides));
//  xmlWriter.writeEndElement();

//  xmlWriter.writeStartElement("c32BitOverrides");
//  xmlWriter.writeCharacters(QString::number(m_c32BitOverrides));
//  xmlWriter.writeEndElement();

//  xmlWriter.writeStartElement("crc");
//  xmlWriter.writeCharacters(qStringHex(m_crc, 8));
//  xmlWriter.writeEndElement();

//  xmlWriter.writeStartElement("Overrides1");
//  for (auto entry : m_Overrides1) {
//    xmlWriter << entry;
//  }
//  xmlWriter.writeEndElement();

//  xmlWriter.writeStartElement("Overrides2");
//  for (auto entry : m_Overrides1) {
//    xmlWriter << entry;
//  }
//  xmlWriter.writeEndElement();

//  xmlWriter.writeEndElement();
//}

} // namespace priv
} // namespace libmson
