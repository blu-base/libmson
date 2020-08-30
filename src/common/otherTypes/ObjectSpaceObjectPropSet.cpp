#include "ObjectSpaceObjectPropSet.h"

ObjectSpaceObjectPropSet::ObjectSpaceObjectPropSet() {}

ObjectSpaceObjectPropSet::ObjectSpaceObjectPropSet(
    QDataStream &ds, const FileNodeChunkReference &ref) {
  quint64 currentLocation = ds.device()->pos();

  ds.device()->seek(ref.stp());
  deserialize(ds);

  ds.device()->seek(currentLocation);
}

QDataStream &operator<<(QDataStream &ds, const ObjectSpaceObjectPropSet &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, ObjectSpaceObjectPropSet &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const ObjectSpaceObjectPropSet &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

ObjectSpaceObjectStreamOfOIDs ObjectSpaceObjectPropSet::OIDs() const {
  return m_OIDs;
}

void ObjectSpaceObjectPropSet::setOIDs(
    const ObjectSpaceObjectStreamOfOIDs &OIDs) {
  m_OIDs = OIDs;
}

ObjectSpaceObjectStreamOfOSIDs ObjectSpaceObjectPropSet::OSIDs() const {
  return m_OSIDs;
}

void ObjectSpaceObjectPropSet::setOSIDs(
    const ObjectSpaceObjectStreamOfOSIDs &OSIDs) {
  m_OSIDs = OSIDs;
}

ObjectSpaceObjectStreamOfContextIDs
ObjectSpaceObjectPropSet::ContextIDs() const {
  return m_ContextIDs;
}

void ObjectSpaceObjectPropSet::setContextIDs(
    const ObjectSpaceObjectStreamOfContextIDs &ContextIDs) {
  m_ContextIDs = ContextIDs;
}

PropertySet ObjectSpaceObjectPropSet::body() const { return m_body; }

void ObjectSpaceObjectPropSet::setBody(const PropertySet &body) {
  m_body = body;
}

void ObjectSpaceObjectPropSet::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ObjectSpaceObjectPropSet");
  xmlWriter.writeAttribute("paddingLength", QString::number(m_paddingLength));

  xmlWriter.writeStartElement("ObjectSpaceObjectStreamOfOIDs");
  if (m_OIDs.header().count() > 0) {
    m_OIDs.generateXml(xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("ObjectSpaceObjectStreamOfOSIDs");
  if (m_OSIDs.header().count() > 0) {
    m_OSIDs.generateXml(xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("ObjectSpaceObjectStreamOfContextIDs");
  if (m_ContextIDs.header().count() > 0) {
    m_ContextIDs.generateXml(xmlWriter);
  }
  xmlWriter.writeEndElement();

  m_body.generateXml(xmlWriter);

  xmlWriter.writeEndElement();
}

void ObjectSpaceObjectPropSet::deserialize(QDataStream &ds) {
  quint64 propSetstart = ds.device()->pos();
  ds >> m_OIDs;

  if (m_OIDs.header().OsidStream_isNotPresent() == false) {
    ds >> m_OSIDs;

    if (m_OSIDs.header().ExtendedStream_isPresent() == true) {
      ds >> m_ContextIDs;
    }
  }
  ds >> m_body;

  //
  m_paddingLength = 8 - (ds.device()->pos() - propSetstart) % 8;

  ds.skipRawData(m_paddingLength);
}

void ObjectSpaceObjectPropSet::serialize(QDataStream &ds) const {
  ds << m_OIDs;
  if (m_OIDs.header().OsidStream_isNotPresent() == false) {
    ds << m_OSIDs;

    if (m_OSIDs.header().ExtendedStream_isPresent() == true) {
      ds << m_ContextIDs;
    }
  }
  ds << m_body;

  QByteArray padding;

  ds << padding.append('\0', m_paddingLength);
}

void ObjectSpaceObjectPropSet::toDebugString(QDebug dbg) const {
  dbg << "ObjectSpaceObjectPropSet:\n";
  dbg << m_OIDs;

  if (m_OIDs.header().OsidStream_isNotPresent() == false) {
    dbg << m_OSIDs;

    if (m_OSIDs.header().ExtendedStream_isPresent() == true) {
      dbg << m_ContextIDs;
    }
  }
}
