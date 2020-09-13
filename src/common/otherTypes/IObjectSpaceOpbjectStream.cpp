#include "IObjectSpaceOpbjectStream.h"

#include "ObjectSpaceObjectStreamHeader.h"

#include <algorithm>

#include <QDataStream>
#include <QDebug>

namespace MSONcommon {

ObjectSpaceObjectStreamHeader IObjectSpaceOpbjectStream::header() const {
  return m_header;
}

void IObjectSpaceOpbjectStream::setHeader(
    const ObjectSpaceObjectStreamHeader &header) {
  m_header = header;
}

std::vector<CompactID> IObjectSpaceOpbjectStream::body() const {
  return m_body;
}

void IObjectSpaceOpbjectStream::setBody(const std::vector<CompactID> &body) {
  m_body = body;
}

void IObjectSpaceOpbjectStream::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  //    xmlWriter.writeStartElement("IObjectSpaceOpbjectStream");
  xmlWriter << m_header;

  xmlWriter.writeStartElement("CompactIDs");
  for (const auto &entry : m_body) {
    xmlWriter << entry;
  }
  xmlWriter.writeEndElement();
  //    xmlWriter.writeEndElement();
}

bool IObjectSpaceOpbjectStream::pushbackToBody(const CompactID &entry) {
  if (m_header.count() < 0xFFFFFF) {
    m_body.push_back(entry);
    m_header.incrementCount();
    return true;
  } else {
    return false;
  }
}

bool IObjectSpaceOpbjectStream::removeIdFromBody(const CompactID &entry) {
  if (m_body.empty()) {
    return false;
  }

  auto pos = std::find(m_body.begin(), m_body.end(), entry);

  if (pos != m_body.end()) {
    m_body.erase(pos);
    m_header.decrementCount();
    return true;
  } else {
    return false;
  }
}

bool IObjectSpaceOpbjectStream::removeIdFromBody(const quint32 &position) {
  if (m_body.size() > position) {
    m_body.erase(m_body.begin() + position);
    return true;
  } else {
    return false;
  }
}

qint32 IObjectSpaceOpbjectStream::positionOfIdInBody(const CompactID &entry) {
  if (m_body.empty()) {
    return -1;
  }
  auto pos = std::find(m_body.begin(), m_body.end(), entry);

  if (pos != m_body.end()) {
    return std::distance(m_body.begin(), pos);
  } else {
    return -1;
  }
}

bool IObjectSpaceOpbjectStream::isIdInBody(const CompactID &entry) {
  if (m_body.empty()) {
    return false;
  }
  auto pos = std::find(m_body.begin(), m_body.end(), entry);

  if (pos != m_body.end()) {
    return true;
  } else {
    return false;
  }
}

IObjectSpaceOpbjectStream::IObjectSpaceOpbjectStream() : m_header(), m_body() {}

IObjectSpaceOpbjectStream::IObjectSpaceOpbjectStream(
    const ObjectSpaceObjectStreamHeader::OsidStreamPresence &osidStreamPresence,
    const ObjectSpaceObjectStreamHeader::ExtendedStreamPresence
        &extendedStreamPresence)
    : m_header(osidStreamPresence, extendedStreamPresence), m_body() {}

IObjectSpaceOpbjectStream::~IObjectSpaceOpbjectStream() {}

void IObjectSpaceOpbjectStream::deserialize(QDataStream &ds) {
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

void IObjectSpaceOpbjectStream::serialize(QDataStream &ds) const {
  ds << m_header;

  for (quint32 i{0}; i < m_header.count(); i++) {
    ds << m_body[i];
  }
}

void IObjectSpaceOpbjectStream::toDebugString(QDebug &dbg) const {

  dbg << "ObjectSpaceOpbjectStream:\n";
  dbg << m_header;

  for (quint32 i(0); i < m_body.size(); i++) {
    dbg << m_body[i];
  }
}

} // namespace MSONcommon
