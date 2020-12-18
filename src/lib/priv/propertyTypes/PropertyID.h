#ifndef PROPERTYID_H
#define PROPERTYID_H

#include "IProperty.h"
#include "IPropertyType.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

enum class PropertyIDs : quint32 {
  None                                 = 0x00000000,
  LayoutTightLayout                    = 0x08001C00,
  PageWidth                            = 0x14001C01,
  PageHeight                           = 0x14001C02,
  OutlineElementChildLevel             = 0x0C001C03,
  Bold                                 = 0x08001C04,
  Italic                               = 0x08001C05,
  Underline                            = 0x08001C06,
  Strikethrough                        = 0x08001C07,
  Superscript                          = 0x08001C08,
  Subscript                            = 0x08001C09,
  Font                                 = 0x1C001C0A,
  FontSize                             = 0x10001C0B,
  FontColor                            = 0x14001C0C,
  Highlight                            = 0x14001C0D,
  RgOutlineIndentDistance              = 0x1C001C12,
  BodyTextAlignment                    = 0x0C001C13,
  OffsetFromParentHoriz                = 0x14001C14,
  OffsetFromParentVert                 = 0x14001C15,
  NumberListFormat                     = 0x1C001C1A,
  LayoutMaxWidth                       = 0x14001C1B,
  LayoutMaxHeight                      = 0x14001C1C,
  ContentChildNodes                    = 0x24001C1F,
  ElementChildNodes                    = 0x24001C20,
  EnableHistory                        = 0x08001E1E,
  RichEditTextUnicode                  = 0x1C001C22,
  ListNodes                            = 0x24001C26,
  NotebookManagementEntityGuid         = 0x1C001C30,
  OutlineElementRTL                    = 0x08001C34,
  LanguageID                           = 0x14001C3B,
  LayoutAlignmentInParent              = 0x14001C3E,
  PictureContainer                     = 0x20001C3F,
  PageMarginTop                        = 0x14001C4C,
  PageMarginBottom                     = 0x14001C4D,
  PageMarginLeft                       = 0x14001C4E,
  PageMarginRight                      = 0x14001C4F,
  ListFont                             = 0x1C001C52,
  TopologyCreationTimeStamp            = 0x18001C65,
  LayoutAlignmentSelf                  = 0x14001C84,
  IsTitleTime                          = 0x08001C87,
  IsBoilerText                         = 0x08001C88,
  PageSize                             = 0x14001C8B,
  PortraitPage                         = 0x08001C8E,
  EnforceOutlineStructure              = 0x08001C91,
  EditRootRTL                          = 0x08001C92,
  CannotBeSelected                     = 0x08001CB2,
  IsTitleText                          = 0x08001CB4,
  IsTitleDate                          = 0x08001CB5,
  ListRestart                          = 0x14001CB7,
  IsLayoutSizeSetByUser                = 0x08001CBD,
  ListSpacingMu                        = 0x14001CCB,
  LayoutOutlineReservedWidth           = 0x14001CDB,
  LayoutResolveChildCollisions         = 0x08001CDC,
  IsReadOnly                           = 0x08001CDE,
  LayoutMinimumOutlineWidth            = 0x14001CEC,
  LayoutCollisionPriority              = 0x14001CF1,
  CachedTitleString                    = 0x1C001CF3,
  DescendantsCannotBeMoved             = 0x08001CF9,
  RichEditTextLangID                   = 0x10001CFE,
  LayoutTightAlignment                 = 0x08001CFF,
  Charset                              = 0x0C001D01,
  CreationTimeStamp                    = 0x14001D09,
  Deletable                            = 0x08001D0C,
  ListMSAAIndex                        = 0x10001D0E,
  IsBackground                         = 0x08001D13,
  IRecordMedia                         = 0x14001D24,
  CachedTitleStringFromPage            = 0x1C001D3C,
  RowCount                             = 0x14001D57,
  ColumnCount                          = 0x14001D58,
  TableBordersVisible                  = 0x08001D5E,
  StructureElementChildNodes           = 0x24001D5F,
  ChildGraphSpaceElementNodes          = 0x2C001D63,
  TableColumnWidths                    = 0x1C001D66,
  Author                               = 0x1C001D75,
  LastModifiedTimeStamp                = 0x18001D77,
  AuthorOriginal                       = 0x20001D78,
  AuthorMostRecent                     = 0x20001D79,
  LastModifiedTime                     = 0x14001D7A,
  IsConflictPage                       = 0x08001D7C,
  TableColumnsLocked                   = 0x1C001D7D,
  SchemaRevisionInOrderToRead          = 0x14001D82,
  IsConflictObjectForRender            = 0x08001D96,
  EmbeddedFileContainer                = 0x20001D9B,
  EmbeddedFileName                     = 0x1C001D9C,
  SourceFilepath                       = 0x1C001D9D,
  ConflictingUserName                  = 0x1C001D9E,
  ImageFilename                        = 0x1C001DD7,
  IsConflictObjectForSelection         = 0x08001DDB,
  PageLevel                            = 0x14001DFF,
  TextRunIndex                         = 0x1C001E12,
  TextRunFormatting                    = 0x24001E13,
  Hyperlink                            = 0x08001E14,
  UnderlineType                        = 0x0C001E15,
  Hidden                               = 0x08001E16,
  HyperlinkProtected                   = 0x08001E19,
  TextRunIsEmbeddedObject              = 0x08001E22,
  ImageAltText                         = 0x1C001E58,
  MathFormatting                       = 0x08003401,
  ParagraphStyle                       = 0x2000342C,
  ParagraphSpaceBefore                 = 0x1400342E,
  ParagraphSpaceAfter                  = 0x1400342F,
  ParagraphLineSpacingExact            = 0x14003430,
  MetaDataObjectsAboveGraphSpace       = 0x24003442,
  TextRunDataObject                    = 0x24003458,
  TextRunData                          = 0x40003499,
  ParagraphStyleId                     = 0x1C00345A,
  HasVersionPages                      = 0x08003462,
  ActionItemType                       = 0x10003463,
  NoteTagShape                         = 0x10003464,
  NoteTagHighlightColor                = 0x14003465,
  NoteTagTextColor                     = 0x14003466,
  NoteTagPropertyStatus                = 0x14003467,
  NoteTagLabel                         = 0x1C003468,
  NoteTagCreated                       = 0x1400346E,
  NoteTagCompleted                     = 0x1400346F,
  NoteTagDefinitionOid                 = 0x20003488,
  NoteTagStates                        = 0x04003489,
  ActionItemStatus                     = 0x10003470,
  ActionItemSchemaVersion              = 0x0C003473,
  ReadingOrderRTL                      = 0x08003476,
  ParagraphAlignment                   = 0x0C003477,
  VersionHistoryGraphSpaceContextNodes = 0x3400347B,
  DisplayedPageNumber                  = 0x14003480,
  SectionDisplayName                   = 0x1C00349B,
  NextStyle                            = 0x1C00348A,
  WebPictureContainer14                = 0x200034C8,
  ImageUploadState                     = 0x140034CB,
  TextExtendedAscii                    = 0x1C003498,
  PictureWidth                         = 0x140034CD,
  PictureHeight                        = 0x140034CE,
  PageMarginOriginX                    = 0x14001D0F,
  PageMarginOriginY                    = 0x14001D10,
  WzHyperlinkUrl                       = 0x1C001E20,
  TaskTagDueDate                       = 0x1400346B,

  // undocumented ids, this is mostly guessed, do no trust whether they are
  // deducted correctly

  /** Likely is used for labeling multi-author document changes
   * Uses two letters for author with one family name and one given name (in
   * german, and english)
   */
  undoc_AuthorInitials = 0x1c001df8,

  /** some windows live stuff, eg:
   * <resolutionId provider="Windows Live" hash="abcdefg"> <localId
   * cid="abcdefg"/></resolutionId>
   */
  undoc_ResolutionID = 0x1c001e30,

  /** ObjectID which points to undoc_jciddrawingToolData(0x00120048), the tool
   * settings which contains:
   * * undoc_Undetermined64byteBlock/ 0x1c00340a
   * * undoc_StrokesColor
   * * undoc_StrokesToolSizeHeight
   * * undoc_StrokesToolSizeWidth
   */
  undoc_StrokesToolSettings = 0x20003409,


  /** When ever there are strokes or a shape, there is this 64bytes object which
   * always have the same content (unparsed):
   * 8f6a8a59c052a04b93afaf357411a561 00000080 ffffff7f 02000000 00007a44
   * 759f3fb5e0049844a7eec30dbb5a9011 00000080 ffffff7f 02000000 00007a44
   *
   * there seem to be two GUIDs in this chunk.
   *
   * FourBytesOfLengthFollowedByData
   */
  undoc_Undetermined64byteBlock = 0x1c00340a,

  /** Blob containing serialized strokes in native format
   *
   * Seems to correlate with InkStroke class from onenote api
   *
   * FourBytesOfLengthFollowedByData
   */
  undoc_StrokesBlob = 0x1c00340b,

  /// \todo find ToolSettings whether it's round or square
  /** float32 for the tool height, 1 unit represents 0.01mm
   */
  undoc_StrokesToolSizeHeight = 0x1400340c,

  /** float32 for the tool width, 1 unit represents 0.01mm
   *
   */
  undoc_StrokesToolSizeWidth = 0x1400340d,

  /** Stroke's Tool color
   * FourBytesOfData
   * it's a array of the type: byte[4]
   * RGB + X
   *
   * the first three bytes seem to be the color hex code.
   *
   * X might be a switch to declare fixed color versus automatically
   * changeble,such as maybe color scheme
   */
  undoc_StrokesColor = 0x1400340f,


  /** Strokes's tool setting, which seem to correlate with square-like tool such
   * as the highlight markers Bool usually seems to have only the value True
   * when present
   */
  undoc_StrokesToolSetting003411 = 0x0c003411,
  /** Strokes's tool setting, which seem to correlate with square-like tool such
   * as the highlight markers OneByteOfData usually seems to have only the value
   * 0x01
   */
  undoc_StrokesToolSetting003412 = 0x0c003412,

  /** Strokes's tool setting, which seem to correlate with square-like tool such
   * as the highlight markers OneByteOfData usually seems to have only the value
   * 0x09
   */
  undoc_StrokesToolSetting003413 = 0x0c003413,

  /** Strokes's tool setting, which seem to correlate with square-like tool such
   * as the highlight markers OneByteOfData usually seems to have only the value
   * 0x7f
   */
  undoc_StrokesToolSetting003414 = 0x0c003414,

  /** ObjectID which lives in undoc_jcidShape (0x00060014)
   * Points to the undoc_jcidDrawingGroupNode (0x0002003b)
   * Which contains PropertyID 0x24003416
   * which further points to undoc_jcidDrawingNode (0x00020047)
   *
   * also contains
   */
  undoc_StrokesContainer = 0x20003415,

  /** ArrayofObjectIDs
   *  lives within undoc_jcidDrawingGroupNode(0x0002003b)
   *
   * points to undoc_jcidDrawingNodes which are likely
   * contain the strokes for which matches according to
   * undoc_StrokesRecognizedText have been found
   */
  undoc_StrokesGroup = 0x24003416,

  /** 16 byte structure, not a guid, maybe 4 uint32 being coordinates or bound
   * box in a unit with very small increments (such as the StrokeTool)
   *
   * only present when Handwritting modus is active
   */
  undoc_Strokes003418 = 0x1c003418,

  /** squential number likely indicating the input order
   * FourBytesOfData
   */
  undoc_StrokesIndex = 0x14003419,
  /** likely the language setting, maybe is used for ocr
  * TwoBytesOfData

  * 16 bytes structure
  * values seem to be quite random, except a GUID' constant bits (56-59, and
  * likely 64-65).
  * FourBytesOfLengthFollowedByData
  */
  undoc_StrokesGUID = 0x1c00341a,


  /** TwoBytes declaring the LanguageID without a SortID
   * TwoBytesOfData
   */
  unodc_StrokeLanguage = 0x1000341b,

  /** observed only values 0x00, 0x01, 0x02.
   * 0x00 seems to be the default value, 'handwriting and drawing'
   * 0x01 seems to only occur when drawing is set to 'handwriting only'
   * 0x02 only occurs when modus is 'drawning only'
   * OneByteOfData
   */
  undoc_StrokesModus = 0x0c00341c,

  /** FILETIME object with creation time of the respective stroke
   *
   * eight bytes in FourBytesOfLengthFollowedByData
   */
  undoc_StrokesCreationTime = 0x1c00341d,


  /** \0-seperated list of recognized text
   * It seems the sorting is sorted by likelyhood
   *
   * FourBytesOfLengthFollowedByData
   */
  undoc_StrokesRecognizedText = 0x1c00341e,

  /** seems to be only present when handwriting modus or dual modus is active
   * bool
   */
  undoc_Strokes00341f = 0x8800341f,

  /// might not be writtng when modus is only drawing
  /// in other handwriting modus and dual modus the value seems somewhat
  /// sequential spanning multiple sections FourBytesOfData  0x14003420

  /// maybe two floats marking the position of the strokes blob; unit unknown,
  /// maybe half inches. offset origin undetermined.
  /// FourBytesOfLengthFollowedByData
  undoc_StrokesOffsetsVertHoriz = 0x1c00345b,

  /// does not to be written in all cases
  /// maybe a cache or alternative text
  /// appears in jcidRichTextOENode
  /// FourBytesOfLengthFollowedByData
  undoc_RecognizedText = 0x1c001cc4,

  /** seems to be only present when "undoc_RecognizedText = 0x1c001cc4" is set
   * maybe two allow highlighting when search handwritten stuff
   *
   * seems to contain alot of zero bytes
   * seems to contain similar content across different sections,
   *
   * appears in jcidRichTextOENode
   * FourBytesOfLengthFollowedByData
   */
  undoc_Strokes00345d = 0x1c00345d,

  /** the following values always appear in a group
   */
  undoc_Strokes00349e = 0x1400349e,
  undoc_Strokes00349f = 0x1400349f,
  undoc_Strokes0034a0 = 0x140034a0,
  undoc_Strokes0034a1 = 0x140034a1,
  undoc_Strokes0034a2 = 0x140034a2,
  undoc_Strokes0034a3 = 0x140034a3,
  undoc_Strokes0034a4 = 0x140034a4,
  undoc_Strokes0034a5 = 0x140034a5,

  /** seems to be always 32 byte wide
   */
  undoc_001d4d = 0x1c001d4d,

  // Maybe stores a file name of a section file, but also found FileSyncandWOPI
  // and OneNote_RecycleBin
  undoc_tocSectionName = 0x1c001d6b,
  // usually 16 bytes, likely a guid?
  undoc_tocSectionGUID = 0x1c001d94,

  // maybe the index within the sequence of sections
  undoc_tocSectionIndex = 0x14001cb9,

  // seems to be a color code. 0xFFFFFFFF might be the default (no setting)
  // which differs from COLORREF spec maybe RGBA, big endian uint32, possibly
  // last byte also switches between default color and selected color
  undoc_tocSectionColor = 0x14001cbe,

  /* seems to always have the same value as SchemaRevisionInOrderToRead
   * might also be SchemaRevisionInOrderToWrite
   */
  undoc_SchemaRevisionInOrderToRead = 0x1400348b,

  // mono color background
  undoc_PageBackgroundColor = 0x14001d2a,


  /** used in PackageStoreFile */
  FileDataObject_GUID = 0x1C00343E,
  /** used in PackageStoreFile */
  FileDataObject_InvalidData = 0x0800343D,
  /** used in PackageStoreFile */
  FileDataObject_Extension = 0x1C003424,
};


class PropertyID : public IProperty {
private:
  quint32 m_value;
  PropertyIDs m_id;
  PropertyIDType m_type;

  bool m_boolValue;

public:
  PropertyID();

  PropertyID(const PropertyIDs& id, const PropertyIDType& type);

  PropertyIDs id() const;
  void setId(const PropertyIDs& id);

  PropertyIDType type() const;
  void setType(const PropertyIDType& type);

  quint32 value() const;

  static QString idToString(const PropertyIDs& val);
  static QString typeToString(const PropertyIDType& val);

  /**
   * @brief returns a bool sized value if PropertyID is of a bool type property
   * @return -1 if PropertyID is not bool type, else 0 for false, 1 for true;
   */
  int boolValue() const;
  void setBoolValue(bool boolValue);

  static constexpr quint64 getSizeInFile() { return sizeInFile; }

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;


  static const quint64 sizeInFile = 4;
};

} // namespace priv
} // namespace libmson

#endif // PROPERTYID_H
