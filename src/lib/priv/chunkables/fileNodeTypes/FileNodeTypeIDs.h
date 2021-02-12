#ifndef FILENODETYPEIDS_H
#define FILENODETYPEIDS_H

#include <cstdint>
#include <QString>

namespace libmson {
namespace priv {


/**
 * @brief enumerates types of data structures used in FileNodes
 *
 * represents the structures specified in [MS-ONESTORE] section 2.5.
 *
 * The NullFnd
 *
 *
 */
enum class FileNodeTypeID : uint16_t {
  ObjectSpaceManifestRootFND                 = 0x004,
  ObjectSpaceManifestListReferenceFND        = 0x008,
  ObjectSpaceManifestListStartFND            = 0x00C,
  RevisionManifestListReferenceFND           = 0x010,
  RevisionManifestListStartFND               = 0x014,
  RevisionManifestStart4FND                  = 0x01B,
  RevisionManifestEndFND                     = 0x01C,
  RevisionManifestStart6FND                  = 0x01E,
  RevisionManifestStart7FND                  = 0x01F,
  GlobalIdTableStartFNDX                     = 0x021,
  GlobalIdTableStart2FND                     = 0x022,
  GlobalIdTableEntryFNDX                     = 0x024,
  GlobalIdTableEntry2FNDX                    = 0x025,
  GlobalIdTableEntry3FNDX                    = 0x026,
  GlobalIdTableEndFNDX                       = 0x028,
  ObjectDeclarationWithRefCountFNDX          = 0x02D,
  ObjectDeclarationWithRefCount2FNDX         = 0x02E,
  ObjectRevisionWithRefCountFNDX             = 0x041,
  ObjectRevisionWithRefCount2FNDX            = 0x042,
  RootObjectReference2FNDX                   = 0x059,
  RootObjectReference3FND                    = 0x05A,
  RevisionRoleDeclarationFND                 = 0x05C,
  RevisionRoleAndContextDeclarationFND       = 0x05D,
  ObjectDeclarationFileData3RefCountFND      = 0x072,
  ObjectDeclarationFileData3LargeRefCountFND = 0x073,
  ObjectDataEncryptionKeyV2FNDX              = 0x07C,
  ObjectInfoDependencyOverridesFND           = 0x084,
  DataSignatureGroupDefinitionFND            = 0x08C,
  FileDataStoreListReferenceFND              = 0x090,
  FileDataStoreObjectReferenceFND            = 0x094,
  ObjectDeclaration2RefCountFND              = 0x0A4,
  ObjectDeclaration2LargeRefCountFND         = 0x0A5,
  ObjectGroupListReferenceFND                = 0x0B0,
  ObjectGroupStartFND                        = 0x0B4,
  ObjectGroupEndFND                          = 0x0B8,
  HashedChunkDescriptor2FND                  = 0x0C2,
  ReadOnlyObjectDeclaration2RefCountFND      = 0x0C4,
  ReadOnlyObjectDeclaration2LargeRefCountFND = 0x0C5,
  ChunkTerminatorFND                         = 0x0FF,

  /** when a FileNodeListFragment is not terminated by a ChunkTerminatorFND the
   * Fragment is padded with 0x00. For convenience, that parser always tryies to
   * deserialize the next 4 bytes to a FileNode. This is when the unspecified
   * NullFnd occurs. It is used to break out of the parsing loop and continue
   * with the FileNodeListFragment footer.
   *
   * \todo this is likely a poor design choice. Refactor FileNodeListFragment
   * parser, to let it check before casting to FileNode.
   */
  NullFnd = 0x0,

  /** should never occur and is only used for asserting uninitialized FileNodes.
   */
  InvalidFND = 0xFFF,
};



static QString fileNodeTypeIDString(const FileNodeTypeID type){

  switch (type) {
    case FileNodeTypeID::ObjectSpaceManifestRootFND:
      return QStringLiteral("ObjectSpaceManifestRootFND");

    case FileNodeTypeID::ObjectSpaceManifestListReferenceFND:
      return QStringLiteral("ObjectSpaceManifestListReferenceFND");

    case FileNodeTypeID::ObjectSpaceManifestListStartFND:
      return QStringLiteral("ObjectSpaceManifestListStartFND");

    case FileNodeTypeID::RevisionManifestListReferenceFND:
      return QStringLiteral("RevisionManifestListReferenceFND");

    case FileNodeTypeID::RevisionManifestListStartFND:
      return QStringLiteral("RevisionManifestListStartFND");

    case FileNodeTypeID::RevisionManifestStart4FND:
      return QStringLiteral("RevisionManifestStart4FND");

    case FileNodeTypeID::RevisionManifestEndFND:
      return QStringLiteral("RevisionManifestEndFND");

    case FileNodeTypeID::RevisionManifestStart6FND:
      return QStringLiteral("RevisionManifestStart6FND");

    case FileNodeTypeID::RevisionManifestStart7FND:
      return QStringLiteral("RevisionManifestStart7FND");

    case FileNodeTypeID::GlobalIdTableStartFNDX:
      return QStringLiteral("GlobalIdTableStartFNDX");

    case FileNodeTypeID::GlobalIdTableStart2FND:
      return QStringLiteral("GlobalIdTableStart2FND");

    case FileNodeTypeID::GlobalIdTableEntryFNDX:
      return QStringLiteral("GlobalIdTableEntryFNDX");

    case FileNodeTypeID::GlobalIdTableEntry2FNDX:
      return QStringLiteral("GlobalIdTableEntry2FNDX");

    case FileNodeTypeID::GlobalIdTableEntry3FNDX:
      return QStringLiteral("GlobalIdTableEntry3FNDX");

    case FileNodeTypeID::GlobalIdTableEndFNDX:
      return QStringLiteral("GlobalIdTableEndFNDX");

    case FileNodeTypeID::ObjectDeclarationWithRefCountFNDX:
      return QStringLiteral("ObjectDeclarationWithRefCountFNDX");

    case FileNodeTypeID::ObjectDeclarationWithRefCount2FNDX:
      return QStringLiteral("ObjectDeclarationWithRefCount2FNDX");

    case FileNodeTypeID::ObjectRevisionWithRefCountFNDX:
      return QStringLiteral("ObjectRevisionWithRefCountFNDX");

    case FileNodeTypeID::ObjectRevisionWithRefCount2FNDX:
      return QStringLiteral("ObjectRevisionWithRefCount2FNDX");

    case FileNodeTypeID::RootObjectReference2FNDX:
      return QStringLiteral("RootObjectReference2FNDX");

    case FileNodeTypeID::RootObjectReference3FND:
      return QStringLiteral("RootObjectReference3FND");

    case FileNodeTypeID::RevisionRoleDeclarationFND:
      return QStringLiteral("RevisionRoleDeclarationFND");

    case FileNodeTypeID::RevisionRoleAndContextDeclarationFND:
      return QStringLiteral("RevisionRoleAndContextDeclarationFND");

    case FileNodeTypeID::ObjectDeclarationFileData3RefCountFND:
      return QStringLiteral("ObjectDeclarationFileData3RefCountFND");

    case FileNodeTypeID::ObjectDeclarationFileData3LargeRefCountFND:
      return QStringLiteral("ObjectDeclarationFileData3LargeRefCountFND");

    case FileNodeTypeID::ObjectDataEncryptionKeyV2FNDX:
      return QStringLiteral("ObjectDataEncryptionKeyV2FNDX");

    case FileNodeTypeID::ObjectInfoDependencyOverridesFND:
      return QStringLiteral("ObjectInfoDependencyOverridesFND");

    case FileNodeTypeID::DataSignatureGroupDefinitionFND:
      return QStringLiteral("DataSignatureGroupDefinitionFND");

    case FileNodeTypeID::FileDataStoreListReferenceFND:
      return QStringLiteral("FileDataStoreListReferenceFND");

    case FileNodeTypeID::FileDataStoreObjectReferenceFND:
      return QStringLiteral("FileDataStoreObjectReferenceFND");

    case FileNodeTypeID::ObjectDeclaration2RefCountFND:
      return QStringLiteral("ObjectDeclaration2RefCountFND");

    case FileNodeTypeID::ObjectDeclaration2LargeRefCountFND:
      return QStringLiteral("ObjectDeclaration2LargeRefCountFND");

    case FileNodeTypeID::ObjectGroupListReferenceFND:
      return QStringLiteral("ObjectGroupListReferenceFND");

    case FileNodeTypeID::ObjectGroupStartFND:
      return QStringLiteral("ObjectGroupStartFND");

    case FileNodeTypeID::ObjectGroupEndFND:
      return QStringLiteral("ObjectGroupEndFND");

    case FileNodeTypeID::HashedChunkDescriptor2FND:
      return QStringLiteral("HashedChunkDescriptor2FND");

    case FileNodeTypeID::ReadOnlyObjectDeclaration2RefCountFND:
      return QStringLiteral("ReadOnlyObjectDeclaration2RefCountFND");

    case FileNodeTypeID::ReadOnlyObjectDeclaration2LargeRefCountFND:
      return QStringLiteral("ReadOnlyObjectDeclaration2LargeRefCountFND");

    case FileNodeTypeID::ChunkTerminatorFND:
      return QStringLiteral("ChunkTerminatorFND");

    case FileNodeTypeID::NullFnd:
      return QStringLiteral("NullFnd");

    case FileNodeTypeID::InvalidFND:
      return QStringLiteral("InvalidFND");

    default:
      return QString();
  }

}


} // namespace priv
} // namespace libmson

#endif // FILENODETYPEIDS_H
