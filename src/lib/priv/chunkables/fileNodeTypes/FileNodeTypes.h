#ifndef FILENODETYPES_H
#define FILENODETYPES_H


#include "ChunkTerminatorFND.h"
#include "DataSignatureGroupDefinitionFND.h"
#include "FileDataStoreListReferenceFND.h"
#include "FileDataStoreObjectReferenceFND.h"
#include "GlobalIdTableEndFNDX.h"
#include "GlobalIdTableEntry2FNDX.h"
#include "GlobalIdTableEntry3FNDX.h"
#include "GlobalIdTableEntryFNDX.h"
#include "GlobalIdTableStart2FND.h"
#include "GlobalIdTableStartFNDX.h"
#include "HashedChunkDescriptor2FND.h"
#include "ObjectDataEncryptionKeyV2FNDX.h"
#include "ObjectDeclaration2LargeRefCountFND.h"
#include "ObjectDeclaration2RefCountFND.h"
#include "ObjectDeclarationFileData3LargeRefCountFND.h"
#include "ObjectDeclarationFileData3RefCountFND.h"
#include "ObjectDeclarationWithRefCount2FNDX.h"
#include "ObjectDeclarationWithRefCountFNDX.h"
#include "ObjectGroupEndFND.h"
#include "ObjectGroupListReferenceFND.h"
#include "ObjectGroupStartFND.h"
#include "ObjectInfoDependencyOverridesFND.h"
#include "ObjectRevisionWithRefCount2FNDX.h"
#include "ObjectRevisionWithRefCountFNDX.h"
#include "ObjectSpaceManifestListReferenceFND.h"
#include "ObjectSpaceManifestListStartFND.h"
#include "ObjectSpaceManifestRootFND.h"
#include "ReadOnlyObjectDeclaration2LargeRefCountFND.h"
#include "ReadOnlyObjectDeclaration2RefCountFND.h"
#include "RevisionManifestEndFND.h"
#include "RevisionManifestListReferenceFND.h"
#include "RevisionManifestListStartFND.h"
#include "RevisionManifestStart4FND.h"
#include "RevisionManifestStart6FND.h"
#include "RevisionManifestStart7FND.h"
#include "RevisionRoleAndContextDeclarationFND.h"
#include "RevisionRoleDeclarationFND.h"
#include "RootObjectReference2FNDX.h"
#include "RootObjectReference3FND.h"


namespace libmson {
namespace priv {
typedef std::shared_ptr<ChunkTerminatorFND> ChunkTerminatorFND_SPtr_t;
typedef std::shared_ptr<DataSignatureGroupDefinitionFND> DataSignatureGroupDefinitionFND_SPtr_t;
typedef std::shared_ptr<FileDataStoreListReferenceFND> FileDataStoreListReferenceFND_SPtr_t;
typedef std::shared_ptr<FileDataStoreObjectReferenceFND> FileDataStoreObjectReferenceFND_SPtr_t;
typedef std::shared_ptr<GlobalIdTableEndFNDX> GlobalIdTableEndFNDX_SPtr_t;
typedef std::shared_ptr<GlobalIdTableEntry2FNDX> GlobalIdTableEntry2FNDX_SPtr_t;
typedef std::shared_ptr<GlobalIdTableEntry3FNDX> GlobalIdTableEntry3FNDX_SPtr_t;
typedef std::shared_ptr<GlobalIdTableEntryFNDX> GlobalIdTableEntryFNDX_SPtr_t;
typedef std::shared_ptr<GlobalIdTableStart2FND> GlobalIdTableStart2FND_SPtr_t;
typedef std::shared_ptr<GlobalIdTableStartFNDX> GlobalIdTableStartFNDX_SPtr_t;
typedef std::shared_ptr<HashedChunkDescriptor2FND> HashedChunkDescriptor2FND_SPtr_t;
typedef std::shared_ptr<ObjectDataEncryptionKeyV2FNDX> ObjectDataEncryptionKeyV2FNDX_SPtr_t;
typedef std::shared_ptr<ObjectDeclaration2LargeRefCountFND> ObjectDeclaration2LargeRefCountFND_SPtr_t;
typedef std::shared_ptr<ObjectDeclaration2RefCountFND> ObjectDeclaration2RefCountFND_SPtr_t;
typedef std::shared_ptr<ObjectDeclarationFileData3LargeRefCountFND> ObjectDeclarationFileData3LargeRefCountFND_SPtr_t;
typedef std::shared_ptr<ObjectDeclarationFileData3RefCountFND> ObjectDeclarationFileData3RefCountFND_SPtr_t;
typedef std::shared_ptr<ObjectDeclarationWithRefCount2FNDX> ObjectDeclarationWithRefCount2FNDX_SPtr_t;
typedef std::shared_ptr<ObjectDeclarationWithRefCountFNDX> ObjectDeclarationWithRefCountFNDX_SPtr_t;
typedef std::shared_ptr<ObjectGroupEndFND> ObjectGroupEndFND_SPtr_t;
typedef std::shared_ptr<ObjectGroupListReferenceFND> ObjectGroupListReferenceFND_SPtr_t;
typedef std::shared_ptr<ObjectGroupStartFND> ObjectGroupStartFND_SPtr_t;
typedef std::shared_ptr<ObjectInfoDependencyOverridesFND> ObjectInfoDependencyOverridesFND_SPtr_t;
typedef std::shared_ptr<ObjectRevisionWithRefCount2FNDX> ObjectRevisionWithRefCount2FNDX_SPtr_t;
typedef std::shared_ptr<ObjectRevisionWithRefCountFNDX> ObjectRevisionWithRefCountFNDX_SPtr_t;
typedef std::shared_ptr<ObjectSpaceManifestListReferenceFND> ObjectSpaceManifestListReferenceFND_SPtr_t;
typedef std::shared_ptr<ObjectSpaceManifestListStartFND> ObjectSpaceManifestListStartFND_SPtr_t;
typedef std::shared_ptr<ObjectSpaceManifestRootFND> ObjectSpaceManifestRootFND_SPtr_t;
typedef std::shared_ptr<ReadOnlyObjectDeclaration2LargeRefCountFND> ReadOnlyObjectDeclaration2LargeRefCountFND_SPtr_t;
typedef std::shared_ptr<ReadOnlyObjectDeclaration2RefCountFND> ReadOnlyObjectDeclaration2RefCountFND_SPtr_t;
typedef std::shared_ptr<RevisionManifestEndFND> RevisionManifestEndFND_SPtr_t;
typedef std::shared_ptr<RevisionManifestListReferenceFND> RevisionManifestListReferenceFND_SPtr_t;
typedef std::shared_ptr<RevisionManifestListStartFND> RevisionManifestListStartFND_SPtr_t;
typedef std::shared_ptr<RevisionManifestStart4FND> RevisionManifestStart4FND_SPtr_t;
typedef std::shared_ptr<RevisionManifestStart6FND> RevisionManifestStart6FND_SPtr_t;
typedef std::shared_ptr<RevisionManifestStart7FND> RevisionManifestStart7FND_SPtr_t;
typedef std::shared_ptr<RevisionRoleAndContextDeclarationFND> RevisionRoleAndContextDeclarationFND_SPtr_t;
typedef std::shared_ptr<RevisionRoleDeclarationFND> RevisionRoleDeclarationFND_SPtr_t;
typedef std::shared_ptr<RootObjectReference2FNDX> RootObjectReference2FNDX_SPtr_t;
typedef std::shared_ptr<RootObjectReference3FND> RootObjectReference3FND_SPtr_t;


typedef std::weak_ptr<ChunkTerminatorFND> ChunkTerminatorFND_WPtr_t;
typedef std::weak_ptr<DataSignatureGroupDefinitionFND> DataSignatureGroupDefinitionFND_WPtr_t;
typedef std::weak_ptr<FileDataStoreListReferenceFND> FileDataStoreListReferenceFND_WPtr_t;
typedef std::weak_ptr<FileDataStoreObjectReferenceFND> FileDataStoreObjectReferenceFND_WPtr_t;
typedef std::weak_ptr<GlobalIdTableEndFNDX> GlobalIdTableEndFNDX_WPtr_t;
typedef std::weak_ptr<GlobalIdTableEntry2FNDX> GlobalIdTableEntry2FNDX_WPtr_t;
typedef std::weak_ptr<GlobalIdTableEntry3FNDX> GlobalIdTableEntry3FNDX_WPtr_t;
typedef std::weak_ptr<GlobalIdTableEntryFNDX> GlobalIdTableEntryFNDX_WPtr_t;
typedef std::weak_ptr<GlobalIdTableStart2FND> GlobalIdTableStart2FND_WPtr_t;
typedef std::weak_ptr<GlobalIdTableStartFNDX> GlobalIdTableStartFNDX_WPtr_t;
typedef std::weak_ptr<HashedChunkDescriptor2FND> HashedChunkDescriptor2FND_WPtr_t;
typedef std::weak_ptr<ObjectDataEncryptionKeyV2FNDX> ObjectDataEncryptionKeyV2FNDX_WPtr_t;
typedef std::weak_ptr<ObjectDeclaration2LargeRefCountFND> ObjectDeclaration2LargeRefCountFND_WPtr_t;
typedef std::weak_ptr<ObjectDeclaration2RefCountFND> ObjectDeclaration2RefCountFND_WPtr_t;
typedef std::weak_ptr<ObjectDeclarationFileData3LargeRefCountFND> ObjectDeclarationFileData3LargeRefCountFND_WPtr_t;
typedef std::weak_ptr<ObjectDeclarationFileData3RefCountFND> ObjectDeclarationFileData3RefCountFND_WPtr_t;
typedef std::weak_ptr<ObjectDeclarationWithRefCount2FNDX> ObjectDeclarationWithRefCount2FNDX_WPtr_t;
typedef std::weak_ptr<ObjectDeclarationWithRefCountFNDX> ObjectDeclarationWithRefCountFNDX_WPtr_t;
typedef std::weak_ptr<ObjectGroupEndFND> ObjectGroupEndFND_WPtr_t;
typedef std::weak_ptr<ObjectGroupListReferenceFND> ObjectGroupListReferenceFND_WPtr_t;
typedef std::weak_ptr<ObjectGroupStartFND> ObjectGroupStartFND_WPtr_t;
typedef std::weak_ptr<ObjectInfoDependencyOverridesFND> ObjectInfoDependencyOverridesFND_WPtr_t;
typedef std::weak_ptr<ObjectRevisionWithRefCount2FNDX> ObjectRevisionWithRefCount2FNDX_WPtr_t;
typedef std::weak_ptr<ObjectRevisionWithRefCountFNDX> ObjectRevisionWithRefCountFNDX_WPtr_t;
typedef std::weak_ptr<ObjectSpaceManifestListReferenceFND> ObjectSpaceManifestListReferenceFND_WPtr_t;
typedef std::weak_ptr<ObjectSpaceManifestListStartFND> ObjectSpaceManifestListStartFND_WPtr_t;
typedef std::weak_ptr<ObjectSpaceManifestRootFND> ObjectSpaceManifestRootFND_WPtr_t;
typedef std::weak_ptr<ReadOnlyObjectDeclaration2LargeRefCountFND> ReadOnlyObjectDeclaration2LargeRefCountFND_WPtr_t;
typedef std::weak_ptr<ReadOnlyObjectDeclaration2RefCountFND> ReadOnlyObjectDeclaration2RefCountFND_WPtr_t;
typedef std::weak_ptr<RevisionManifestEndFND> RevisionManifestEndFND_WPtr_t;
typedef std::weak_ptr<RevisionManifestListReferenceFND> RevisionManifestListReferenceFND_WPtr_t;
typedef std::weak_ptr<RevisionManifestListStartFND> RevisionManifestListStartFND_WPtr_t;
typedef std::weak_ptr<RevisionManifestStart4FND> RevisionManifestStart4FND_WPtr_t;
typedef std::weak_ptr<RevisionManifestStart6FND> RevisionManifestStart6FND_WPtr_t;
typedef std::weak_ptr<RevisionManifestStart7FND> RevisionManifestStart7FND_WPtr_t;
typedef std::weak_ptr<RevisionRoleAndContextDeclarationFND> RevisionRoleAndContextDeclarationFND_WPtr_t;
typedef std::weak_ptr<RevisionRoleDeclarationFND> RevisionRoleDeclarationFND_WPtr_t;
typedef std::weak_ptr<RootObjectReference2FNDX> RootObjectReference2FNDX_WPtr_t;
typedef std::weak_ptr<RootObjectReference3FND> RootObjectReference3FND_WPtr_t;


}
}

#endif // FILENODETYPES_H
