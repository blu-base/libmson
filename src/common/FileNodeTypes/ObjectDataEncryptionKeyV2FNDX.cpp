#include "ObjectDataEncryptionKeyV2FNDX.h"

#include "../helper/Helper.h"

ObjectDataEncryptionKeyV2FNDX::ObjectDataEncryptionKeyV2FNDX(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : m_ref(stpFormat, cbFormat), m_header(), m_footer() {}
ObjectDataEncryptionKeyV2FNDX::ObjectDataEncryptionKeyV2FNDX(quint8 stpFormat,
                                                             quint8 cbFormat)
    : m_ref(stpFormat, cbFormat), m_header(), m_footer() {}

QByteArray ObjectDataEncryptionKeyV2FNDX::getEncryptionData() const {
  return m_EncryptionData;
}

void ObjectDataEncryptionKeyV2FNDX::setEncryptionData(const QByteArray &value) {
  m_EncryptionData = value;
}

quint64 ObjectDataEncryptionKeyV2FNDX::getFooter() const { return m_footer; }

void ObjectDataEncryptionKeyV2FNDX::setFooter(const quint64 &value) {
  m_footer = value;
}

quint64 ObjectDataEncryptionKeyV2FNDX::getHeader() const { return m_header; }

void ObjectDataEncryptionKeyV2FNDX::setHeader(const quint64 &value) {
  m_header = value;
}

FileNodeChunkReference ObjectDataEncryptionKeyV2FNDX::getRef() const {
  return m_ref;
}

void ObjectDataEncryptionKeyV2FNDX::setRef(
    const FileNodeChunkReference &value) {
  m_ref = value;
}

/**
 * @brief ObjectDataEncryptionKeyV2FNDX::deserialize
 * @param ds
 *
 * \todo there is probably an error here
 */
void ObjectDataEncryptionKeyV2FNDX::deserialize(QDataStream &ds) {
  ds >> m_ref;

  quint64 currentloc = ds.device()->pos();

  ds.device()->seek(m_ref.stp());
  ds >> m_header;
  /// \todo read data chunk
  m_EncryptionData = ds.device()->read(m_ref.cb() - 16);
  ds >> m_footer;

  ds.device()->seek(currentloc);
}

/**
 * @brief ObjectDataEncryptionKeyV2FNDX::serialize
 * @param ds
 *
 * \todo figure out when encrypted data should be stored, currently
 * unimplemented
 */
void ObjectDataEncryptionKeyV2FNDX::serialize(QDataStream &ds) const {
  ds << m_ref;
}

void ObjectDataEncryptionKeyV2FNDX::toDebugString(QDebug dbg) const {
  dbg << " ObjectDataEncryptionKeyV2FNDX:\n"
      << " Ref: " << m_ref << '\n';
}

void ObjectDataEncryptionKeyV2FNDX::generateXml(
    QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ObjectDataEncryptionKeyV2FNDX");

  xmlWriter.writeAttribute("header", qStringHex(m_header, 16));
  xmlWriter.writeAttribute("footer", qStringHex(m_header, 16));

  m_ref.generateXml(xmlWriter);

  xmlWriter.writeStartElement("m_EncryptionData");
  xmlWriter.writeCDATA(m_EncryptionData);
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();
}
