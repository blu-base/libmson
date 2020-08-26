#include "PropertyID.h"



#include "../commonTypes/Enums.h"
#include "../helper/Helper.h"


#include <QDataStream>
#include <QDebug>

PropertyIDs PropertyID::id() const { return m_id; }

void PropertyID::setId(const PropertyIDs &id) { m_id = id; }

PropertyIDType PropertyID::type() const { return m_type; }

void PropertyID::setType(const PropertyIDType &type) { m_type = type; }

quint32 PropertyID::value() const
{
    return m_value;
}

QString PropertyID::idToString(const PropertyIDs& val)
{
    QString m_id_string;
    switch(val) {
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
    case PropertyIDs::ResolutionID:
        m_id_string = "ResolutionID";
        break;
    case PropertyIDs::AuthorInitials:
        m_id_string = "AuthorInitials";
        break;

    case PropertyIDs::None:
    default:
            m_id_string= "None";
        break;
    }

    return m_id_string;
}

QString PropertyID::typeToString(const PropertyIDType& val)
{
    QString m_type_string;
    switch(val) {
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
        m_type_string= "InvalidType";
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

void PropertyID::generateXml(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("PropertyID");

    xmlWriter.writeAttribute("Value", qStringHex(m_value,8));

    xmlWriter.writeAttribute("ID", idToString(m_id));


    xmlWriter.writeAttribute("Type", typeToString(m_type));

    xmlWriter.writeAttribute("boolValue", m_boolValue ? "True" : "False");

    xmlWriter.writeEndElement();
}

PropertyID::PropertyID()
    : m_id(PropertyIDs::None), m_type(PropertyIDType::None),
      m_boolValue(false) {}

PropertyID::PropertyID(const PropertyIDs &id, const PropertyIDType &type)
    : m_id(id), m_type(type), m_boolValue(false) {}

void PropertyID::deserialize(QDataStream &ds) {
  ds >> m_value;

  m_boolValue = m_value << 31;

  /// \todo PropertyID structure not fully clear...
  quint32 m_id_val = m_value & 0x7FFFFFFF;

  switch(m_id_val) {
  case 0x00000000:
    m_id = PropertyIDs::None;
    break;

  case 0x08001C00:
    m_id = PropertyIDs::LayoutTightLayout;
    break;

  case 0x14001C01:
    m_id = PropertyIDs::PageWidth;
    break;

  case 0x14001C02:
    m_id = PropertyIDs::PageHeight;
    break;

  case 0x0C001C03:
    m_id = PropertyIDs::OutlineElementChildLevel;
    break;

  case 0x08001C04:
    m_id = PropertyIDs::Bold;
    break;

  case 0x08001C05:
    m_id = PropertyIDs::Italic;
    break;

  case 0x08001C06:
    m_id = PropertyIDs::Underline;
    break;

  case 0x08001C07:
    m_id = PropertyIDs::Strikethrough;
    break;

  case 0x08001C08:
    m_id = PropertyIDs::Superscript;
    break;

  case 0x08001C09:
    m_id = PropertyIDs::Subscript;
    break;

  case 0x1C001C0A:
    m_id = PropertyIDs::Font;
    break;

  case 0x10001C0B:
    m_id = PropertyIDs::FontSize;
    break;

  case 0x14001C0C:
    m_id = PropertyIDs::FontColor;
    break;

  case 0x14001C0D:
    m_id = PropertyIDs::Highlight;
    break;

  case 0x1C001C12:
    m_id = PropertyIDs::RgOutlineIndentDistance;
    break;

  case 0x0C001C13:
    m_id = PropertyIDs::BodyTextAlignment;
    break;

  case 0x14001C14:
    m_id = PropertyIDs::OffsetFromParentHoriz;
    break;

  case 0x14001C15:
    m_id = PropertyIDs::OffsetFromParentVert;
    break;

  case 0x1C001C1A:
    m_id = PropertyIDs::NumberListFormat;
    break;

  case 0x14001C1B:
    m_id = PropertyIDs::LayoutMaxWidth;
    break;

  case 0x14001C1C:
    m_id = PropertyIDs::LayoutMaxHeight;
    break;

  case 0x24001C1F:
    m_id = PropertyIDs::ContentChildNodes;
    break;

  case 0x24001C20:
    m_id = PropertyIDs::ElementChildNodes;
    break;

  case 0x08001E1E:
    m_id = PropertyIDs::EnableHistory;
    break;

  case 0x1C001C22:
    m_id = PropertyIDs::RichEditTextUnicode;
    break;

  case 0x24001C26:
    m_id = PropertyIDs::ListNodes;
    break;

  case 0x1C001C30:
    m_id = PropertyIDs::NotebookManagementEntityGuid;
    break;

  case 0x08001C34:
    m_id = PropertyIDs::OutlineElementRTL;
    break;

  case 0x14001C3B:
    m_id = PropertyIDs::LanguageID;
    break;

  case 0x14001C3E:
    m_id = PropertyIDs::LayoutAlignmentInParent;
    break;

  case 0x20001C3F:
    m_id = PropertyIDs::PictureContainer;
    break;

  case 0x14001C4C:
    m_id = PropertyIDs::PageMarginTop;
    break;

  case 0x14001C4D:
    m_id = PropertyIDs::PageMarginBottom;
    break;

  case 0x14001C4E:
    m_id = PropertyIDs::PageMarginLeft;
    break;

  case 0x14001C4F:
    m_id = PropertyIDs::PageMarginRight;
    break;

  case 0x1C001C52:
    m_id = PropertyIDs::ListFont;
    break;

  case 0x18001C65:
    m_id = PropertyIDs::TopologyCreationTimeStamp;
    break;

  case 0x14001C84:
    m_id = PropertyIDs::LayoutAlignmentSelf;
    break;

  case 0x08001C87:
    m_id = PropertyIDs::IsTitleTime;
    break;

  case 0x08001C88:
    m_id = PropertyIDs::IsBoilerText;
    break;

  case 0x14001C8B:
    m_id = PropertyIDs::PageSize;
    break;

  case 0x08001C8E:
    m_id = PropertyIDs::PortraitPage;
    break;

  case 0x08001C91:
    m_id = PropertyIDs::EnforceOutlineStructure;
    break;

  case 0x08001C92:
    m_id = PropertyIDs::EditRootRTL;
    break;

  case 0x08001CB2:
    m_id = PropertyIDs::CannotBeSelected;
    break;

  case 0x08001CB4:
    m_id = PropertyIDs::IsTitleText;
    break;

  case 0x08001CB5:
    m_id = PropertyIDs::IsTitleDate;
    break;

  case 0x14001CB7:
    m_id = PropertyIDs::ListRestart;
    break;

  case 0x08001CBD:
    m_id = PropertyIDs::IsLayoutSizeSetByUser;
    break;

  case 0x14001CCB:
    m_id = PropertyIDs::ListSpacingMu;
    break;

  case 0x14001CDB:
    m_id = PropertyIDs::LayoutOutlineReservedWidth;
    break;

  case 0x08001CDC:
    m_id = PropertyIDs::LayoutResolveChildCollisions;
    break;

  case 0x08001CDE:
    m_id = PropertyIDs::IsReadOnly;
    break;

  case 0x14001CEC:
    m_id = PropertyIDs::LayoutMinimumOutlineWidth;
    break;

  case 0x14001CF1:
    m_id = PropertyIDs::LayoutCollisionPriority;
    break;

  case 0x1C001CF3:
    m_id = PropertyIDs::CachedTitleString;
    break;

  case 0x08001CF9:
    m_id = PropertyIDs::DescendantsCannotBeMoved;
    break;

  case 0x10001CFE:
    m_id = PropertyIDs::RichEditTextLangID;
    break;

  case 0x08001CFF:
    m_id = PropertyIDs::LayoutTightAlignment;
    break;

  case 0x0C001D01:
    m_id = PropertyIDs::Charset;
    break;

  case 0x14001D09:
    m_id = PropertyIDs::CreationTimeStamp;
    break;

  case 0x08001D0C:
    m_id = PropertyIDs::Deletable;
    break;

  case 0x10001D0E:
    m_id = PropertyIDs::ListMSAAIndex;
    break;

  case 0x08001D13:
    m_id = PropertyIDs::IsBackground;
    break;

  case 0x14001D24:
    m_id = PropertyIDs::IRecordMedia;
    break;

  case 0x1C001D3C:
    m_id = PropertyIDs::CachedTitleStringFromPage;
    break;

  case 0x14001D57:
    m_id = PropertyIDs::RowCount;
    break;

  case 0x14001D58:
    m_id = PropertyIDs::ColumnCount;
    break;

  case 0x08001D5E:
    m_id = PropertyIDs::TableBordersVisible;
    break;

  case 0x24001D5F:
    m_id = PropertyIDs::StructureElementChildNodes;
    break;

  case 0x2C001D63:
    m_id = PropertyIDs::ChildGraphSpaceElementNodes;
    break;

  case 0x1C001D66:
    m_id = PropertyIDs::TableColumnWidths;
    break;

  case 0x1C001D75:
    m_id = PropertyIDs::Author;
    break;

  case 0x18001D77:
    m_id = PropertyIDs::LastModifiedTimeStamp;
    break;

  case 0x20001D78:
    m_id = PropertyIDs::AuthorOriginal;
    break;

  case 0x20001D79:
    m_id = PropertyIDs::AuthorMostRecent;
    break;

  case 0x14001D7A:
    m_id = PropertyIDs::LastModifiedTime;
    break;

  case 0x08001D7C:
    m_id = PropertyIDs::IsConflictPage;
    break;

  case 0x1C001D7D:
    m_id = PropertyIDs::TableColumnsLocked;
    break;

  case 0x14001D82:
    m_id = PropertyIDs::SchemaRevisionInOrderToRead;
    break;

  case 0x08001D96:
    m_id = PropertyIDs::IsConflictObjectForRender;
    break;

  case 0x20001D9B:
    m_id = PropertyIDs::EmbeddedFileContainer;
    break;

  case 0x1C001D9C:
    m_id = PropertyIDs::EmbeddedFileName;
    break;

  case 0x1C001D9D:
    m_id = PropertyIDs::SourceFilepath;
    break;

  case 0x1C001D9E:
    m_id = PropertyIDs::ConflictingUserName;
    break;

  case 0x1C001DD7:
    m_id = PropertyIDs::ImageFilename;
    break;

  case 0x08001DDB:
    m_id = PropertyIDs::IsConflictObjectForSelection;
    break;

  case 0x14001DFF:
    m_id = PropertyIDs::PageLevel;
    break;

  case 0x1C001E12:
    m_id = PropertyIDs::TextRunIndex;
    break;

  case 0x24001E13:
    m_id = PropertyIDs::TextRunFormatting;
    break;

  case 0x08001E14:
    m_id = PropertyIDs::Hyperlink;
    break;

  case 0x0C001E15:
    m_id = PropertyIDs::UnderlineType;
    break;

  case 0x08001E16:
    m_id = PropertyIDs::Hidden;
    break;

  case 0x08001E19:
    m_id = PropertyIDs::HyperlinkProtected;
    break;

  case 0x08001E22:
    m_id = PropertyIDs::TextRunIsEmbeddedObject;
    break;

  case 0x1C001E58:
    m_id = PropertyIDs::ImageAltText;
    break;

  case 0x08003401:
    m_id = PropertyIDs::MathFormatting;
    break;

  case 0x2000342C:
    m_id = PropertyIDs::ParagraphStyle;
    break;

  case 0x1400342E:
    m_id = PropertyIDs::ParagraphSpaceBefore;
    break;

  case 0x1400342F:
    m_id = PropertyIDs::ParagraphSpaceAfter;
    break;

  case 0x14003430:
    m_id = PropertyIDs::ParagraphLineSpacingExact;
    break;

  case 0x24003442:
    m_id = PropertyIDs::MetaDataObjectsAboveGraphSpace;
    break;

  case 0x24003458:
    m_id = PropertyIDs::TextRunDataObject;
    break;

  case 0x40003499:
    m_id = PropertyIDs::TextRunData;
    break;

  case 0x1C00345A:
    m_id = PropertyIDs::ParagraphStyleId;
    break;

  case 0x08003462:
    m_id = PropertyIDs::HasVersionPages;
    break;

  case 0x10003463:
    m_id = PropertyIDs::ActionItemType;
    break;

  case 0x10003464:
    m_id = PropertyIDs::NoteTagShape;
    break;

  case 0x14003465:
    m_id = PropertyIDs::NoteTagHighlightColor;
    break;

  case 0x14003466:
    m_id = PropertyIDs::NoteTagTextColor;
    break;

  case 0x14003467:
    m_id = PropertyIDs::NoteTagPropertyStatus;
    break;

  case 0x1C003468:
    m_id = PropertyIDs::NoteTagLabel;
    break;

  case 0x1400346E:
    m_id = PropertyIDs::NoteTagCreated;
    break;

  case 0x1400346F:
    m_id = PropertyIDs::NoteTagCompleted;
    break;

  case 0x20003488:
    m_id = PropertyIDs::NoteTagDefinitionOid;
    break;

  case 0x04003489:
    m_id = PropertyIDs::NoteTagStates;
    break;

  case 0x10003470:
    m_id = PropertyIDs::ActionItemStatus;
    break;

  case 0x0C003473:
    m_id = PropertyIDs::ActionItemSchemaVersion;
    break;

  case 0x08003476:
    m_id = PropertyIDs::ReadingOrderRTL;
    break;

  case 0x0C003477:
    m_id = PropertyIDs::ParagraphAlignment;
    break;

  case 0x3400347B:
    m_id = PropertyIDs::VersionHistoryGraphSpaceContextNodes;
    break;

  case 0x14003480:
    m_id = PropertyIDs::DisplayedPageNumber;
    break;

  case 0x1C00349B:
    m_id = PropertyIDs::SectionDisplayName;
    break;

  case 0x1C00348A:
    m_id = PropertyIDs::NextStyle;
    break;

  case 0x200034C8:
    m_id = PropertyIDs::WebPictureContainer14;
    break;

  case 0x140034CB:
    m_id = PropertyIDs::ImageUploadState;
    break;

  case 0x1C003498:
    m_id = PropertyIDs::TextExtendedAscii;
    break;

  case 0x140034CD:
    m_id = PropertyIDs::PictureWidth;
    break;

  case 0x140034CE:
    m_id = PropertyIDs::PictureHeight;
    break;

  case 0x14001D0F:
    m_id = PropertyIDs::PageMarginOriginX;
    break;

  case 0x14001D10:
    m_id = PropertyIDs::PageMarginOriginY;
    break;

  case 0x1C001E20:
    m_id = PropertyIDs::WzHyperlinkUrl;
    break;

  case 0x1400346B:
    m_id = PropertyIDs::TaskTagDueDate;
    break;
  case 0x1c001df8:
      m_id = PropertyIDs::AuthorInitials;
      break;
  case 0x1c001e30:
      m_id = PropertyIDs::ResolutionID;
      break;

  default:
    m_id = PropertyIDs::None;
    break;

  }

  quint8 m_type_val = static_cast<quint8>((m_value >> 26) & 0x1F) ;

  switch (m_type_val) {
  case 0x0:
    m_type = PropertyIDType::None;
    break;
  case 0x1:
    m_type = PropertyIDType::NoData;
    break;
  case 0x2:
    m_type = PropertyIDType::Bool;
    break;
  case 0x3:
    m_type = PropertyIDType::OneByteOfData;
    break;
  case 0x4:
    m_type = PropertyIDType::TwoBytesOfData;
    break;
  case 0x5:
    m_type = PropertyIDType::FourBytesOfData;
    break;
  case 0x6:
    m_type = PropertyIDType::EightBytesOfData;
    break;
  case 0x7:
    m_type = PropertyIDType::FourBytesOfLengthFollowedByData;
    break;
  case 0x8:
    m_type = PropertyIDType::ObjectID;
    break;
  case 0x9:
    m_type = PropertyIDType::ArrayOfObjectIDs;
    break;
  case 0xA:
    m_type = PropertyIDType::ObjectSpaceID;
    break;
  case 0xB:
    m_type = PropertyIDType::ArrayOfObjectSpaceIDs;
    break;
  case 0xC:
    m_type = PropertyIDType::ContextID;
    break;
  case 0xD:
    m_type = PropertyIDType::ArrayOfContextIDs;
    break;
  case 0x10:
    m_type = PropertyIDType::ArrayOfPropertyValues;
    break;
  case 0x11:
    m_type = PropertyIDType::PropertySet;
    break;

  default:
    m_type = PropertyIDType::None;
    break;

  }

  if (m_type != PropertyIDType::Bool) {
    m_boolValue = false;
  }
}

void PropertyID::serialize(QDataStream &ds) const {
  quint32 temp{};

  temp += m_boolValue << 31;
  if (m_type != PropertyIDType::InvalidType && m_id !=PropertyIDs::None) {
  temp += static_cast<quint32>(m_type) << 26;
  temp += static_cast<quint32>(m_id);
  } else {
      qWarning() << "Trying to write invalid PropertyID.";
  }

  ds << temp;
}

void PropertyID::toDebugString(QDebug dbg) const {}
