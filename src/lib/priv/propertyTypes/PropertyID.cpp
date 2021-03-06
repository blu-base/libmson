#include "PropertyID.h"

#include "../utils/Helper.h"
#include <QDebug>

namespace libmson {
namespace priv {

PropertyIDs PropertyID::id() const { return m_id; }

void PropertyID::setId(const PropertyIDs& id) { m_id = id; }

PropertyIDType PropertyID::type() const { return m_type; }

void PropertyID::setType(const PropertyIDType& type) { m_type = type; }

quint32 PropertyID::value() const { return m_value; }

QString PropertyID::idToString() const { return PropertyID::idToString(m_id);
}

QString PropertyID::idToString(const PropertyIDs& val)
{

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
    m_id_string = QLatin1String("RowCount");
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

  case PropertyIDs::undoc_float001c9e:
    m_id_string = "undoc_float001c9e";
    break;
  case PropertyIDs::undoc_float001c9f:
    m_id_string = "undoc_float001c9f";
    break;
  case PropertyIDs::undoc_float001ca0:
    m_id_string = "undoc_float001ca0";
    break;
  case PropertyIDs::undoc_float001ca1:
    m_id_string = "undoc_float001ca1";
    break;

  case PropertyIDs::TextServiesFrameworkFlag1:
    m_id_string = "TextServiesFrameworkFlag1";
    break;

  case PropertyIDs::TextServicesFrameworkBlob:
    m_id_string = "TextServicesFrameworkBlob";
    break;

  case PropertyIDs::undoc_001d5c:
    m_id_string = "undoc_001d5c";
    break;
  case PropertyIDs::undoc_001d5d:
    m_id_string = "undoc_001d5d";
    break;

  case PropertyIDs::AuthorInitials:
    m_id_string = "AuthorInitials";
    break;

  case PropertyIDs::ResolutionID:
    m_id_string = "ResolutionID";
    break;

  case PropertyIDs::InkToolProperties:
    m_id_string = "InkToolProperties";
    break;
  case PropertyIDs::InkMetricTable:
    m_id_string = "InkMetricTable";
    break;
  case PropertyIDs::InkPath:
    m_id_string = "InkPath";
    break;
  case PropertyIDs::InkToolHeight:
    m_id_string = "InkToolHeight";
    break;
  case PropertyIDs::InkToolWidth:
    m_id_string = "InkToolWidth";
    break;
  case PropertyIDs::InkColor:
    m_id_string = "InkColor";
    break;
  case PropertyIDs::InkData:
    m_id_string = "InkData";
    break;
  case PropertyIDs::InkStrokes:
    m_id_string = "InkStrokes";
    break;
  case PropertyIDs::InkBoundingBox:
    m_id_string = "InkBoundingBox";
    break;
  case PropertyIDs::InkStrokeOrderingIndex:
    m_id_string = "InkStrokeOrderingIndex";
    break;
  case PropertyIDs::InkGUID:
    m_id_string = "InkGUID";
    break;
  case PropertyIDs::InkLanguageID:
    m_id_string = "InkLanguageID";
    break;
  case PropertyIDs::InkBias:
    m_id_string = "InkBias";
    break;

  case PropertyIDs::InkCreationTime:
    m_id_string = "InkCreationTime";
    break;
  case PropertyIDs::InkRecognizedText:
    m_id_string = "InkRecognizedText";
    break;

  case PropertyIDs::undoc_StrokesOffsetsVertHoriz:
    m_id_string = "undoc_StrokesOffsetsVertHoriz";
    break;

  case PropertyIDs::undoc_SchemaRevisionInOrderToRead:
    m_id_string = "undoc_SchemaRevisionInOrderToRead";
    break;
  case PropertyIDs::RecognizedText:
    m_id_string = "RecognizedText";
    break;

  case PropertyIDs::undoc_TextServicesFrameworkBlob:
    m_id_string = "undoc_TextServicesFrameworkBlob";
    break;

  case PropertyIDs::SectionName:
    m_id_string = "SectionName";
    break;
  case PropertyIDs::SectionOrderingIndex:
    m_id_string = "SectionOrderingIndex";
    break;
  case PropertyIDs::SectionGUID:
    m_id_string = "SectionGUID";
    break;
  case PropertyIDs::SectionColor:
    m_id_string = "SectionColor";
    break;

  case PropertyIDs::PageBackgroundColor:
    m_id_string = "PageBackgroundColor";
    break;

  case PropertyIDs::NoteTags:
    m_id_string = "NoteTags";
    break;


  case PropertyIDs::FileDataObject_GUID:
    m_id_string = "FileDataObject_GUID";
    break;
  case PropertyIDs::FileDataObject_InvalidData:
    m_id_string = "FileDataObject_InvalidData";
    break;
  case PropertyIDs::FileDataObject_Extension:
    m_id_string = "FileDataObject_Extension";
    break;

  case libmson::priv::PropertyIDs::undoc_TextRunDataPropertyArray:
    m_id_string = "undoc_TextRunDataPropertyArray";
    break;

  case PropertyIDs::InkIgnorePressure:
    m_id_string = "InkIgnorePressure";
    break;
  case PropertyIDs::undoc_StrokesToolSetting003411:
    m_id_string = "undoc_StrokesToolSetting003411";
    break;
  case PropertyIDs::undoc_StrokesToolSetting003412:
    m_id_string = "undoc_StrokesToolSetting003412";
    break;
  case PropertyIDs::undoc_StrokesToolSetting003413:
    m_id_string = "undoc_StrokesToolSetting003413";
    break;
  case PropertyIDs::undoc_StrokesToolSetting003414:
    m_id_string = "undoc_StrokesToolSetting003414";
    break;
  case PropertyIDs::undoc_Strokes00341f:
    m_id_string = "undoc_Strokes00341f";
    break;
  case PropertyIDs::undoc_Strokes003420:
    m_id_string = "undoc_Strokes003420";
    break;
  case PropertyIDs::EmbeddedInkStartX:
    m_id_string = "EmbeddedInkStartX";
    break;
  case PropertyIDs::EmbeddedInkStartY:
    m_id_string = "EmbeddedInkStartY";
    break;
  case PropertyIDs::EmbeddedInkWidth:
    m_id_string = "EmbeddedInkWidth";
    break;
  case PropertyIDs::EmbeddedInkHeight:
    m_id_string = "EmbeddedInkHeight";
    break;
  case PropertyIDs::EmbeddedInkOffsetHoriz:
    m_id_string = "EmbeddedInkOffsetHoriz";
    break;
  case PropertyIDs::EmbeddedInkOffsetVert:
    m_id_string = "EmbeddedInkOffsetVert";
    break;
  case PropertyIDs::undoc_Strokes0034a4:
    m_id_string = "undoc_Strokes0034a4";
    break;
  case PropertyIDs::undoc_Strokes0034a5:
    m_id_string = "undoc_Strokes0034a5";
    break;
  case PropertyIDs::undoc_0x2c001d62:
    m_id_string = "undoc_0x2c001d62";
    break;
  case PropertyIDs::undoc_0x08001c32:
    m_id_string = "undoc_0x08001c32";
    break;
  case PropertyIDs::undoc_0x08001d85:
    m_id_string = "undoc_0x08001d85";
    break;
  case PropertyIDs::undoc_0x08001d8d:
    m_id_string = "undoc_0x08001d8d";
    break;
  case PropertyIDs::undoc_0x08001dce:
    m_id_string = "undoc_0x08001dce";
    break;
  case PropertyIDs::undoc_0x08001dec:
    m_id_string = "undoc_0x08001dec";
    break;
  case PropertyIDs::undoc_0x08001e24:
    m_id_string = "undoc_0x08001e24";
    break;
  case PropertyIDs::undoc_0x08001e2c:
    m_id_string = "undoc_0x08001e2c";
    break;
  case PropertyIDs::undoc_0x08003405:
    m_id_string = "undoc_0x08003405";
    break;
  case PropertyIDs::undoc_0x08003406:
    m_id_string = "undoc_0x08003406";
    break;
  case PropertyIDs::undoc_0x08003495:
    m_id_string = "undoc_0x08003495";
    break;
  case PropertyIDs::undoc_0x080034aa:
    m_id_string = "undoc_0x080034aa";
    break;
  case PropertyIDs::undoc_0x080034dd:
    m_id_string = "undoc_0x080034dd";
    break;
  case PropertyIDs::undoc_0x14001c27:
    m_id_string = "undoc_0x14001c27";
    break;
  case PropertyIDs::undoc_0x14001c28:
    m_id_string = "undoc_0x14001c28";
    break;
  case PropertyIDs::undoc_0x14001c48:
    m_id_string = "undoc_0x14001c48";
    break;
  case PropertyIDs::undoc_0x14001c49:
    m_id_string = "undoc_0x14001c49";
    break;
  case PropertyIDs::undoc_0x14001c4a:
    m_id_string = "undoc_0x14001c4a";
    break;
  case PropertyIDs::undoc_0x14001c4b:
    m_id_string = "undoc_0x14001c4b";
    break;
  case PropertyIDs::undoc_0x14001c99:
    m_id_string = "undoc_0x14001c99";
    break;
  case PropertyIDs::undoc_0x14001cfd:
    m_id_string = "undoc_0x14001cfd";
    break;
  case PropertyIDs::undoc_0x14001df6:
    m_id_string = "undoc_0x14001df6";
    break;
  case PropertyIDs::undoc_0x14001df9:
    m_id_string = "undoc_0x14001df9";
    break;
  case PropertyIDs::undoc_0x1400344f:
    m_id_string = "undoc_0x1400344f";
    break;
  case PropertyIDs::undoc_0x14003450:
    m_id_string = "undoc_0x14003450";
    break;
  case PropertyIDs::undoc_0x14003457:
    m_id_string = "undoc_0x14003457";
    break;
  case PropertyIDs::undoc_0x14003481:
    m_id_string = "undoc_0x14003481";
    break;
  case PropertyIDs::undoc_0x140035a4:
    m_id_string = "undoc_0x140035a4";
    break;
  case PropertyIDs::undoc_0x140035d1:
    m_id_string = "undoc_0x140035d1";
    break;
  case PropertyIDs::undoc_0x140035d2:
    m_id_string = "undoc_0x140035d2";
    break;
  case PropertyIDs::undoc_0x1c001c97:
    m_id_string = "undoc_0x1c001c97";
    break;
  case PropertyIDs::undoc_0x1c001c98:
    m_id_string = "undoc_0x1c001c98";
    break;
  case PropertyIDs::undoc_0x1c001ca3:
    m_id_string = "undoc_0x1c001ca3";
    break;
  case PropertyIDs::undoc_0x1c001ca5:
    m_id_string = "undoc_0x1c001ca5";
    break;
  case PropertyIDs::undoc_0x1c001ca6:
    m_id_string = "undoc_0x1c001ca6";
    break;
  case PropertyIDs::undoc_0x1c001ca7:
    m_id_string = "undoc_0x1c001ca7";
    break;
  case PropertyIDs::undoc_0x1c001cc8:
    m_id_string = "undoc_0x1c001cc8";
    break;
  case PropertyIDs::undoc_0x1c001cda:
    m_id_string = "undoc_0x1c001cda";
    break;
  case PropertyIDs::undoc_0x1c001d4c:
    m_id_string = "undoc_0x1c001d4c";
    break;
  case PropertyIDs::undoc_0x1c001d5d:
    m_id_string = "undoc_0x1c001d5d";
    break;
  case PropertyIDs::undoc_0x1c001d61:
    m_id_string = "undoc_0x1c001d61";
    break;
  case PropertyIDs::undoc_0x1c001d84:
    m_id_string = "undoc_0x1c001d84";
    break;
  case PropertyIDs::undoc_0x1c001daa:
    m_id_string = "undoc_0x1c001daa";
    break;
  case PropertyIDs::undoc_0x1c001dac:
    m_id_string = "undoc_0x1c001dac";
    break;
  case PropertyIDs::undoc_0x1c001dbe:
    m_id_string = "undoc_0x1c001dbe";
    break;
  case PropertyIDs::undoc_0x1c001dbf:
    m_id_string = "undoc_0x1c001dbf";
    break;
  case PropertyIDs::undoc_0x1c001dcf:
    m_id_string = "undoc_0x1c001dcf";
    break;
  case PropertyIDs::undoc_0x1c001dfb:
    m_id_string = "undoc_0x1c001dfb";
    break;
  case PropertyIDs::undoc_0x1c001dfc:
    m_id_string = "undoc_0x1c001dfc";
    break;
  case PropertyIDs::undoc_0x0c001cc0:
    m_id_string = "undoc_0x0c001cc0";
    break;
  case PropertyIDs::undoc_0x0c001d4f:
    m_id_string = "undoc_0x0c001d4f";
    break;
  case PropertyIDs::undoc_0x0c003452:
    m_id_string = "undoc_0x0c003452";
    break;
  case PropertyIDs::undoc_0x1000344e:
    m_id_string = "undoc_0x1000344e";
    break;
  case PropertyIDs::undoc_0x10003453:
    m_id_string = "undoc_0x10003453";
    break;
  case PropertyIDs::undoc_0x10003454:
    m_id_string = "undoc_0x10003454";
    break;
  case PropertyIDs::undoc_0x24001cf6:
    m_id_string = "undoc_0x24001cf6";
    break;


  case PropertyIDs::None:
    m_id_string = "None";
    break;

//  default:
//    m_id_string = "unspecified";
//    break;
  }

  return m_id_string;
}

QString PropertyID::typeToString() const
{
  return PropertyID::typeToString(m_type);
}

QString PropertyID::typeToString(const PropertyIDType& val)
{
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
  case PropertyIDType::ArrayNumber:
    m_type_string = "ArrayNumber";
    break;

  case PropertyIDType::InvalidType:
  default:
    m_type_string = "InvalidType";
    break;
  }

  return m_type_string;
}

int PropertyID::boolValue() const
{
  if (m_type == PropertyIDType::Bool) {
    return m_boolValue;
  }
  else {
    return -1;
  }
}

void PropertyID::setBoolValue(bool boolValue)
{
  if (m_type == PropertyIDType::Bool) {
    m_boolValue = boolValue;
  }
  else {
    m_boolValue = false;
  }
}

// void PropertyID::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
//  xmlWriter.writeStartElement("PropertyID");

//  xmlWriter.writeAttribute("Value", qStringHex(m_value, 8));

//  xmlWriter.writeAttribute("ID", idToString(m_id));

//  xmlWriter.writeAttribute("Type", typeToString(m_type));

//  xmlWriter.writeAttribute("boolValue", m_boolValue ? "True" : "False");

//  xmlWriter.writeEndElement();
//}

PropertyID::PropertyID()
    : m_value(), m_id(PropertyIDs::None), m_type(PropertyIDType::None),
      m_boolValue(false)
{
}

PropertyID::PropertyID(const PropertyIDs& id, const PropertyIDType& type)
    : m_value(), m_id(id), m_type(type), m_boolValue(false)
{
}

void PropertyID::deserialize(QDataStream& ds)
{
  ds >> m_value;

  m_boolValue = m_value >> 31;

  /// \todo PropertyID structure not fully clear...
  quint32 m_id_val = m_value & 0x7FFFFFFF;

  m_id = static_cast<PropertyIDs>(m_id_val);

  quint8 m_type_val = static_cast<quint8>((m_value >> 26) & 0x1F);

  m_type = static_cast<PropertyIDType>(m_type_val);

  if (m_type != PropertyIDType::Bool) {
    m_boolValue = false;
  }
}

void PropertyID::serialize(QDataStream& ds) const
{
  quint32 temp{};

  temp += m_boolValue << 31;

  /// \todo PropertyID uses hardcoded PropertyIDs
  if (m_type != PropertyIDType::InvalidType && m_id != PropertyIDs::None) {
    temp += static_cast<quint32>(m_id);
  }
  else {
    qWarning() << "Trying to write invalid or unknown PropertyID.";

    temp += static_cast<quint32>(m_id);
  }

  ds << temp;
}

// void PropertyID::toDebugString(QDebug &dbg) const {}

} // namespace priv
} // namespace libmson
