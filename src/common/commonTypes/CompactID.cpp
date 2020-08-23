#include "CompactID.h"

#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QString>

#include <math.h>
#include <string>

#include "../helper/Helper.h"

quint8 CompactID::getN() const { return m_n; }

void CompactID::setN(const quint8 &value) { m_n = value; }

quint32 CompactID::getGuidIndex() const { return guidIndex; }

/**
 * @brief CompactID::setGuidIndex
 * @param value
 * @return
 *
 * checks if uint32_t value
 */
bool CompactID::setGuidIndex(const quint32 &value) {
  if (value >= 0xFFFFFF) {
    return false;
  } else {
    guidIndex = value;
    return true;
  }
}

ExtendedGUID *CompactID::getExtendedGUID() const { return eguid; }

void CompactID::setExtendedGUID(ExtendedGUID *const guid) { eguid = guid; }

bool CompactID::isValid() const {
  return m_n == eguid->getN() && guidIndex < 0xFFFFFF;
}

bool CompactID::isNull() const { return (m_n == 0) && (guidIndex == 0); }

QByteArray CompactID::toByteArray() const {
  QByteArray raw;

  raw.append(QByteArray::number(m_n, 16));

  raw.append(QByteArray::number(guidIndex, 16).right(3));

  return raw;
}

QString CompactID::toString() const {
  return QString(QString::fromStdString(std::to_string(guidIndex) + ", " +
                                        std::to_string(m_n)));
}

void CompactID::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("CompactID");
  xmlWriter.writeAttribute("guidIndex", qStringHex(guidIndex, 8));
  xmlWriter.writeAttribute("n", qStringHex(m_n, 2));
  xmlWriter.writeEndElement();
}

QDataStream &operator<<(QDataStream &ds, const CompactID &obj) {

  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, CompactID &obj) {
  ds.setByteOrder(QDataStream::LittleEndian);

  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const CompactID &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

void CompactID::toDebugString(QDebug dbg) const {
  QDebugStateSaver saver(dbg);
  dbg.nospace() << "CompactID(" << toString() << ')';
}

void CompactID::deserialize(QDataStream &ds) {
  quint32 temp{};

  ds >> temp;

  m_n = static_cast<quint8>(temp & 0xFF);

  guidIndex = temp >> 8;
}

void CompactID::serialize(QDataStream &ds) const {
  quint32 temp{};

  temp += m_n;
  temp += guidIndex << 8;

  ds << temp;
}


bool operator==(const CompactID &lhs, const CompactID &rhs) noexcept {
  return lhs.getN() == rhs.getN() && lhs.getGuidIndex() == rhs.getGuidIndex();
}

bool operator!=(const CompactID &lhs, const CompactID &rhs) noexcept {
  return !(lhs == rhs);
}

CompactID::CompactID() : m_n{0}, guidIndex{0}, eguid{nullptr} {}

CompactID::CompactID(ExtendedGUID *guid) : m_n{0}, guidIndex{0}, eguid{guid} {}

CompactID::CompactID(const quint8 n, const quint32 guidIndex)
    : m_n{n}, guidIndex{0}, eguid{nullptr} {
  setGuidIndex(guidIndex);
}

CompactID::CompactID(const quint8 n, const quint32 guidIndex,
                     ExtendedGUID *guid)
    : m_n{n}, guidIndex{0}, eguid{guid} {
  setGuidIndex(guidIndex);
}

CompactID::CompactID(const QByteArray &bytes) : m_n{0}, guidIndex{0} {
  setN(bytes.at(0));
  setGuidIndex(bytes.right(3).toUInt());
}

CompactID::~CompactID() { delete[] eguid; }
