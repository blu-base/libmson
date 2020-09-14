#include "PropertyID.h"

#include "../commonTypes/Enums.h"
#include "../helper/Helper.h"

#include <QDataStream>
#include <QDebug>

namespace MSONcommon {

PropertyIDs PropertyID::id() const { return m_id; }

void PropertyID::setId(const PropertyIDs &id) { m_id = id; }

PropertyIDType PropertyID::type() const { return m_type; }

void PropertyID::setType(const PropertyIDType &type) { m_type = type; }

quint32 PropertyID::value() const { return m_value; }

QString PropertyID::idToString(const PropertyIDs &val) {
  QString m_id_string;
  switch (val) {
  case PropertyIDs::LayoutTightLayout:
    m_id_string = "LayoutTightLayout";
    break;
  case PropertyIDs::PageWidth:
    m_id_string = "PageWidth";
    break;
  case PropertyIDs::PageHeight:
    m_id_string = "PageHeight";
    break;
  case PropertyIDs::OutlineElementChildLevel:
    m_id_string = "OutlineElementChildLevel";
    break;
  case PropertyIDs::Bold:
    m_id_string = "Bold";
    break;
  case PropertyIDs::Italic:
    m_id_string = "Italic";
    break;
  case PropertyIDs::Underline:
    m_id_string = "Underline";
    break;
  case PropertyIDs::Strikethrough:
    m_id_string = "Strikethrough";
    break;
  case PropertyIDs::Superscript:
    m_id_string = "Superscript";
    break;
  case PropertyIDs::Subscript:
    m_id_string = "Subscript";
    break;
  case PropertyIDs::Font:
    m_id_string = "Font";
    break;
  case PropertyIDs::FontSize:
    m_id_string = "FontSize";
    break;
  case PropertyIDs::FontColor:
    m_id_string = "FontColor";
    break;
  case PropertyIDs::Highlight:
    m_id_string = "Highlight";
    break;
  case PropertyIDs::RgOutlineIndentDistance:
    m_id_string = "RgOutlineIndentDistance";
    break;
  case PropertyIDs::BodyTextAlignment:
    m_id_string = "BodyTextAlignment";
    break;
  case PropertyIDs::OffsetFromParentHoriz:
    m_id_string = "OffsetFromParentHoriz";
    break;
  case PropertyIDs::OffsetFromParentVert:
    m_id_string = "OffsetFromParentVert";
    break;
  case PropertyIDs::NumberListFormat:
    m_id_string = "NumberListFormat";
    break;
  case PropertyIDs::LayoutMaxWidth:
    m_id_string = "LayoutMaxWidth";
    break;
  case PropertyIDs::LayoutMaxHeight:
    m_id_string = "LayoutMaxHeight";
    break;
  case PropertyIDs::ContentChildNodes:
    m_id_string = "ContentChildNodes";
    break;
  case PropertyIDs::ElementChildNodes:
    m_id_string = "ElementChildNodes";
    break;
  case PropertyIDs::EnableHistory:
    m_id_string = "EnableHistory";
    break;
  case PropertyIDs::RichEditTextUnicode:
    m_id_string = "RichEditTextUnicode";
    break;
  case PropertyIDs::ListNodes:
    m_id_string = "ListNodes";
    break;
  case PropertyIDs::NotebookManagementEntityGuid:
    m_id_string = "NotebookManagementEntityGuid";
    break;
  case PropertyIDs::OutlineElementRTL:
    m_id_string = "OutlineElementRTL";
    break;
  case PropertyIDs::LanguageID:
    m_id_string = "LanguageID";
    break;
  case PropertyIDs::LayoutAlignmentInParent:
    m_id_string = "LayoutAlignmentInParent";
    break;
  case PropertyIDs::PictureContainer:
    m_id_string = "PictureContainer";
    break;
  case PropertyIDs::PageMarginTop:
    m_id_string = "PageMarginTop";
    break;
  case PropertyIDs::PageMarginBottom:
    m_id_string = "PageMarginBottom";
    break;
  case PropertyIDs::PageMarginLeft:
    m_id_string = "PageMarginLeft";
    break;
  case PropertyIDs::PageMarginRight:
    m_id_string = "PageMarginRight";
    break;
  case PropertyIDs::ListFont:
    m_id_string = "ListFont";
    break;
  case PropertyIDs::TopologyCreationTimeStamp:
    m_id_string = "TopologyCreationTimeStamp";
    break;
  case PropertyIDs::LayoutAlignmentSelf:
    m_id_string = "LayoutAlignmentSelf";
    break;
  case PropertyIDs::IsTitleTime:
    m_id_string = "IsTitleTime";
    break;
  case PropertyIDs::IsBoilerText:
    m_id_string = "IsBoilerText";
    break;
  case PropertyIDs::PageSize:
    m_id_string = "PageSize";
    break;
  case PropertyIDs::PortraitPage:
    m_id_string = "PortraitPage";
    break;
  case PropertyIDs::EnforceOutlineStructure:
    m_id_string = "EnforceOutlineStructure";
    break;
  case PropertyIDs::EditRootRTL:
    m_id_string = "EditRootRTL";
    break;
  case PropertyIDs::CannotBeSelected:
    m_id_string = "CannotBeSelected";
    break;
  case PropertyIDs::IsTitleText:
    m_id_string = "IsTitleText";
    break;
  case PropertyIDs::IsTitleDate:
    m_id_string = "IsTitleDate";
    break;
  case PropertyIDs::ListRestart:
    m_id_string = "ListRestart";
    break;
  case PropertyIDs::IsLayoutSizeSetByUser:
    m_id_string = "IsLayoutSizeSetByUser";
    break;
  case PropertyIDs::ListSpacingMu:
    m_id_string = "ListSpacingMu";
    break;
  case PropertyIDs::LayoutOutlineReservedWidth:
    m_id_string = "LayoutOutlineReservedWidth";
    break;
  case PropertyIDs::LayoutResolveChildCollisions:
    m_id_string = "LayoutResolveChildCollisions";
    break;
  case PropertyIDs::IsReadOnly:
    m_id_string = "IsReadOnly";
    break;
  case PropertyIDs::LayoutMinimumOutlineWidth:
    m_id_string = "LayoutMinimumOutlineWidth";
    break;
  case PropertyIDs::LayoutCollisionPriority:
    m_id_string = "LayoutCollisionPriority";
    break;
  case PropertyIDs::CachedTitleString:
    m_id_string = "CachedTitleString";
    break;
  case PropertyIDs::DescendantsCannotBeMoved:
    m_id_string = "DescendantsCannotBeMoved";
    break;
  case PropertyIDs::RichEditTextLangID:
    m_id_string = "RichEditTextLangID";
    break;
  case PropertyIDs::LayoutTightAlignment:
    m_id_string = "LayoutTightAlignment";
    break;
  case PropertyIDs::Charset:
    m_id_string = "Charset";
    break;
  case PropertyIDs::CreationTimeStamp:
    m_id_string = "CreationTimeStamp";
    break;
  case PropertyIDs::Deletable:
    m_id_string = "Deletable";
    break;
  case PropertyIDs::ListMSAAIndex:
    m_id_string = "ListMSAAIndex";
    break;
  case PropertyIDs::IsBackground:
    m_id_string = "IsBackground";
    break;
  case PropertyIDs::IRecordMedia:
    m_id_string = "IRecordMedia";
    break;
  case PropertyIDs::CachedTitleStringFromPage:
    m_id_string = "CachedTitleStringFromPage";
    break;
  case PropertyIDs::RowCount:
    m_id_string = "RowCount";
    break;
  case PropertyIDs::ColumnCount:
    m_id_string = "ColumnCount";
    break;
  case PropertyIDs::TableBordersVisible:
    m_id_string = "TableBordersVisible";
    break;
  case PropertyIDs::StructureElementChildNodes:
    m_id_string = "StructureElementChildNodes";
    break;
  case PropertyIDs::ChildGraphSpaceElementNodes:
    m_id_string = "ChildGraphSpaceElementNodes";
    break;
  case PropertyIDs::TableColumnWidths:
    m_id_string = "TableColumnWidths";
    break;
  case PropertyIDs::Author:
    m_id_string = "Author";
    break;
  case PropertyIDs::LastModifiedTimeStamp:
    m_id_string = "LastModifiedTimeStamp";
    break;
  case PropertyIDs::AuthorOriginal:
    m_id_string = "AuthorOriginal";
    break;
  case PropertyIDs::AuthorMostRecent:
    m_id_string = "AuthorMostRecent";
    break;
  case PropertyIDs::LastModifiedTime:
    m_id_string = "LastModifiedTime";
    break;
  case PropertyIDs::IsConflictPage:
    m_id_string = "IsConflictPage";
    break;
  case PropertyIDs::TableColumnsLocked:
    m_id_string = "TableColumnsLocked";
    break;
  case PropertyIDs::SchemaRevisionInOrderToRead:
    m_id_string = "SchemaRevisionInOrderToRead";
    break;
  case PropertyIDs::IsConflictObjectForRender:
    m_id_string = "IsConflictObjectForRender";
    break;
  case PropertyIDs::EmbeddedFileContainer:
    m_id_string = "EmbeddedFileContainer";
    break;
  case PropertyIDs::EmbeddedFileName:
    m_id_string = "EmbeddedFileName";
    break;
  case PropertyIDs::SourceFilepath:
    m_id_string = "SourceFilepath";
    break;
  case PropertyIDs::ConflictingUserName:
    m_id_string = "ConflictingUserName";
    break;
  case PropertyIDs::ImageFilename:
    m_id_string = "ImageFilename";
    break;
  case PropertyIDs::IsConflictObjectForSelection:
    m_id_string = "IsConflictObjectForSelection";
    break;
  case PropertyIDs::PageLevel:
    m_id_string = "PageLevel";
    break;
  case PropertyIDs::TextRunIndex:
    m_id_string = "TextRunIndex";
    break;
  case PropertyIDs::TextRunFormatting:
    m_id_string = "TextRunFormatting";
    break;
  case PropertyIDs::Hyperlink:
    m_id_string = "Hyperlink";
    break;
  case PropertyIDs::UnderlineType:
    m_id_string = "UnderlineType";
    break;
  case PropertyIDs::Hidden:
    m_id_string = "Hidden";
    break;
  case PropertyIDs::HyperlinkProtected:
    m_id_string = "HyperlinkProtected";
    break;
  case PropertyIDs::TextRunIsEmbeddedObject:
    m_id_string = "TextRunIsEmbeddedObject";
    break;
  case PropertyIDs::ImageAltText:
    m_id_string = "ImageAltText";
    break;
  case PropertyIDs::MathFormatting:
    m_id_string = "MathFormatting";
    break;
  case PropertyIDs::ParagraphStyle:
    m_id_string = "ParagraphStyle";
    break;
  case PropertyIDs::ParagraphSpaceBefore:
    m_id_string = "ParagraphSpaceBefore";
    break;
  case PropertyIDs::ParagraphSpaceAfter:
    m_id_string = "ParagraphSpaceAfter";
    break;
  case PropertyIDs::ParagraphLineSpacingExact:
    m_id_string = "ParagraphLineSpacingExact";
    break;
  case PropertyIDs::MetaDataObjectsAboveGraphSpace:
    m_id_string = "MetaDataObjectsAboveGraphSpace";
    break;
  case PropertyIDs::TextRunDataObject:
    m_id_string = "TextRunDataObject";
    break;
  case PropertyIDs::TextRunData:
    m_id_string = "TextRunData";
    break;
  case PropertyIDs::ParagraphStyleId:
    m_id_string = "ParagraphStyleId";
    break;
  case PropertyIDs::HasVersionPages:
    m_id_string = "HasVersionPages";
    break;
  case PropertyIDs::ActionItemType:
    m_id_string = "ActionItemType";
    break;
  case PropertyIDs::NoteTagShape:
    m_id_string = "NoteTagShape";
    break;
  case PropertyIDs::NoteTagHighlightColor:
    m_id_string = "NoteTagHighlightColor";
    break;
  case PropertyIDs::NoteTagTextColor:
    m_id_string = "NoteTagTextColor";
    break;
  case PropertyIDs::NoteTagPropertyStatus:
    m_id_string = "NoteTagPropertyStatus";
    break;
  case PropertyIDs::NoteTagLabel:
    m_id_string = "NoteTagLabel";
    break;
  case PropertyIDs::NoteTagCreated:
    m_id_string = "NoteTagCreated";
    break;
  case PropertyIDs::NoteTagCompleted:
    m_id_string = "NoteTagCompleted";
    break;
  case PropertyIDs::NoteTagDefinitionOid:
    m_id_string = "NoteTagDefinitionOid";
    break;
  case PropertyIDs::NoteTagStates:
    m_id_string = "NoteTagStates";
    break;
  case PropertyIDs::ActionItemStatus:
    m_id_string = "ActionItemStatus";
    break;
  case PropertyIDs::ActionItemSchemaVersion:
    m_id_string = "ActionItemSchemaVersion";
    break;
  case PropertyIDs::ReadingOrderRTL:
    m_id_string = "ReadingOrderRTL";
    break;
  case PropertyIDs::ParagraphAlignment:
    m_id_string = "ParagraphAlignment";
    break;
  case PropertyIDs::VersionHistoryGraphSpaceContextNodes:
    m_id_string = "VersionHistoryGraphSpaceContextNodes";
    break;
  case PropertyIDs::DisplayedPageNumber:
    m_id_string = "DisplayedPageNumber";
    break;
  case PropertyIDs::SectionDisplayName:
    m_id_string = "SectionDisplayName";
    break;
  case PropertyIDs::NextStyle:
    m_id_string = "NextStyle";
    break;
  case PropertyIDs::WebPictureContainer14:
    m_id_string = "WebPictureContainer14";
    break;
  case PropertyIDs::ImageUploadState:
    m_id_string = "ImageUploadState";
    break;
  case PropertyIDs::TextExtendedAscii:
    m_id_string = "TextExtendedAscii";
    break;
  case PropertyIDs::PictureWidth:
    m_id_string = "PictureWidth";
    break;
  case PropertyIDs::PictureHeight:
    m_id_string = "PictureHeight";
    break;
  case PropertyIDs::PageMarginOriginX:
    m_id_string = "PageMarginOriginX";
    break;
  case PropertyIDs::PageMarginOriginY:
    m_id_string = "PageMarginOriginY";
    break;
  case PropertyIDs::WzHyperlinkUrl:
    m_id_string = "WzHyperlinkUrl";
    break;
  case PropertyIDs::TaskTagDueDate:
    m_id_string = "TaskTagDueDate";
    break;

  case PropertyIDs::undoc_AuthorInitials:
    m_id_string = "undoc_AuthorInitials";
    break;

  case PropertyIDs::undoc_ResolutionID:
    m_id_string = "undoc_ResolutionID";
    break;

  case PropertyIDs::undoc_StrokesToolSettings:
    m_id_string = "undoc_StrokesToolSettings";
    break;
  case PropertyIDs::undoc_Undetermined64byteBlock:
    m_id_string = "undoc_Undetermined64byteBlock";
    break;
  case PropertyIDs::undoc_StrokesBlob:
    m_id_string = "undoc_StrokesBlob";
    break;
  case PropertyIDs::undoc_StrokesToolSizeHeight:
    m_id_string = "undoc_StrokesToolSizeHeight";
    break;
  case PropertyIDs::undoc_StrokesToolSizeWidth:
    m_id_string = "undoc_StrokesToolSizeWidth";
    break;
  case PropertyIDs::undoc_StrokesColor:
    m_id_string = "undoc_StrokesColor";
    break;
  case PropertyIDs::undoc_StrokesContainer:
    m_id_string = "undoc_StrokesContainer";
    break;
  case PropertyIDs::undoc_StrokesGroup:
    m_id_string = "undoc_StrokesGroup";
    break;
  case PropertyIDs::undoc_Strokes003418:
    m_id_string = "undoc_Strokes003418";
    break;
  case PropertyIDs::undoc_StrokesIndex:
    m_id_string = "undoc_StrokesIndex";
    break;
  case PropertyIDs::undoc_StrokesGUID:
    m_id_string = "undoc_StrokesGUID";
    break;
  case PropertyIDs::unodc_StrokeLanguage:
    m_id_string = "unodc_StrokeLanguage";
    break;
  case PropertyIDs::undoc_StrokesModus:
    m_id_string = "undoc_StrokesModus";
    break;

  case PropertyIDs::undoc_StrokesCreationTime:
    m_id_string = "undoc_StrokesCreationTime";
    break;
  case PropertyIDs::undoc_StrokesRecognizedText:
    m_id_string = "undoc_StrokesRecognizedText";
    break;

  case PropertyIDs::undoc_StrokesOffsetsVertHoriz:
    m_id_string = "undoc_StrokesOffsetsVertHoriz";
    break;

  case PropertyIDs::undoc_SchemaRevisionInOrderToRead:
    m_id_string = "undoc_SchemaRevisionInOrderToRead";
    break;
  case PropertyIDs::undoc_RecognizedText:
    m_id_string = "undoc_RecognizedText";
    break;

  case PropertyIDs::undoc_tocSectionName:
    m_id_string = "undoc_tocSectionName";
    break;
  case PropertyIDs::undoc_tocSectionIndex:
    m_id_string = "undoc_tocSectionIndex";
    break;
  case PropertyIDs::undoc_tocSectionGUID:
    m_id_string = "undoc_tocSectionGUID";
    break;
  case PropertyIDs::undoc_tocSectionColor:
    m_id_string = "undoc_tocSectionColor";
    break;

  case PropertyIDs::undoc_PageBackgroundColor:
    m_id_string = "undoc_PageBackgroundColor";
    break;

  case PropertyIDs::None:
    m_id_string = "None";
    break;
  default:
    m_id_string = "unspecified";
    break;
  }

  return m_id_string;
}

QString PropertyID::typeToString(const PropertyIDType &val) {
  QString m_type_string;
  switch (val) {
  case PropertyIDType::None:
    m_type_string = "None";
    break;
  case PropertyIDType::NoData:
    m_type_string = "NoData";
    break;
  case PropertyIDType::Bool:
    m_type_string = "Bool";
    break;
  case PropertyIDType::OneByteOfData:
    m_type_string = "OneByteOfData";
    break;
  case PropertyIDType::TwoBytesOfData:
    m_type_string = "TwoBytesOfData";
    break;
  case PropertyIDType::FourBytesOfData:
    m_type_string = "FourBytesOfData";
    break;
  case PropertyIDType::EightBytesOfData:
    m_type_string = "EightBytesOfData";
    break;
  case PropertyIDType::FourBytesOfLengthFollowedByData:
    m_type_string = "FourBytesOfLengthFollowedByData";
    break;
  case PropertyIDType::ObjectID:
    m_type_string = "ObjectID";
    break;
  case PropertyIDType::ArrayOfObjectIDs:
    m_type_string = "ArrayOfObjectIDs";
    break;
  case PropertyIDType::ObjectSpaceID:
    m_type_string = "ObjectSpaceID";
    break;
  case PropertyIDType::ArrayOfObjectSpaceIDs:
    m_type_string = "ArrayOfObjectSpaceIDs";
    break;
  case PropertyIDType::ContextID:
    m_type_string = "ContextID";
    break;
  case PropertyIDType::ArrayOfContextIDs:
    m_type_string = "ArrayOfContextIDs";
    break;
  case PropertyIDType::ArrayOfPropertyValues:
    m_type_string = "ArrayOfPropertyValues";
    break;
  case PropertyIDType::PropertySet:
    m_type_string = "PropertySet";
    break;

  case PropertyIDType::InvalidType:
  default:
    m_type_string = "InvalidType";
    break;
  }

  return m_type_string;
}

int PropertyID::boolValue() const {
  if (m_type == PropertyIDType::Bool) {
    return m_boolValue;
  } else {
    return -1;
  }
}

void PropertyID::setBoolValue(bool boolValue) {
  if (m_type == PropertyIDType::Bool) {
    m_boolValue = boolValue;
  } else {
    m_boolValue = false;
  }
}

void PropertyID::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("PropertyID");

  xmlWriter.writeAttribute("Value", qStringHex(m_value, 8));

  xmlWriter.writeAttribute("ID", idToString(m_id));

  xmlWriter.writeAttribute("Type", typeToString(m_type));

  xmlWriter.writeAttribute("boolValue", m_boolValue ? "True" : "False");

  xmlWriter.writeEndElement();
}

PropertyID::PropertyID()
    : m_value(), m_id(PropertyIDs::None), m_type(PropertyIDType::None),
      m_boolValue(false) {}

PropertyID::PropertyID(const PropertyIDs &id, const PropertyIDType &type)
    : m_value(), m_id(id), m_type(type), m_boolValue(false) {}

void PropertyID::deserialize(QDataStream &ds) {
  ds >> m_value;

  m_boolValue = m_value << 31;

  /// \todo PropertyID structure not fully clear...
  quint32 m_id_val = m_value & 0x7FFFFFFF;

  m_id = static_cast<PropertyIDs>(m_id_val);

  quint8 m_type_val = static_cast<quint8>((m_value >> 26) & 0x1F);

  m_type = static_cast<PropertyIDType>(m_type_val);

  if (m_type != PropertyIDType::Bool) {
    m_boolValue = false;
  }
}

void PropertyID::serialize(QDataStream &ds) const {
  quint32 temp{};

  temp += m_boolValue << 31;
  if (m_type != PropertyIDType::InvalidType && m_id != PropertyIDs::None) {
    temp += static_cast<quint32>(m_type) << 26;
    temp += static_cast<quint32>(m_id);
  } else {
    qWarning() << "Trying to write invalid PropertyID.";
  }

  ds << temp;
}

void PropertyID::toDebugString(QDebug &dbg) const {}

} // namespace MSONcommon
