#ifndef PROPERTYID_H
#define PROPERTYID_H

#include "IProperty.h"
#include <QtCore/qglobal.h>

#include "../commonTypes/Enums.h"
#include <QXmlStreamWriter>

enum class PropertyIDs : quint32 {
  None = 0x00000000,
  LayoutTightLayout = 0x08001C00,
  PageWidth = 0x14001C01,
  PageHeight = 0x14001C02,
  OutlineElementChildLevel = 0x0C001C03,
  Bold = 0x08001C04,
  Italic = 0x08001C05,
  Underline = 0x08001C06,
  Strikethrough = 0x08001C07,
  Superscript = 0x08001C08,
  Subscript = 0x08001C09,
  Font = 0x1C001C0A,
  FontSize = 0x10001C0B,
  FontColor = 0x14001C0C,
  Highlight = 0x14001C0D,
  RgOutlineIndentDistance = 0x1C001C12,
  BodyTextAlignment = 0x0C001C13,
  OffsetFromParentHoriz = 0x14001C14,
  OffsetFromParentVert = 0x14001C15,
  NumberListFormat = 0x1C001C1A,
  LayoutMaxWidth = 0x14001C1B,
  LayoutMaxHeight = 0x14001C1C,
  ContentChildNodes = 0x24001C1F,
  ElementChildNodes = 0x24001C20,
  EnableHistory = 0x08001E1E,
  RichEditTextUnicode = 0x1C001C22,
  ListNodes = 0x24001C26,
  NotebookManagementEntityGuid = 0x1C001C30,
  OutlineElementRTL = 0x08001C34,
  LanguageID = 0x14001C3B,
  LayoutAlignmentInParent = 0x14001C3E,
  PictureContainer = 0x20001C3F,
  PageMarginTop = 0x14001C4C,
  PageMarginBottom = 0x14001C4D,
  PageMarginLeft = 0x14001C4E,
  PageMarginRight = 0x14001C4F,
  ListFont = 0x1C001C52,
  TopologyCreationTimeStamp = 0x18001C65,
  LayoutAlignmentSelf = 0x14001C84,
  IsTitleTime = 0x08001C87,
  IsBoilerText = 0x08001C88,
  PageSize = 0x14001C8B,
  PortraitPage = 0x08001C8E,
  EnforceOutlineStructure = 0x08001C91,
  EditRootRTL = 0x08001C92,
  CannotBeSelected = 0x08001CB2,
  IsTitleText = 0x08001CB4,
  IsTitleDate = 0x08001CB5,
  ListRestart = 0x14001CB7,
  IsLayoutSizeSetByUser = 0x08001CBD,
  ListSpacingMu = 0x14001CCB,
  LayoutOutlineReservedWidth = 0x14001CDB,
  LayoutResolveChildCollisions = 0x08001CDC,
  IsReadOnly = 0x08001CDE,
  LayoutMinimumOutlineWidth = 0x14001CEC,
  LayoutCollisionPriority = 0x14001CF1,
  CachedTitleString = 0x1C001CF3,
  DescendantsCannotBeMoved = 0x08001CF9,
  RichEditTextLangID = 0x10001CFE,
  LayoutTightAlignment = 0x08001CFF,
  Charset = 0x0C001D01,
  CreationTimeStamp = 0x14001D09,
  Deletable = 0x08001D0C,
  ListMSAAIndex = 0x10001D0E,
  IsBackground = 0x08001D13,
  IRecordMedia = 0x14001D24,
  CachedTitleStringFromPage = 0x1C001D3C,
  RowCount = 0x14001D57,
  ColumnCount = 0x14001D58,
  TableBordersVisible = 0x08001D5E,
  StructureElementChildNodes = 0x24001D5F,
  ChildGraphSpaceElementNodes = 0x2C001D63,
  TableColumnWidths = 0x1C001D66,
  Author = 0x1C001D75,
  LastModifiedTimeStamp = 0x18001D77,
  AuthorOriginal = 0x20001D78,
  AuthorMostRecent = 0x20001D79,
  LastModifiedTime = 0x14001D7A,
  IsConflictPage = 0x08001D7C,
  TableColumnsLocked = 0x1C001D7D,
  SchemaRevisionInOrderToRead = 0x14001D82,
  IsConflictObjectForRender = 0x08001D96,
  EmbeddedFileContainer = 0x20001D9B,
  EmbeddedFileName = 0x1C001D9C,
  SourceFilepath = 0x1C001D9D,
  ConflictingUserName = 0x1C001D9E,
  ImageFilename = 0x1C001DD7,
  IsConflictObjectForSelection = 0x08001DDB,
  PageLevel = 0x14001DFF,
  TextRunIndex = 0x1C001E12,
  TextRunFormatting = 0x24001E13,
  Hyperlink = 0x08001E14,
  UnderlineType = 0x0C001E15,
  Hidden = 0x08001E16,
  HyperlinkProtected = 0x08001E19,
  TextRunIsEmbeddedObject = 0x08001E22,
  ImageAltText = 0x1C001E58,
  MathFormatting = 0x08003401,
  ParagraphStyle = 0x2000342C,
  ParagraphSpaceBefore = 0x1400342E,
  ParagraphSpaceAfter = 0x1400342F,
  ParagraphLineSpacingExact = 0x14003430,
  MetaDataObjectsAboveGraphSpace = 0x24003442,
  TextRunDataObject = 0x24003458,
  TextRunData = 0x40003499,
  ParagraphStyleId = 0x1C00345A,
  HasVersionPages = 0x08003462,
  ActionItemType = 0x10003463,
  NoteTagShape = 0x10003464,
  NoteTagHighlightColor = 0x14003465,
  NoteTagTextColor = 0x14003466,
  NoteTagPropertyStatus = 0x14003467,
  NoteTagLabel = 0x1C003468,
  NoteTagCreated = 0x1400346E,
  NoteTagCompleted = 0x1400346F,
  NoteTagDefinitionOid = 0x20003488,
  NoteTagStates = 0x04003489,
  ActionItemStatus = 0x10003470,
  ActionItemSchemaVersion = 0x0C003473,
  ReadingOrderRTL = 0x08003476,
  ParagraphAlignment = 0x0C003477,
  VersionHistoryGraphSpaceContextNodes = 0x3400347B,
  DisplayedPageNumber = 0x14003480,
  SectionDisplayName = 0x1C00349B,
  NextStyle = 0x1C00348A,
  WebPictureContainer14 = 0x200034C8,
  ImageUploadState = 0x140034CB,
  TextExtendedAscii = 0x1C003498,
  PictureWidth = 0x140034CD,
  PictureHeight = 0x140034CE,
  PageMarginOriginX = 0x14001D0F,
  PageMarginOriginY = 0x14001D10,
  WzHyperlinkUrl = 0x1C001E20,
  TaskTagDueDate = 0x1400346B,

  // undocumented ids, this is mostly guessed

  undoc_AuthorInitials = 0x1c001df8,

  // some windows live stuff, eg:
  // &lt;resolutionId provider=&quot;Windows Live&quot;
  // hash=&quot;abcdefg==&quot;&gt; &lt;localId
  // cid=&quot;abcdefg&quot;/&gt;&lt;/resolutionId&gt;
  undoc_ResolutionID = 0x1c001e30,

  //
  undoc_StrokesBlob = 0x1c00340b,

  // maybe is color of the used tool/stroke
  undoc_StrokesColor = 0x1400340f,

  // likely the language setting, maybe is used for ocr
  unodc_StrokeLanguage = 0x1000341b,

  // squential number likely indicating the input order
  undoc_IndexOfStrokes = 0x14003419,

  // Maybe stores a file name of a section file, but also found FileSyncandWOPI and OneNote_RecycleBin
  undoc_tocSectionName = 0x1c001d6b,
  // usually 16 bytes, likely a guid?
  undoc_tocSectionGUID = 0x1c001d94,

  // maybe the index within the sequence of sections
  undoc_tocSectionIndex = 0x14001cb9,

  // seems to be a color code. 0xFFFFFFFF might be the default (no setting) which differs from COLORREF spec
  undoc_tocSectionColor = 0x14001cbe,

  // seems to always have the same value as SchemaRevisionInOrderToRead
  undoc_SchemaRevisionInOrderToRead = 0x1400348b,

};


class PropertyID : public IProperty {
private:
  quint32 m_value;
  PropertyIDs m_id;
  PropertyIDType m_type;

  bool m_boolValue;

public:
  PropertyID();

  PropertyID(const PropertyIDs &id, const PropertyIDType &type);

  PropertyIDs id() const;
  void setId(const PropertyIDs &id);

  PropertyIDType type() const;
  void setType(const PropertyIDType &type);

  quint32 value() const;

  static QString idToString(const PropertyIDs &val);
  static QString typeToString(const PropertyIDType &val);

  /**
   * @brief returns a bool sized value if PropertyID is of a bool type property
   * @return -1 if PropertyID is not bool type, else 0 for false, 1 for true;
   */
  int boolValue() const;
  void setBoolValue(bool boolValue);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // PROPERTYID_H
