#ifndef ENUMS_H
#define ENUMS_H

#include <QtCore/qglobal.h>

namespace MSONcommon {

enum class FileNodeTypeID : quint16 {
  ObjectSpaceManifestRootFND = 0x004,
  ObjectSpaceManifestListReferenceFND = 0x008,
  ObjectSpaceManifestListStartFND = 0x00C,
  RevisionManifestListReferenceFND = 0x010,
  RevisionManifestListStartFND = 0x014,
  RevisionManifestStart4FND = 0x01B,
  RevisionManifestEndFND = 0x01C,
  RevisionManifestStart6FND = 0x01E,
  RevisionManifestStart7FND = 0x01F,
  GlobalIdTableStartFNDX = 0x021,
  GlobalIdTableStart2FND = 0x022,
  GlobalIdTableEntryFNDX = 0x024,
  GlobalIdTableEntry2FNDX = 0x025,
  GlobalIdTableEntry3FNDX = 0x026,
  GlobalIdTableEndFNDX = 0x028,
  ObjectDeclarationWithRefCountFNDX = 0x02D,
  ObjectDeclarationWithRefCount2FNDX = 0x02E,
  ObjectRevisionWithRefCountFNDX = 0x041,
  ObjectRevisionWithRefCount2FNDX = 0x042,
  RootObjectReference2FNDX = 0x059,
  RootObjectReference3FND = 0x05A,
  RevisionRoleDeclarationFND = 0x05C,
  RevisionRoleAndContextDeclarationFND = 0x05D,
  ObjectDeclarationFileData3RefCountFND = 0x072,
  ObjectDeclarationFileData3LargeRefCountFND = 0x073,
  ObjectDataEncryptionKeyV2FNDX = 0x07C,
  ObjectInfoDependencyOverridesFND = 0x084,
  DataSignatureGroupDefinitionFND = 0x08C,
  FileDataStoreListReferenceFND = 0x090,
  FileDataStoreObjectReferenceFND = 0x094,
  ObjectDeclaration2RefCountFND = 0x0A4,
  ObjectDeclaration2LargeRefCountFND = 0x0A5,
  ObjectGroupListReferenceFND = 0x0B0,
  ObjectGroupStartFND = 0x0B4,
  ObjectGroupEndFND = 0x0B8,
  HashedChunkDescriptor2FND = 0x0C2,
  ReadOnlyObjectDeclaration2RefCountFND = 0x0C4,
  ReadOnlyObjectDeclaration2LargeRefCountFND = 0x0C5,
  ChunkTerminatorFND = 0x0FF,
  InvalidFND = 0xFFF,
};

enum class PropertyIDType : quint8 {
  None = 0x0,
  NoData = 0x1,
  Bool = 0x2,
  OneByteOfData = 0x3,
  TwoBytesOfData = 0x4,
  FourBytesOfData = 0x5,
  EightBytesOfData = 0x6,
  FourBytesOfLengthFollowedByData = 0x7,
  ObjectID = 0x8,
  ArrayOfObjectIDs = 0x9,
  ObjectSpaceID = 0xA,
  ArrayOfObjectSpaceIDs = 0xB,
  ContextID = 0xC,
  ArrayOfContextIDs = 0xD,
  ArrayOfPropertyValues = 0x10,
  PropertySet = 0x11,
  InvalidType = 0xFF,
};



enum class JCIDs : quint32 {
jcidReadOnlyPersistablePropertyContainerForAuthor = 0x00120001,
jcidPersistablePropertyContainerForTOC = 0x00020001,
jcidPersistablePropertyContainerForTOCSection = 0x00020001,
jcidSectionNode = 0x00060007,
jcidPageSeriesNode = 0x00060008,
jcidPageNode = 0x0006000B,
jcidOutlineNode = 0x0006000C,
jcidOutlineElementNode = 0x0006000D,
jcidRichTextOENode = 0x0006000E,
jcidImageNode = 0x00060011,
jcidNumberListNode = 0x00060012,
jcidOutlineGroup = 0x00060019,
jcidTableNode = 0x00060022,
jcidTableRowNode = 0x00060023,
jcidTableCellNode = 0x00060024,
jcidTitleNode = 0x0006002C,
jcidPageMetaData = 0x00020030,
jcidSectionMetaData = 0x00020031,
jcidEmbeddedFileNode = 0x00060035,
jcidPageManifestNode = 0x00060037,
jcidConflictPageMetaData = 0x00020038,
jcidVersionHistoryContent = 0x0006003C,
jcidVersionProxy = 0x0006003D,
jcidNoteTagSharedDefinitionContainer = 0x00120043,
jcidRevisionMetaData = 0x00020044,
jcidVersionHistoryMetaData = 0x00020046,
jcidParagraphStyleObject = 0x0012004D,
jcidParagraphStyleObjectForText = 0x0012004D,
none = 0x00000000,


undoc_drawing = 0x00020047,
undoc_shape = 0x00060014,
};


enum class Charset : quint8 {
ANSI_CHARSET = 0,
DEFAULT_CHARSET = 1,
SYMBOL_CHARSET = 2,
MAC_CHARSET = 77,
SHIFTJIS_CHARSET = 128,
HANGUL_CHARSET = 129,
JOHAB_CHARSET = 130,
GB2312_CHARSET = 134,
CHINESEBIG5_CHARSET = 136,
GREEK_CHARSET = 161,
TURKISH_CHARSET = 162,
VIETNAMESE_CHARSET = 163,
HEBREW_CHARSET = 177,
ARABIC_CHARSET = 178,
BALTIC_CHARSET = 186,
RUSSIAN_CHARSET = 204,
THAI_CHARSET = 222,
EASTEUROPE_CHARSET = 238,
OEM_CHARSET = 255,
};

} // namespace MSONcommon

#endif // ENUMS_H
