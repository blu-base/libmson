#include "IStreamObject.h"

#include "../StreamObjectHeader.h"
#include "../StreamObjectHeaderEnd.h"

#include <QDebug>

namespace libmson {
namespace fsshttpb {

quint64 IStreamObject::getSizeInFile()
{
  auto cb = strObjBody_cb();
  cb += StreamObjectHeader::getSizeInFile(cbNextHeader(), getType());

  if (isCompound()) {
    cb += StreamObjectHeaderEnd::getSizeInFile(getType());
  }

  return cb;
}

quint64 IStreamObject::getCbNextHeader() { return cbNextHeader(); }

bool IStreamObject::isCompound() const { return compoundType.at(getType()); }

std::vector<IStreamObject_WPtr_t> IStreamObject::getObjects()
{
  std::vector<IStreamObject_WPtr_t> vec{};

  vec.reserve(m_children.size());
  std::transform(
      m_children.cbegin(), m_children.cend(), std::back_inserter(vec),
      [](auto& ptr) { return ptr; });

  return vec;
}

std::vector<IStreamObject_WPtr_t>
IStreamObject::getObjects(StreamObjectType type) const
{
  std::vector<IStreamObject_WPtr_t> vec{};

  std::copy_if(
      m_children.begin(), m_children.end(), std::back_inserter(vec),
      [&](auto& ptr) { return ptr->getType() == type; });

  return vec;
}

void IStreamObject::removeObjects(StreamObjectType type)
{

  auto it = m_children.begin();
  while (it != m_children.end()) {
    if ((*it)->getType() == type) {
      it = m_children.erase(it);
    }
    else {
      ++it;
    }
  }
}

IStreamObject_WPtr_t IStreamObject::at(size_t pos)
{
  if (!isCompound() && size() > pos) {
    return m_children.at(pos);
  }

  return IStreamObject_WPtr_t();
}

bool IStreamObject::isEmpty()
{
  if (!isCompound()) {
    return true;
  }

  return m_children.empty();
}

size_t IStreamObject::size() const
{
  if (!isCompound()) {
    return 0;
  }

  return m_children.size();
}

IStreamObj_It_t IStreamObject::begin()
{
  if (isCompound()) {
    return m_children.begin();
  }

  return m_children.end();
}

IStreamObj_It_t IStreamObject::end() { return m_children.end(); }

void IStreamObject::pop_back()
{
  if (isCompound()) {
    return m_children.pop_back();
  }
}

IStreamObj_const_It_t IStreamObject::cbegin() const
{
  if (isCompound()) {
    return m_children.cbegin();
  }

  return m_children.cend();
}

IStreamObj_const_It_t IStreamObject::cend() const { return m_children.cend(); }

IStreamObj_It_t IStreamObject::erase(IStreamObj_It_t pos)
{
  if (isCompound()) {
    return m_children.erase(pos);
  }

  return m_children.end();
}

void IStreamObject::clear() { m_children.clear(); }


bool IStreamObject::isParsed() const { return m_isParsed; }

bool IStreamObject::isObjectStreamEnd(QDataStream& ds)
{
  if (ds.atEnd()) {
    return true;
  }

  std::array<char, 1> peek;
  ds.device()->peek(peek.data(), 1);

  return (peek[0] & 1u) == 1u;
}

bool IStreamObject::isObjectStreamEnd(StreamObjectType type, QDataStream& ds)
{
  if (ds.atEnd()) {
    return true;
  }

  ds.startTransaction();

  StreamObjectHeaderEnd end;
  ds >> end;

  ds.rollbackTransaction();

  return end.getType() == type;
}

// std::vector<IStreamObject_SPtr_t>
// IStreamObject::parseStreamObjects(QDataStream& ds, StreamObjectType type)
//{
//  std::vector<IStreamObject_SPtr_t> vec;


//  std::array<char, 1> peek;

//  qint64 peeking = ds.device()->peek(peek.data(), 1);
//  while ((static_cast<uint8_t>(peek[0]) & 0x1) != 1) {

//    auto obj = std::make_shared<IStreamObject>();
//    ds >> *obj;

//    vec.push_back(obj);

//    peeking = ds.device()->peek(peek.data(), 1);

//    if (peeking == 0) {
//      qDebug() << "Ran out of bytes";
//      break;
//    }
//  }

//}

void IStreamObject::setIsChanged() { m_isChanged = true; }

bool IStreamObject::isChanged() const { return m_isChanged; }

void IStreamObject::deserialize(QDataStream& ds)
{
  StreamObjectHeader head;
  ds >> head;

  m_cbNxtHd = head.getLength();

  auto curPos = ds.device()->pos();

  if (m_cbNxtHd == 0) {
    if (!(head.getType() == StreamObjectType::ObjectGroupDeclarations ||
          head.getType() == StreamObjectType::ObjectGroupData)) {
      qDebug() << "empty Stream object";
    }
  }
  deserializeStrObj(ds);

  if (isCompound()) {
    StreamObjectHeaderEnd end;
    ds >> end;

    if (head.getType() != end.getType()) {
      qCritical() << "StreamObjectHeaderEnd has not the same type as the "
                     "respective StreamObjectHeader.";
    }
  }
}

void IStreamObject::serialize(QDataStream& ds) const
{
  auto type = getType();

  auto header = StreamObjectHeader(type, cbNextHeader());
  ds << header;

  serializeStrObj(ds);

  if (isCompound()) {
    ds << header.getEnd();
  }
}

} // namespace fsshttpb
} // namespace libmson
