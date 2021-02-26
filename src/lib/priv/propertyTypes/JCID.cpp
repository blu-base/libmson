#include "JCID.h"
#include "../utils/Helper.h"

#include <QString>

namespace libmson {
namespace priv {

quint16 JCID::index() const
{
  return (m_value >> JCID_shiftValue) & JCID_relmaskValue;
}

void JCID::setIndex(const quint16& index)
{
  m_value = (m_value & JCID_imaskValue) +
            (static_cast<quint32>(index) << JCID_shiftValue);
}

bool JCID::IsBinary() const
{
  return (m_value >> JCID_shiftIsBinary) & JCID_relmaskIsBinary;
}

void JCID::setIsBinary(bool IsBinary)
{
  m_value = (m_value & JCID_imaskIsBinary) +
            (static_cast<quint32>(IsBinary) << JCID_shiftIsBinary);
  ;
}

bool JCID::IsPropertySet() const
{
  return (m_value >> JCID_shiftIsPropertySet) & JCID_relmaskIsPropertySet;
}

void JCID::setIsPropertySet(bool IsPropertySet)
{
  m_value = (m_value & JCID_imaskIsPropertySet) +
            (static_cast<quint32>(IsPropertySet) << JCID_shiftIsPropertySet);
  ;
}

bool JCID::IsGraphNode() const
{
  return (m_value >> JCID_shiftIsGraphNode) & JCID_relmaskIsGraphNode;
}

void JCID::setIsGraphNode(bool IsGraphNode)
{
  m_value = (m_value & JCID_imaskIsGraphNode) +
            (static_cast<quint32>(IsGraphNode) << JCID_shiftIsGraphNode);
  ;
}

bool JCID::IsFileData() const
{
  return (m_value >> JCID_shiftIsFileData) & JCID_relmaskIsFileData;
}

void JCID::setIsFileData(bool IsFileData)
{
  m_value = (m_value & JCID_imaskIsFileData) +
            (static_cast<quint32>(IsFileData) << JCID_shiftIsFileData);
  ;
}

bool JCID::IsReadOnly() const
{
  return (m_value >> JCID_shiftIsReadOnly) & JCID_relmaskIsReadOnly;
}

void JCID::setIsReadOnly(bool IsReadOnly)
{
  m_value = (m_value & JCID_imaskIsReadOnly) +
            (static_cast<quint32>(IsReadOnly) << JCID_shiftIsReadOnly);
  ;
}

JCIDs JCID::type() const { return static_cast<JCIDs>(m_value); }

QString JCID::typeToString() const
{

  switch (type()) {
  case JCIDs::jcidReadOnlyPersistablePropertyContainerForAuthor:
    return QStringLiteral("jcidReadOnlyPersistablePropertyContainerForAuthor");
  case JCIDs::jcidPersistablePropertyContainerForTOC:
    return QStringLiteral("jcidPersistablePropertyContainerForTOC");
  case JCIDs::jcidSectionNode:
    return QStringLiteral("jcidSectionNode");
  case JCIDs::jcidPageSeriesNode:
    return QStringLiteral("jcidPageSeriesNode");
  case JCIDs::jcidPageNode:
    return QStringLiteral("jcidPageNode");
  case JCIDs::jcidOutlineNode:
    return QStringLiteral("jcidOutlineNode");
  case JCIDs::jcidOutlineElementNode:
    return QStringLiteral("jcidOutlineElementNode");
  case JCIDs::jcidRichTextOENode:
    return QStringLiteral("jcidRichTextOENode");
  case JCIDs::jcidImageNode:
    return QStringLiteral("jcidImageNode");
  case JCIDs::jcidNumberListNode:
    return QStringLiteral("jcidNumberListNode");
  case JCIDs::jcidOutlineGroup:
    return QStringLiteral("jcidOutlineGroup");
  case JCIDs::jcidTableNode:
    return QStringLiteral("jcidTableNode");
  case JCIDs::jcidTableRowNode:
    return QStringLiteral("jcidTableRowNode");
  case JCIDs::jcidTableCellNode:
    return QStringLiteral("jcidTableCellNode");
  case JCIDs::jcidTitleNode:
    return QStringLiteral("jcidTitleNode");
  case JCIDs::jcidPageMetaData:
    return QStringLiteral("jcidPageMetaData");
  case JCIDs::jcidSectionMetaData:
    return QStringLiteral("jcidSectionMetaData");
  case JCIDs::jcidEmbeddedFileNode:
    return QStringLiteral("jcidEmbeddedFileNode");
  case JCIDs::jcidPageManifestNode:
    return QStringLiteral("jcidPageManifestNode");
  case JCIDs::jcidConflictPageMetaData:
    return QStringLiteral("jcidConflictPageMetaData");
  case JCIDs::jcidVersionHistoryContent:
    return QStringLiteral("jcidVersionHistoryContent");
  case JCIDs::jcidVersionProxy:
    return QStringLiteral("jcidVersionProxy");
  case JCIDs::jcidNoteTagSharedDefinitionContainer:
    return QStringLiteral("jcidNoteTagSharedDefinitionContainer");
  case JCIDs::jcidRevisionMetaData:
    return QStringLiteral("jcidRevisionMetaData");
  case JCIDs::jcidVersionHistoryMetaData:
    return QStringLiteral("jcidVersionHistoryMetaData");
  case JCIDs::jcidParagraphStyleObject:
    return QStringLiteral("jcidParagraphStyleObject");

  case JCIDs::jcidInkContainer:
    return QStringLiteral("jcidInkContainer");
  case JCIDs::jcidInkNode:
    return QStringLiteral("jcidInkNode");
  case JCIDs::jcidInkToolProperties:
    return QStringLiteral("jcidInkToolProperties");

  case JCIDs::none:
    return QStringLiteral("none");
  default:
    return QStringLiteral("unspecified");
  }
}

JCID::JCID() : m_value() {}

quint64 JCID::getSizeInFile() { return sizeInFile; }

void JCID::deserialize(QDataStream& ds) { ds >> m_value; }

void JCID::serialize(QDataStream& ds) const { ds << m_value; }

} // namespace priv
} // namespace libmson
