#include "JCID.h"
#include "../helper/Helper.h"
#include <QDataStream>
#include <QDebug>

quint16 JCID::index() const { return m_index; }

void JCID::setIndex(const quint16 &index) { m_index = index; }

bool JCID::IsBinary() const { return m_IsBinary; }

void JCID::setIsBinary(bool IsBinary) { m_IsBinary = IsBinary; }

bool JCID::IsPropertySet() const { return m_IsPropertySet; }

void JCID::setIsPropertySet(bool IsPropertySet) {
  m_IsPropertySet = IsPropertySet;
}

bool JCID::IsGraphNode() const { return m_IsGraphNode; }

void JCID::setIsGraphNode(bool IsGraphNode) { m_IsGraphNode = IsGraphNode; }

bool JCID::IsFileData() const { return m_IsFileData; }

void JCID::setIsFileData(bool IsFileData) { m_IsFileData = IsFileData; }

bool JCID::IsReadOnly() const { return m_IsReadOnly; }

void JCID::setIsReadOnly(bool IsReadOnly) { m_IsReadOnly = IsReadOnly; }

void JCID::deserialize(QDataStream &ds) {
  ds >> m_index;

  quint16 temp;

  ds >> temp;

  m_IsBinary = temp & 0x1;
  m_IsPropertySet = (temp & 0x2) >> 1;
  m_IsGraphNode = (temp & 0x4) >> 2;
  m_IsFileData = (temp & 0x8) >> 3;
  m_IsReadOnly = (temp & 0x10) >> 4;
}

void JCID::serialize(QDataStream &ds) const {

  ds << m_index;

  quint16 temp{0};

  temp += m_IsReadOnly << 4;
  temp += m_IsFileData << 3;
  temp += m_IsGraphNode << 2;
  temp += m_IsPropertySet << 1;
  temp += m_IsBinary;

  ds << temp;
}

void JCID::toDebugString(QDebug dbg) const {
  dbg << " JCID: index: " << qStringHex(m_index, 4)
      << " m_IsBinary: " << m_IsBinary << '\n'
      << " m_IsPropertySet: " << m_IsPropertySet << '\n'
      << " m_IsGraphNode: " << m_IsGraphNode << '\n'
      << " m_IsFileData: " << m_IsFileData << '\n'
      << " m_IsReadOnly: " << m_IsReadOnly << '\n';
}

JCID::JCID()
    : m_index{}, m_IsBinary{false}, m_IsPropertySet{false},
      m_IsGraphNode{false}, m_IsFileData{false}, m_IsReadOnly{true} {}

void JCID::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("JCID");
  xmlWriter.writeAttribute("index", qStringHex(m_index, 4));
  xmlWriter.writeAttribute("isBinary", m_IsBinary ? "true" : "false");
  xmlWriter.writeAttribute("IsPropertySet", m_IsPropertySet ? "true" : "false");
  xmlWriter.writeAttribute("IsGraphNode", m_IsGraphNode ? "true" : "false");
  xmlWriter.writeAttribute("IsFileData", m_IsFileData ? "true" : "false");
  xmlWriter.writeAttribute("IsReadOnly", m_IsReadOnly ? "true" : "false");


  xmlWriter.writeEndElement();
}

QDataStream &operator<<(QDataStream &ds, const JCID &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, JCID &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const JCID &obj) {
  obj.toDebugString(dbg);
  return dbg;
}
