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


  /** ID occured in the ArrayOfPropertyValues which inherits a TextRunData
   * PropertyID
   *
   * PropertySet
   *
   *
   * Tags? :
   * https://github.com/msiemens/onenote.rs/blob/master/src/one/property/mod.rs
   */
  undoc_TextRunDataPropertyArray = 0x44000811,

  /** seems to be a float, maybe some margins
   *
   * FourBytesOfData
   */
  undoc_float001c9e = 0x14001c9e,
  /** seems to be a float, maybe some margins
   *
   * FourBytesOfData
   */
  undoc_float001c9f = 0x14001c9f,
  /** seems to be a float, maybe some margins
   *
   * FourBytesOfData
   */
  undoc_float001ca0 = 0x14001ca0,
  /** seems to be a float, maybe some margins
   *
   * FourBytesOfData
   */
  undoc_float001ca1 = 0x14001ca1,


  /// maybe the index within the sequence of sections
  SectionOrderingIndex = 0x14001cb9,

  // seems to be a color code. 0xFFFFFFFF might be the default (no setting)
  // which differs from COLORREF spec maybe RGBA, big endian uint32, possibly
  // last byte also switches between default color and selected color
  SectionColor = 0x14001cbe,

  /// does not to be written in all cases
  /// maybe a cache or alternative text
  /// appears in jcidRichTextOENode
  /// FourBytesOfLengthFollowedByData
  RecognizedText = 0x1c001cc4,

  // Maybe stores a file name of a section file, but also found FileSyncandWOPI
  // and OneNote_RecycleBin
  SectionName = 0x1c001d6b,
  // usually 16 bytes, likely a guid?
  SectionGUID = 0x1c001d94,


  /** 32 byte blob
   *
   * seems to be only present when undoc_TextServiceFrameworkBlob is in same
   * ObjectSpaceObjectPropSet
   *
   * observed sequences
   * 03090000b60f00002c0a0000b60f00002c0a0000a617000003090000a6170000
   * 090f0000bc530000fb0f0000bc530000fb0f000074560000090f000074560000
   * 10100000ab190000fe3500006d1e0000e2350000491f0000f50f0000881a0000
   * 10100000ac190000fe3500006d1e0000e2350000491f0000f40f0000881a0000
   * 10100000b0190000fe3500006d1e0000e2350000481f0000f40f00008c1a0000
   * 130100007d010000220100007d010000220100008c010000130100008c010000
   * 1301000092010000220100009201000022010000a101000013010000a1010000
   * 1a0d00001b6900007c1300007466000066140000a7680000040e00004e6b0000
   * 271a0000ee0b0000604100009c0f00000a400000d71d0000d1180000281a0000
   * 370f0000421400000b250000421400000b25000012170000370f000012170000
   * 370f00005d110000413f00005d110000413f000054200000370f000054200000
   * 3b0d0000560d000099490000590c0000c74900008a1700006a0d000087180000
   * 401300003a5c0000331400003a5c000033140000355d000040130000355d0000
   * 410a0000280c00003f0b0000280c00003f0b00001e110000410a00001e110000
   * 42100000c8120000b63400002a150000a8340000fb1500003510000099130000
   * 42100000ca120000b73400002c150000a9340000fc150000351000009a130000
   * 5301000092010000620100009201000062010000a101000053010000a1010000
   * 5619000007f411009d19000040e81100ce1c000053e81100881c00001bf41100
   * 5a3d000066370000693d000066370000693d0000753700005a3d000075370000
   * 5d1800000c0a0000291b000011360000bd0f0000cb360000f10c0000c60a0000
   * 650a0000060c00004c160000d60d00008a150000d5120000a209000005110000
   * 680100007d010000770100007d010000770100008c010000680100008c010000
   * 692900008a0800006d3800000b0c0000d5360000df120000d12700005e0f0000
   * 6b3f0000183e00007a3f0000183e00007a3f0000273e00006b3f0000273e0000
   * 6d0d0000f466000036130000f466000036130000666800006d0d000066680000
   * 7012000005080000ce18000005080000ce1800001b1d0000701200001b1d0000
   * 77190000a10f00000c2f0000a10f00000c2f00000d240000771900000d240000
   * 7b020000df3a00008a020000df3a00008a020000ee3a00007b020000ee3a0000
   * 7c21000023190000590800001f1900005a080000890e00007e2100008d0e0000
   * 84280000410a00007b370000410a00007b370000c61c000084280000c61c0000
   * 871100005d110000922100005d11000092210000831e000087110000831e0000
   * 8b0d0000220d00005b1e0000b90c0000961e000043160000c60d0000ab160000
   * 8d2e0000601a0000413f0000601a0000413f0000731b00008d2e0000731b0000
   * 901800001e0a0000371b0000ee3c0000b90f0000883d0000120d0000b80a0000
   * 930f0000e10f0000ca3f0000d9130000803e000088230000480e0000901f0000
   * 9a1d0000672100004647000067210000464700005d3100009a1d00005d310000
   * 9a1d000068210000e940000068210000e94000005e3100009a1d00005e310000
   * a52c0000251800004f0d000023180000500d00000e0d0000a62c0000110d0000
   * a840000092010000b740000092010000b7400000a1010000a8400000a1010000
   * bf3f000053010000ce3f000053010000ce3f000062010000bf3f000062010000
   * ca0d0000e9630000720e0000e9630000720e0000b2640000ca0d0000b2640000
   * cb0d00003f0c0000f34500000e0e000092450000d21900006a0d000003180000
   * cd0e0000341b000026220000341b000026220000041e0000cd0e0000041e0000
   * cf1900007a0d0000f06100004f11000031610000511f0000101900007d1b0000
   * cf1900007a0d0000f16100004f11000032610000521f0000101900007c1b0000
   * d20d0000910c00007f4000009f0e00000a400000ec1900005d0d0000de170000
   * d3400000333b0000e2400000333b0000e2400000423b0000d3400000423b0000
   * d8330000b425000061440000b42500006144000007270000d833000007270000
   * e02f0000a90b000052410000a90b000052410000240e0000e02f0000240e0000
   * e70e0000821a00003e2200005f1d000024220000101e0000cd0e0000341b0000
   * e91c00008c720000fd1d00005a6d0000861f0000ac6d0000711e0000dd720000
   * ea1f0000fc16000033260000fc1600003326000027170000ea1f000027170000
   * eb0d00009a0c000048220000e50d000097210000c31800003a0d000078170000
   * f50f00006b0a0000101800006b0a00001018000066170000f50f000066170000
   * fd4000009b3c00000c4100009b3c00000c410000aa3c0000fd400000aa3c0000
   *
   */
  TextServicesFrameworkBlob = 0x1c001d4d,


  /** Four bytes
   *
   * seems to be only present when undoc_TextServiceFrameworkBlob is in same
   * ObjectSpaceObjectPropSet
   *
   * Observed these byte sequences
   * 01000000
   * 02000000
   * 03000000
   * 04000000
   * 05000000
   * 06000000
   * 07000000
   * 08000000
   * 09000000
   * 0a000000
   * 0c000000
   * 0d000000
   * 0e000000
   * 10000000
   * 16000000
   * 18000000
   *
   * maybe flags, of 0x01, 0x02, 0x04, 0x08, and 0x10
   *
   */
  TextServiesFrameworkFlag1 = 0x14001d4e,


  /**
   * FourBytes
   *
   * Flags?
   *
   * Observed these byte sequences
   * 01000000
   * 02000000
   * 03000000
   * 04000000
   * 05000000
   * 06000000
   * 08000000
   * 09000000
   * 0a000000
   * 0b000000
   * 0c000000
   * 0d000000
   * 0e000000
   * 0f000000
   * 10000000
   * 11000000
   * 12000000
   * 13000000
   */
  undoc_001d5c = 0x14001d5c,

  /** Seems to always have odd sizes, such as 17,33,49,81
   * FourBytesOfLengthFollowedByData
   */
  undoc_001d5d = 0x14001d5d,

  /** Likely is used for labeling multi-author document changes
   * Uses two letters for author with one family name and one given name (in
   * german, and english)
   */
  undoc_AuthorInitials = 0x1c001df8,

  /** some windows live stuff, eg:
   * <resolutionId provider="Windows Live" hash="abcdefg"> <localId
   * cid="abcdefg"/></resolutionId>
   */
  ResolutionID = 0x1c001e30,

  /** ObjectID which points to undoc_jciddrawingToolData(0x00120048), the tool
   * settings which contains:
   * * undoc_Undetermined64byteBlock/ 0x1c00340a
   * * undoc_StrokesColor
   * * undoc_StrokesToolSizeHeight
   * * undoc_StrokesToolSizeWidth
   */
  InkStrokeProperties = 0x20003409,


  /** ISF Metric table
   *
   * FourBytesOfLengthFollowedByData, at least 64 bytes
   *  Encoding:
   *  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F |
   *  | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
   *  | Tag Guid (16 bytes) ||||||||||||||||
   *  | logic min (int32) |||| logic max (int32) |||| unit enum (32 bits] |||| resolution (float32) ||||
   *
   * X = '{598A6A8F-52C0-4BA0-93AF-AF357411A561}'
   * Y = '{B53F9F75-04E0-4498-A7EE-C30DBB5A9011}'
   *
   * Reference:
   * https://docs.microsoft.com/de-de/uwp/specifications/ink-serialized-format
   *
   */
  InkMetricTable = 0x1c00340a,

  /** Blob containing serialized strokes in native format
   *
   * Seems to correlate with InkStroke class from onenote api
   *
   * Multi-byte encoding according to:
   * https://docs.microsoft.com/de-de/uwp/specifications/ink-serialized-format
   */
  InkPath = 0x1c00340b,

  /// \todo find ToolSettings whether it's round or square
  /** float32 for the tool height, 1 unit represents 0.01mm
   */
  InkPenHeight = 0x1400340c,

  /** float32 for the tool width, 1 unit represents 0.01mm
   *
   */
  InkPenWidth = 0x1400340d,

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
  InkColor = 0x1400340f,

  /**
   * \todo why is 003411 byte and bool?
   * Nameing source: https://github.com/msiemens/onenote.rs/blob/master/src/one/property/mod.rs
   */
  InkIgnorePressure = 0x08003411,
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
   * Nameing source: https://github.com/msiemens/onenote.rs/blob/master/src/one/property/mod.rs
   */
  InkData = 0x20003415,

  /** ArrayofObjectIDs
   *  lives within undoc_jcidDrawingGroupNode(0x0002003b)
   *
   * points to undoc_jcidDrawingNodes which are likely
   * contain the strokes for which matches according to
   * undoc_StrokesRecognizedText have been found
   *
   * Nameing source: https://github.com/msiemens/onenote.rs/blob/master/src/one/property/mod.rs
   */
  InkStrokes = 0x24003416,

  /** Bounding box of an ink object
   *
   *  16 byte object containing 4 uint32_t
   *
   *  \todo specify unit, and order
   *
   * only present when Handwritting modus is active?
   *
   * Nameing source: https://github.com/msiemens/onenote.rs/blob/master/src/one/property/mod.rs
   */
  InkBoundingBox = 0x1c003418,

  /** squential number likely indicating the input order
   * FourBytesOfData
   */
  InkStorkeOrderingIndex = 0x14003419,
  /** likely the language setting, maybe is used for ocr
  * TwoBytesOfData


  * Guid for the referencing ink object
  *
  * 16 bytes structure
  */
  InkGUID = 0x1c00341a,


  /** TwoBytes declaring the LanguageID without a SortID
   * TwoBytesOfData
   */
  unodc_StrokeLanguage = 0x1000341b,

  /** Switch which describes the drawing mode used to create the referencing ink object
   *
   *  One byte of data
   *
   *  | Value | Feature                 |
   *  | ----- | ----------------------- |
   *  | 0x00  | handwriting and drawing |
   *  | 0x01  | handwriting only        |
   *  | 0x02  | drawing only            |
   *
   *
   *  https://docs.microsoft.com/en-us/archive/blogs/johnguin/the-inkbias-registry-key-in-onenote
   */
  InkBias = 0x0c00341c,

  /** FILETIME object with creation time of the respective stroke
   *
   * eight bytes in FourBytesOfLengthFollowedByData
   */
  InkCreationTime = 0x1c00341d,


  /** \0-seperated list of recognized text in the ink object
   * It seems the sorting is by likelyhood
   *
   * FourBytesOfLengthFollowedByData
   */
  InkRecognizedText = 0x1c00341e,

  /** seems to be only present when handwriting modus or dual modus is active
   * if that modus is active this bool is set to true
   * bool
   */
  undoc_Strokes00341f = 0x0800341f,

  /*
   * FourBytesOfData
   */
  undoc_Strokes003420 = 0x14003420,

  /// might not be writtng when modus is only drawing
  /// in other handwriting modus and dual modus the value seems somewhat
  /// sequential spanning multiple sections FourBytesOfData  0x14003420

  /// maybe two floats marking the position of the strokes blob; unit unknown,
  /// maybe half inches. offset origin undetermined.
  /// FourBytesOfLengthFollowedByData
  undoc_StrokesOffsetsVertHoriz = 0x1c00345b,


  /** seems to be only present when "undoc_RecognizedText = 0x1c001cc4" is set
   *
   * maybe a MS Text Service Framework blob
   * Found GUIDs in
   * https://github.com/NyaRuRu/TSF-TypeLib/blob/master/TSF.TypeLib/src/msctf.cs
   *
   * appears in jcidRichTextOENode
   * FourBytesOfLengthFollowedByData
   */
  undoc_TextServicesFrameworkBlob = 0x1c00345d,

  //the following values always appear in a group
  // EmbeddedInkStartX
  // EmbeddedInkStartY
  // EmbeddedInkWidth
  // EmbeddedInkHeight
  // EmbeddedInkOffsetHoriz
  // EmbeddedInkHeight
  // undoc_Strokes0034a4
  // undoc_Strokes0034a5


  /** Initial x coordinate of an embedded ink object
   *
   *  Source:
   *  https://github.com/msiemens/onenote.rs/blob/master/src/one/property/mod.rs
   */
  EmbeddedInkStartX = 0x1400349e,

  /** Initial y coordinate of an embedded ink object
   *
   *  Source:
   *  https://github.com/msiemens/onenote.rs/blob/master/src/one/property/mod.rs
   */
  EmbeddedInkStartY = 0x1400349f,

  /** Width of an embedded ink object
   *
   *  Source:
   *  https://github.com/msiemens/onenote.rs/blob/master/src/one/property/mod.rs
   *
   */
  EmbeddedInkWidth = 0x140034a0,

  /** Height of an embedded ink object
   *
   *  Source:
   *  https://github.com/msiemens/onenote.rs/blob/master/src/one/property/mod.rs
   *
   */
  EmbeddedInkHeight = 0x140034a1,

  /** Horizontal offset of an embedded ink object
   *  \todo from where?
   *
   *  Source:
   *  https://github.com/msiemens/onenote.rs/blob/master/src/one/property/mod.rs
   *
   */
  EmbeddedInkOffsetHoriz = 0x140034a2,

  /** Vertical offset of an embedded ink object
   *  \todo from where?
   *
   *  Source:
   *  https://github.com/msiemens/onenote.rs/blob/master/src/one/property/mod.rs
   *
   */
  EmbeddedInkOffsetVert = 0x140034a3,


  undoc_Strokes0034a4 = 0x140034a4,
  undoc_Strokes0034a5 = 0x140034a5,


  /* seems to always have the same value as SchemaRevisionInOrderToRead
   * might also be SchemaRevisionInOrderToWrite
   */
  undoc_SchemaRevisionInOrderToRead = 0x1400348b,

  // mono color background
  PageBackgroundColor = 0x14001d2a,


  /** used in PackageStoreFile */
  FileDataObject_GUID = 0x1C00343E,
  /** used in PackageStoreFile */
  FileDataObject_InvalidData = 0x0800343D,
  /** used in PackageStoreFile */
  FileDataObject_Extension = 0x1C003424,


  /// the following undocumented IDs where observed but not yet specified

  // ArrayOfObjectSpaceIDs
  undoc_0x2c001d62 = 0x2c001d62,

  // bools
  undoc_0x08001c32 = 0x08001c32,
  undoc_0x08001d85 = 0x08001d85,
  undoc_0x08001d8d = 0x08001d8d,
  undoc_0x08001dce = 0x08001dce,
  undoc_0x08001dec = 0x08001dec,
  undoc_0x08001e24 = 0x08001e24,
  undoc_0x08001e2c = 0x08001e2c,
  undoc_0x08003405 = 0x08003405,
  undoc_0x08003406 = 0x08003406,

  undoc_0x08003495 = 0x08003495,
  undoc_0x080034aa = 0x080034aa,
  undoc_0x080034dd = 0x080034dd,

  // FourBytesOfData
  undoc_0x14001c28 = 0x14001c28,
  undoc_0x14001c48 = 0x14001c48,
  undoc_0x14001c49 = 0x14001c49,
  undoc_0x14001c4a = 0x14001c4a,
  undoc_0x14001c4b = 0x14001c4b,
  undoc_0x14001c99 = 0x14001c99,
  undoc_0x14001cfd = 0x14001cfd,
  undoc_0x14001df6 = 0x14001df6,
  undoc_0x14001df9 = 0x14001df9,
  undoc_0x1400344f = 0x1400344f,
  undoc_0x14003450 = 0x14003450,
  undoc_0x14003481 = 0x14003481,
  undoc_0x140035a4 = 0x140035a4,
  undoc_0x140035d1 = 0x140035d1,
  undoc_0x140035d2 = 0x140035d2,

  // FourBytesOfLengthFollowedByData
  undoc_0x1c001c97 = 0x1c001c97,
  undoc_0x1c001c98 = 0x1c001c98,
  undoc_0x1c001ca3 = 0x1c001ca3,
  undoc_0x1c001ca5 = 0x1c001ca5,
  undoc_0x1c001ca6 = 0x1c001ca6,
  undoc_0x1c001ca7 = 0x1c001ca7,
  undoc_0x1c001cc8 = 0x1c001cc8,
  undoc_0x1c001cda = 0x1c001cda,
  undoc_0x1c001d4c = 0x1c001d4c,
  undoc_0x1c001d5d = 0x1c001d5d,
  undoc_0x1c001d61 = 0x1c001d61,
  undoc_0x1c001d84 = 0x1c001d84,
  undoc_0x1c001daa = 0x1c001daa,
  undoc_0x1c001dbe = 0x1c001dbe,
  undoc_0x1c001dbf = 0x1c001dbf,
  undoc_0x1c001dcf = 0x1c001dcf,
  undoc_0x1c001dfb = 0x1c001dfb,
  undoc_0x1c001dfc = 0x1c001dfc,
  // OneByteOfData
  undoc_0x0c001cc0 = 0x0c001cc0,
  undoc_0x0c001d4f = 0x0c001d4f,
  undoc_0x0c003452 = 0x0c003452,

  //TwoBytesOfData
  undoc_0x1000344e = 0x1000344e,
  undoc_0x10003453 = 0x10003453,

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

  QString idToString() const;
  static QString idToString(const PropertyIDs& val);

  QString typeToString() const;
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
