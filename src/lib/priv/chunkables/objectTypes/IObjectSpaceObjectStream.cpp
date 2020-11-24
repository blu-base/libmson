#include "IObjectSpaceObjectStream.h"
#include <algorithm>


namespace libmson {
namespace priv {

ObjectSpaceObjectStreamHeader IObjectSpaceObjectStream::header() const
{
  return m_header;
}

void IObjectSpaceObjectStream::setHeader(
    const ObjectSpaceObjectStreamHeader& header)
{
  m_header = header;
}

std::vector<CompactID> IObjectSpaceObjectStream::body() const { return m_body; }

void IObjectSpaceObjectStream::setBody(const std::vector<CompactID>& body)
{
  m_body = body;
}


bool IObjectSpaceObjectStream::pushbackToBody(const CompactID& entry)
{
  if (m_header.count() < 0xFFFFFF) {
    m_body.push_back(entry);
    m_header.incrementCount();
    return true;
  }
  else {
    return false;
  }
}

bool IObjectSpaceObjectStream::removeIdFromBody(const CompactID& entry)
{
  if (m_body.empty()) {
    return false;
  }

  auto pos = std::find(m_body.begin(), m_body.end(), entry);

  if (pos != m_body.end()) {
    m_body.erase(pos);
    m_header.decrementCount();
    return true;
  }
  else {
    return false;
  }
}

bool IObjectSpaceObjectStream::removeIdFromBody(const quint32& position)
{
  if (m_body.size() > position) {
    m_body.erase(m_body.begin() + position);
    return true;
  }
  else {
    return false;
  }
}

qint32 IObjectSpaceObjectStream::positionOfIdInBody(const CompactID& entry)
{
  if (m_body.empty()) {
    return -1;
  }
  auto pos = std::find(m_body.begin(), m_body.end(), entry);

  if (pos != m_body.end()) {
    return std::distance(m_body.begin(), pos);
  }
  else {
    return -1;
  }
}

bool IObjectSpaceObjectStream::isIdInBody(const CompactID& entry)
{
  if (m_body.empty()) {
    return false;
  }
  auto pos = std::find(m_body.begin(), m_body.end(), entry);

  if (pos != m_body.end()) {
    return true;
  }
  else {
    return false;
  }
}

const quint64 IObjectSpaceObjectStream::sizeInFileBase =
    ObjectSpaceObjectStreamHeader::getSizeInFile();

quint64 IObjectSpaceObjectStream::getSizeInFile() const
{
  return sizeInFileBase + m_header.count() * CompactID::getSizeInFile();
}

IObjectSpaceObjectStream::IObjectSpaceObjectStream() : m_header(), m_body() {}

IObjectSpaceObjectStream::IObjectSpaceObjectStream(
    const ObjectSpaceObjectStreamHeader::OsidStreamPresence& osidStreamPresence,
    const ObjectSpaceObjectStreamHeader::ExtendedStreamPresence&
        extendedStreamPresence)
    : m_header(osidStreamPresence, extendedStreamPresence), m_body()
{
}

IObjectSpaceObjectStream::~IObjectSpaceObjectStream() {}

void IObjectSpaceObjectStream::deserialize(QDataStream& ds)
{
  ds >> m_header;

  std::vector<CompactID> ids{};
  ids.reserve(m_header.count());

  for (quint32 i{0}; i < m_header.count(); i++) {
    CompactID entry;
    ds >> entry;
    ids.push_back(entry);
  }
  m_body = ids;
}

void IObjectSpaceObjectStream::serialize(QDataStream& ds) const
{
  /// \todo update header count from contents of m_bofy
  ds << m_header;

  for (quint32 i{0}; i < m_header.count(); i++) {
    ds << m_body[i];
  }
}


// void IObjectSpaceObjectStream::writeLowLevelXml(
//    QXmlStreamWriter &xmlWriter) const {
//  //    xmlWriter.writeStartElement("IObjectSpaceObjectStream");
//  xmlWriter << m_header;

//  xmlWriter.writeStartElement("CompactIDs");
//  for (const auto &entry : m_body) {
//    xmlWriter << entry;
//  }
//  xmlWriter.writeEndElement();
//  //    xmlWriter.writeEndElement();
//}

// void IObjectSpaceObjectStream::toDebugString(QDebug &dbg) const {

//  dbg << "ObjectSpaceOpbjectStream:\n";
//  dbg << m_header;

//  for (quint32 i(0); i < m_body.size(); i++) {
//    dbg << m_body[i];
//  }
//}

} // namespace priv
} // namespace libmson
