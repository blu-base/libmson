#include "ObjectSpaceObjectStreamHeader.h"
#include <QDebug>

namespace libmson {
namespace priv {

quint32 ObjectSpaceObjectStreamHeader::getCount() const { return m_count; }

void ObjectSpaceObjectStreamHeader::setCount(const quint32& count)
{
  if (count > 0xFFFFFF) {
    qWarning() << "ObjectSpaceObjectStreamHeader: count is exciding limit for "
                  "ObjectSpaceObjectStream\n truncating to 24bit width.";
  }

  m_count = count & 0xFFFFFF;
}

bool ObjectSpaceObjectStreamHeader::incrementCount()
{
  if (m_count == 0xFFFFFF) {
    return false;
  }
  else {
    m_count++;
    return true;
  }
}

bool ObjectSpaceObjectStreamHeader::decrementCount()
{
  if (m_count > 0) {
    m_count--;
    return true;
  }
  else {
    return false;
  }
}

bool ObjectSpaceObjectStreamHeader::isExtendedStreamPresent() const
{
  return m_ExtendedStreamsPresent;
}

void ObjectSpaceObjectStreamHeader::setExtendedStreamsPresence(
    const ExtendedStreamPresence& extendedStreamPresence)
{
  m_ExtendedStreamsPresent = static_cast<bool>(extendedStreamPresence);
}

bool ObjectSpaceObjectStreamHeader::isOsidStreamNotPresent() const
{
  return m_OsidStreamNotPresent;
}

void ObjectSpaceObjectStreamHeader::setOsidStreamPresence(
    const OsidStreamPresence& osidStreamPresence)
{
  m_OsidStreamNotPresent = static_cast<bool>(osidStreamPresence);
}


void ObjectSpaceObjectStreamHeader::deserialize(QDataStream& ds)
{
  quint32 composed;
  ds >> composed;

  m_count                  = composed & 0xFFFFFF;
  m_ExtendedStreamsPresent = (composed >> 30) & 0x1;
  m_OsidStreamNotPresent   = (composed >> 31);
}

void ObjectSpaceObjectStreamHeader::serialize(QDataStream& ds) const
{
  quint32 composed = m_count;

  composed += m_OsidStreamNotPresent << 31;
  composed += m_ExtendedStreamsPresent << 30;

  ds << composed;
}


ObjectSpaceObjectStreamHeader::ObjectSpaceObjectStreamHeader()
    : m_count(0), m_OsidStreamNotPresent(true), m_ExtendedStreamsPresent(false)
{
}

ObjectSpaceObjectStreamHeader::ObjectSpaceObjectStreamHeader(
    const OsidStreamPresence& osidStreamPresence,
    const ExtendedStreamPresence& extendedStreamPresence)
    : m_count(0), m_OsidStreamNotPresent(static_cast<bool>(osidStreamPresence)),
      m_ExtendedStreamsPresent(static_cast<bool>(extendedStreamPresence))
{
}

ObjectSpaceObjectStreamHeader::ObjectSpaceObjectStreamHeader(
    const quint32& count, const OsidStreamPresence& osidStreamPresence,
    const ExtendedStreamPresence& extendedStreamPresence)
    : m_count(0), m_OsidStreamNotPresent(static_cast<bool>(osidStreamPresence)),
      m_ExtendedStreamsPresent(static_cast<bool>(extendedStreamPresence))
{
  this->setCount(count);
}

// void ObjectSpaceObjectStreamHeader::toDebugString(QDebug &dbg) const {
//  dbg << "ObjectSpaceObjectStreamHeader:\n"
//      << " count: " << m_count << "\n"
//      << "ExtendedStreamsPresent: " << m_ExtendedStreamsPresent << '\n'
//      << "OsidStreamNotPresent:   " << m_OsidStreamNotPresent << '\n';
//}

// void ObjectSpaceObjectStreamHeader::writeLowLevelXml(
//    QXmlStreamWriter &xmlWriter) const {
//  xmlWriter.writeStartElement("ObjectSpaceObjectStreamHeader");
//  xmlWriter.writeAttribute("count", QString::number(m_count));
//  xmlWriter.writeAttribute("OsidStreamNotPresent",
//                           m_OsidStreamNotPresent ? "True" : "False");
//  xmlWriter.writeAttribute("ExtendedStreamsPresent",
//                           m_ExtendedStreamsPresent ? "True" : "False");
//  xmlWriter.writeEndElement();
//}

} // namespace priv
} // namespace libmson
