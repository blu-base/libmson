#include "CompactID.h"

#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QString>

#include <math.h>
#include <string>

uint8_t CompactID::getN() const { return n; }

void CompactID::setN(const uint8_t &value) { n = value; }

uint32_t CompactID::getGuidIndex() const { return guidIndex; }

/**
 * @brief CompactID::setGuidIndex
 * @param value
 * @return
 *
 * checks if uint32_t value
 */
bool CompactID::setGuidIndex(const uint32_t &value) {
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
  return n == eguid->getN() && guidIndex < 0xFFFFFF;
}

bool CompactID::isNull() const { return (n == 0) && (guidIndex == 0); }

QByteArray CompactID::toByteArray() const {
  QByteArray raw;

  raw.append(QByteArray::number(n, 16));

  raw.append(QByteArray::number(guidIndex, 16).right(3));

  return raw;
}

QString CompactID::toString() const {
  return QString(QString::fromStdString(std::to_string(guidIndex) + ", " +
                                        std::to_string(n)));
}

QDataStream &operator<<(QDataStream &s, const CompactID &obj) {
  QByteArray bytes = obj.toByteArray();

  if (s.writeRawData(bytes.data(), 4) != 4) {
    s.setStatus(QDataStream::WriteFailed);
  }

  return s;
}

QDataStream &operator>>(QDataStream &s, CompactID &obj) {

  QByteArray bytes(4, Qt::Uninitialized);
  if (s.readRawData(bytes.data(), 4) != 4) {
    s.setStatus(QDataStream::ReadPastEnd);
    return s;
  }

  obj.setN(bytes.at(0));
  obj.setGuidIndex(bytes.right(3).toUInt());

  return s;
}

QDebug operator<<(QDebug dbg, const CompactID &obj) {
  QDebugStateSaver saver(dbg);
  dbg.nospace() << "CompactID(" << obj.toString() << ')';
  return dbg;
}

bool operator==(const CompactID &lhs, const CompactID &rhs) noexcept {
  return lhs.getN() == rhs.getN() && lhs.getGuidIndex() == rhs.getGuidIndex();
}

bool operator!=(const CompactID &lhs, const CompactID &rhs) noexcept {
  return !(lhs == rhs);
}

CompactID::CompactID() : n{0}, guidIndex{0}, eguid{nullptr} {}

CompactID::CompactID(ExtendedGUID *guid) : n{0}, guidIndex{0}, eguid{guid} {}

CompactID::CompactID(const uint8_t n, const uint32_t guidIndex)
    : n{n}, guidIndex{0}, eguid{nullptr} {
  setGuidIndex(guidIndex);
}

CompactID::CompactID(const uint8_t n, const uint32_t guidIndex,
                     ExtendedGUID *guid)
    : n{n}, guidIndex{0}, eguid{guid} {
  setGuidIndex(guidIndex);
}

CompactID::CompactID(const QByteArray &bytes) : n{0}, guidIndex{0} {
  setN(bytes.at(0));
  setGuidIndex(bytes.right(3).toUInt());
}

CompactID::~CompactID() { delete[] eguid; }
