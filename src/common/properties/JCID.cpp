#include "JCID.h"
#include "../helper/Helper.h"

#include <QDataStream>
#include <QDebug>
#include <QString>

quint16 JCID::index() const {
  return (m_value >> JCID_shiftValue) & JCID_relmaskValue;
}

void JCID::setIndex(const quint16 &index) {
  m_value = (m_value & JCID_imaskValue) +
            (static_cast<quint32>(index) << JCID_shiftValue);
}

bool JCID::IsBinary() const {
  return (m_value >> JCID_shiftIsBinary) & JCID_relmaskIsBinary;
}

void JCID::setIsBinary(bool IsBinary) {
  m_value = (m_value & JCID_imaskIsBinary) +
               (static_cast<quint32>(IsBinary) << JCID_shiftIsBinary);
  ;
}

bool JCID::IsPropertySet() const {
  return (m_value >> JCID_shiftIsPropertySet) & JCID_relmaskIsPropertySet;
}

void JCID::setIsPropertySet(bool IsPropertySet) {
  m_value = (m_value & JCID_imaskIsPropertySet) +
                    (static_cast<quint32>(IsPropertySet) << JCID_shiftIsPropertySet);
  ;
}

bool JCID::IsGraphNode() const {
  return (m_value >> JCID_shiftIsGraphNode) & JCID_relmaskIsGraphNode;
}

void JCID::setIsGraphNode(bool IsGraphNode) {
  m_value = (m_value & JCID_imaskIsGraphNode) +
                  (static_cast<quint32>(IsGraphNode) << JCID_shiftIsGraphNode);
  ;
}

bool JCID::IsFileData() const {
  return (m_value >> JCID_shiftIsFileData) & JCID_relmaskIsFileData;
}

void JCID::setIsFileData(bool IsFileData) {
  m_value = (m_value & JCID_imaskIsFileData) +
                 (static_cast<quint32>(IsFileData) << JCID_shiftIsFileData);
  ;
}

bool JCID::IsReadOnly() const {
  return (m_value >> JCID_shiftIsReadOnly) & JCID_relmaskIsReadOnly;
}

void JCID::setIsReadOnly(bool IsReadOnly) {
  m_value = (m_value & JCID_imaskIsReadOnly) +
                 (static_cast<quint32>(IsReadOnly) << JCID_shiftIsReadOnly);
  ;
}

JCIDs JCID::type() const
{
    switch (m_value) {
    case 0x00120001:
        return JCIDs::jcidReadOnlyPersistablePropertyContainerForAuthor;
    case 0x00020001:
        return JCIDs::jcidPersistablePropertyContainerForTOC;
    case 0x00060007:
        return JCIDs::jcidSectionNode;
    case 0x00060008:
        return JCIDs::jcidPageSeriesNode;
    case 0x0006000B:
        return JCIDs::jcidPageNode;
    case 0x0006000C:
        return JCIDs::jcidOutlineNode;
    case 0x0006000D:
        return JCIDs::jcidOutlineElementNode;
    case 0x0006000E:
        return JCIDs::jcidRichTextOENode;
    case 0x00060011:
        return JCIDs::jcidImageNode;
    case 0x00060012:
        return JCIDs::jcidNumberListNode;
    case 0x00060019:
        return JCIDs::jcidOutlineGroup;
    case 0x00060022:
        return JCIDs::jcidTableNode;
    case 0x00060023:
        return JCIDs::jcidTableRowNode;
    case 0x00060024:
        return JCIDs::jcidTableCellNode;
    case 0x0006002C:
        return JCIDs::jcidTitleNode;
    case 0x00020030:
        return JCIDs::jcidPageMetaData;
    case 0x00020031:
        return JCIDs::jcidSectionMetaData;
    case 0x00060035:
        return JCIDs::jcidEmbeddedFileNode;
    case 0x00060037:
        return JCIDs::jcidPageManifestNode;
    case 0x00020038:
        return JCIDs::jcidConflictPageMetaData;
    case 0x0006003C:
        return JCIDs::jcidVersionHistoryContent;
    case 0x0006003D:
        return JCIDs::jcidVersionProxy;
    case 0x00120043:
        return JCIDs::jcidNoteTagSharedDefinitionContainer;
    case 0x00020044:
        return JCIDs::jcidRevisionMetaData;
    case 0x00020046:
        return JCIDs::jcidVersionHistoryMetaData;
    case 0x0012004D:
        return JCIDs::jcidParagraphStyleObject;
    case 0x00000000:
    default:
        return JCIDs::none;
    }
}

QString JCID::typeToString() const
{
    switch (m_value) {
    case 0x00120001:
        return QString("jcidReadOnlyPersistablePropertyContainerForAuthor");
    case 0x00020001:
        return QString("jcidPersistablePropertyContainerForTOC");
    case 0x00060007:
        return QString("jcidSectionNode");
    case 0x00060008:
        return QString("jcidPageSeriesNode");
    case 0x0006000B:
        return QString("jcidPageNode");
    case 0x0006000C:
        return QString("jcidOutlineNode");
    case 0x0006000D:
        return QString("jcidOutlineElementNode");
    case 0x0006000E:
        return QString("jcidRichTextOENode");
    case 0x00060011:
        return QString("jcidImageNode");
    case 0x00060012:
        return QString("jcidNumberListNode");
    case 0x00060019:
        return QString("jcidOutlineGroup");
    case 0x00060022:
        return QString("jcidTableNode");
    case 0x00060023:
        return QString("jcidTableRowNode");
    case 0x00060024:
        return QString("jcidTableCellNode");
    case 0x0006002C:
        return QString("jcidTitleNode");
    case 0x00020030:
        return QString("jcidPageMetaData");
    case 0x00020031:
        return QString("jcidSectionMetaData");
    case 0x00060035:
        return QString("jcidEmbeddedFileNode");
    case 0x00060037:
        return QString("jcidPageManifestNode");
    case 0x00020038:
        return QString("jcidConflictPageMetaData");
    case 0x0006003C:
        return QString("jcidVersionHistoryContent");
    case 0x0006003D:
        return QString("jcidVersionProxy");
    case 0x00120043:
        return QString("jcidNoteTagSharedDefinitionContainer");
    case 0x00020044:
        return QString("jcidRevisionMetaData");
    case 0x00020046:
        return QString("jcidVersionHistoryMetaData");
    case 0x0012004D:
        return QString("jcidParagraphStyleObject");
    case 0x00000000:
    default:
        return QString("none");
    }
}

void JCID::deserialize(QDataStream &ds) { ds >> m_value; }

void JCID::serialize(QDataStream &ds) const { ds << m_value; }

void JCID::toDebugString(QDebug dbg) const {
  dbg << " JCID: index: " << qStringHex(index(), 4)
      << " m_IsBinary: " << IsBinary() << '\n'
      << " m_IsPropertySet: " << IsPropertySet() << '\n'
      << " m_IsGraphNode: " << IsGraphNode() << '\n'
      << " m_IsFileData: " << IsFileData() << '\n'
      << " m_IsReadOnly: " << IsReadOnly() << '\n';
}

JCID::JCID()
    : m_value() {}

void JCID::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("JCID");
  xmlWriter.writeAttribute("type", typeToString());
  xmlWriter.writeAttribute("value", qStringHex(m_value, 8));
  xmlWriter.writeAttribute("index", qStringHex(index(), 4));
  xmlWriter.writeAttribute("isBinary", IsBinary() ? "true" : "false");
  xmlWriter.writeAttribute("IsPropertySet", IsPropertySet() ? "true" : "false");
  xmlWriter.writeAttribute("IsGraphNode", IsGraphNode() ? "true" : "false");
  xmlWriter.writeAttribute("IsFileData", IsFileData() ? "true" : "false");
  xmlWriter.writeAttribute("IsReadOnly", IsReadOnly() ? "true" : "false");

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
