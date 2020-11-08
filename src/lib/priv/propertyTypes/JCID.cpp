#include "JCID.h"
#include "../helper/Helper.h"

#include <QDataStream>
#include <QDebug>
#include <QString>

namespace libmson{
namespace priv{

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

JCIDs JCID::type() const {
  return static_cast<JCIDs>(m_value);

  //    switch (m_value) {
  //    case 0x00120001:
  //        return JCIDs::jcidReadOnlyPersistablePropertyContainerForAuthor;
  //    case 0x00020001:
  //        return JCIDs::jcidPersistablePropertyContainerForTOC;
  //    case 0x00060007:
  //        return JCIDs::jcidSectionNode;
  //    case 0x00060008:
  //        return JCIDs::jcidPageSeriesNode;
  //    case 0x0006000B:
  //        return JCIDs::jcidPageNode;
  //    case 0x0006000C:
  //        return JCIDs::jcidOutlineNode;
  //    case 0x0006000D:
  //        return JCIDs::jcidOutlineElementNode;
  //    case 0x0006000E:
  //        return JCIDs::jcidRichTextOENode;
  //    case 0x00060011:
  //        return JCIDs::jcidImageNode;
  //    case 0x00060012:
  //        return JCIDs::jcidNumberListNode;
  //    case 0x00060019:
  //        return JCIDs::jcidOutlineGroup;
  //    case 0x00060022:
  //        return JCIDs::jcidTableNode;
  //    case 0x00060023:
  //        return JCIDs::jcidTableRowNode;
  //    case 0x00060024:
  //        return JCIDs::jcidTableCellNode;
  //    case 0x0006002C:
  //        return JCIDs::jcidTitleNode;
  //    case 0x00020030:
  //        return JCIDs::jcidPageMetaData;
  //    case 0x00020031:
  //        return JCIDs::jcidSectionMetaData;
  //    case 0x00060035:
  //        return JCIDs::jcidEmbeddedFileNode;
  //    case 0x00060037:
  //        return JCIDs::jcidPageManifestNode;
  //    case 0x00020038:
  //        return JCIDs::jcidConflictPageMetaData;
  //    case 0x0006003C:
  //        return JCIDs::jcidVersionHistoryContent;
  //    case 0x0006003D:
  //        return JCIDs::jcidVersionProxy;
  //    case 0x00120043:
  //        return JCIDs::jcidNoteTagSharedDefinitionContainer;
  //    case 0x00020044:
  //        return JCIDs::jcidRevisionMetaData;
  //    case 0x00020046:
  //        return JCIDs::jcidVersionHistoryMetaData;
  //    case 0x0012004D:
  //        return JCIDs::jcidParagraphStyleObject;
  //    case 0x00000000:
  //    default:
  //        return JCIDs::none;
  //    }
}

QString JCID::typeToString() const {

  switch (type()) {
  case JCIDs::jcidReadOnlyPersistablePropertyContainerForAuthor:
    return QString("jcidReadOnlyPersistablePropertyContainerForAuthor");
  case JCIDs::jcidPersistablePropertyContainerForTOC:
    return QString("jcidPersistablePropertyContainerForTOC");
  case JCIDs::jcidSectionNode:
    return QString("jcidSectionNode");
  case JCIDs::jcidPageSeriesNode:
    return QString("jcidPageSeriesNode");
  case JCIDs::jcidPageNode:
    return QString("jcidPageNode");
  case JCIDs::jcidOutlineNode:
    return QString("jcidOutlineNode");
  case JCIDs::jcidOutlineElementNode:
    return QString("jcidOutlineElementNode");
  case JCIDs::jcidRichTextOENode:
    return QString("jcidRichTextOENode");
  case JCIDs::jcidImageNode:
    return QString("jcidImageNode");
  case JCIDs::jcidNumberListNode:
    return QString("jcidNumberListNode");
  case JCIDs::jcidOutlineGroup:
    return QString("jcidOutlineGroup");
  case JCIDs::jcidTableNode:
    return QString("jcidTableNode");
  case JCIDs::jcidTableRowNode:
    return QString("jcidTableRowNode");
  case JCIDs::jcidTableCellNode:
    return QString("jcidTableCellNode");
  case JCIDs::jcidTitleNode:
    return QString("jcidTitleNode");
  case JCIDs::jcidPageMetaData:
    return QString("jcidPageMetaData");
  case JCIDs::jcidSectionMetaData:
    return QString("jcidSectionMetaData");
  case JCIDs::jcidEmbeddedFileNode:
    return QString("jcidEmbeddedFileNode");
  case JCIDs::jcidPageManifestNode:
    return QString("jcidPageManifestNode");
  case JCIDs::jcidConflictPageMetaData:
    return QString("jcidConflictPageMetaData");
  case JCIDs::jcidVersionHistoryContent:
    return QString("jcidVersionHistoryContent");
  case JCIDs::jcidVersionProxy:
    return QString("jcidVersionProxy");
  case JCIDs::jcidNoteTagSharedDefinitionContainer:
    return QString("jcidNoteTagSharedDefinitionContainer");
  case JCIDs::jcidRevisionMetaData:
    return QString("jcidRevisionMetaData");
  case JCIDs::jcidVersionHistoryMetaData:
    return QString("jcidVersionHistoryMetaData");
  case JCIDs::jcidParagraphStyleObject:
    return QString("jcidParagraphStyleObject");

  case JCIDs::undoc_jcidShape:
    return QString("undoc_jcidShape");
  case JCIDs::undoc_jcidDrawingNode:
    return QString("undoc_jcidDrawingNode");
  case JCIDs::undoc_jciddrawingToolData:
    return QString("undoc_jciddrawingToolData");

  case JCIDs::none:
    return QString("none");
  default:
    return QString("unspecified");
  }
}

quint64 JCID::getSizeInFile()
{
  return sizeInFile;
}

void JCID::deserialize(QDataStream &ds) { ds >> m_value; }

void JCID::serialize(QDataStream &ds) const { ds << m_value; }

void JCID::toDebugString(QDebug &dbg) const {
  dbg << " JCID: index: " << qStringHex(index(), 4)
      << " m_IsBinary: " << IsBinary() << '\n'
      << " m_IsPropertySet: " << IsPropertySet() << '\n'
      << " m_IsGraphNode: " << IsGraphNode() << '\n'
      << " m_IsFileData: " << IsFileData() << '\n'
      << " m_IsReadOnly: " << IsReadOnly() << '\n';
}

JCID::JCID() : m_value() {}

void JCID::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
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

} //namespace priv
} // namespace libmson
