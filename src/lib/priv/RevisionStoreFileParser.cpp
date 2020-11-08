#include "RevisionStoreFileParser.h"

#include "chunkables/FileNode.h"
#include "chunkables/FileNodeListFragment.h"
#include "chunkables/FreeChunk.h"
#include "chunkables/FreeChunkListFragment.h"
#include "chunkables/RevisionStoreFileHeader.h"

#include "chunkables/fileNodeTypes/ChunkTerminatorFND.h"
#include "chunkables/fileNodeTypes/DataSignatureGroupDefinitionFND.h"
//#include "chunkables/fileNodeTypes/FileDataStoreListReferenceFND.h"
//#include "chunkables/fileNodeTypes/FileDataStoreObjectReferenceFND.h"
#include "chunkables/fileNodeTypes/GlobalIdTableEndFNDX.h"
#include "chunkables/fileNodeTypes/GlobalIdTableEntry2FNDX.h"
#include "chunkables/fileNodeTypes/GlobalIdTableEntry3FNDX.h"
#include "chunkables/fileNodeTypes/GlobalIdTableEntryFNDX.h"
#include "chunkables/fileNodeTypes/GlobalIdTableStart2FND.h"
#include "chunkables/fileNodeTypes/GlobalIdTableStartFNDX.h"
#include "chunkables/fileNodeTypes/HashedChunkDescriptor2FND.h"
#include "chunkables/fileNodeTypes/ObjectDataEncryptionKeyV2FNDX.h"
#include "chunkables/fileNodeTypes/ObjectDeclaration2LargeRefCountFND.h"
#include "chunkables/fileNodeTypes/ObjectDeclaration2RefCountFND.h"
#include "chunkables/fileNodeTypes/ObjectDeclarationFileData3LargeRefCountFND.h"
#include "chunkables/fileNodeTypes/ObjectDeclarationFileData3RefCountFND.h"
#include "chunkables/fileNodeTypes/ObjectDeclarationWithRefCount2FNDX.h"
#include "chunkables/fileNodeTypes/ObjectDeclarationWithRefCountFNDX.h"
#include "chunkables/fileNodeTypes/ObjectGroupEndFND.h"
#include "chunkables/fileNodeTypes/ObjectGroupListReferenceFND.h"
#include "chunkables/fileNodeTypes/ObjectGroupStartFND.h"
#include "chunkables/fileNodeTypes/ObjectInfoDependencyOverridesFND.h"
#include "chunkables/fileNodeTypes/ObjectRevisionWithRefCount2FNDX.h"
#include "chunkables/fileNodeTypes/ObjectRevisionWithRefCountFNDX.h"
#include "chunkables/fileNodeTypes/ObjectSpaceManifestListReferenceFND.h"
#include "chunkables/fileNodeTypes/ObjectSpaceManifestListStartFND.h"
#include "chunkables/fileNodeTypes/ObjectSpaceManifestRootFND.h"
#include "chunkables/fileNodeTypes/ReadOnlyObjectDeclaration2LargeRefCountFND.h"
#include "chunkables/fileNodeTypes/ReadOnlyObjectDeclaration2RefCountFND.h"
#include "chunkables/fileNodeTypes/RevisionManifestEndFND.h"
#include "chunkables/fileNodeTypes/RevisionManifestListReferenceFND.h"
#include "chunkables/fileNodeTypes/RevisionManifestListStartFND.h"
#include "chunkables/fileNodeTypes/RevisionManifestStart4FND.h"
#include "chunkables/fileNodeTypes/RevisionManifestStart6FND.h"
#include "chunkables/fileNodeTypes/RevisionManifestStart7FND.h"
#include "chunkables/fileNodeTypes/RevisionRoleAndContextDeclarationFND.h"
#include "chunkables/fileNodeTypes/RevisionRoleDeclarationFND.h"
#include "chunkables/fileNodeTypes/RootObjectReference2FNDX.h"
#include "chunkables/fileNodeTypes/RootObjectReference3FND.h"

namespace libmson {
namespace priv {

RevisionStoreFileParser::RevisionStoreFileParser(QDataStream& inputStream) : m_ds(inputStream) {}


std::shared_ptr<RevisionStoreFile> RevisionStoreFileParser::parse()
{
  auto revisionStoreFile = std::make_shared<RevisionStoreFile>();

  parseRevisionStoreFileHeader();



  auto header = std::static_pointer_cast<RevisionStoreFileHeader>(m_file->chunks().begin()->get()->getContent());

  // parsing RootFileNodeListFragment
  parseFileNodeListFragment(m_ds, header->fcrFileNodeListRoot.lock());



  return revisionStoreFile;
}

bool RevisionStoreFileParser::parseRevisionStoreFileHeader()
{
  if (m_ds.device()->bytesAvailable() < 0x400) {
    qWarning("File size insufficient to be OneNote file.");
    return false;
  }
  // if byte order is big endian, change to little endian
  if (m_ds.byteOrder() == QDataStream::BigEndian) {
    m_ds.setByteOrder(QDataStream::LittleEndian);
  }

  auto headerChunk = std::make_shared<RevisionStoreChunkContainer>(
      std::make_shared<RevisionStoreFileHeader>(), 0u, RevisionStoreFileHeader::sizeInFile);

  m_file->chunks().push_back(headerChunk);

  auto header = std::static_pointer_cast<RevisionStoreFileHeader>(headerChunk->getContent());

  m_ds >> header->guidFileType;
  m_ds >> header->guidFile;
  m_ds >> header->guidLegacyFileVersion;
  if (header->guidLegacyFileVersion != header->v_guidLegacyFileVersion) {
    qWarning("guidLegacyFileVersion of the RevisionStoreFileHeader is invalid.");
  }
  m_ds >> header->guidFileFormat;
  if (header->guidFileFormat != header->v_guidFileFormat) {
    qWarning("guidFileFormat of the RevisionStoreFileHeader is invalid.");
    return false;
  }
  m_ds >> header->ffvLastWriterVersion;
  m_ds >> header->ffvOldestWriterVersion;
  m_ds >> header->ffvNewestWriterVersion;
  m_ds >> header->ffvOldestReader;

  FileChunkReference32 fcrLegacyFreeChunkList;
  m_ds >> fcrLegacyFreeChunkList;
  if (!fcrLegacyFreeChunkList.is_fcrZero()) {
    qWarning("fcrLegacyFreeChunkList of the RevisionStoreFileHeader is invalid.");
  }

  FileChunkReference32 fcrLegacyTransactionLog;
  m_ds >> fcrLegacyTransactionLog;
  if (!fcrLegacyTransactionLog.is_fcrNil()) {
    qWarning("fcrLegacyTransactionLog of the RevisionStoreFileHeader is invalid.");
  }

  m_ds >> header->cTransactionsInLog;

  quint32 cbLegacyExpectedFileLength;
  m_ds >> cbLegacyExpectedFileLength;
  if (cbLegacyExpectedFileLength != 0u) {
    qWarning("cbLegacyExpectedFileLength of the RevisionStoreFileHeader is "
             "invalid.");
  }

  m_ds >> header->rgbPlaceholder;

  FileChunkReference32 fcrLegacyFileNodeListRoot;
  m_ds >> fcrLegacyFileNodeListRoot;
  if (!fcrLegacyFileNodeListRoot.is_fcrNil()) {
    qWarning("fcrLegacyFileNodeListRoot of the RevisionStoreFileHeader is invalid.");
  }

  quint32 cbLegacyFreeSpaceInFreeChunkList;
  m_ds >> cbLegacyFreeSpaceInFreeChunkList;
  if (cbLegacyFreeSpaceInFreeChunkList != 0u) {
    qWarning("cbLegacyFreeSpaceInFreeChunkList of the RevisionStoreFileHeader "
             "is invalid.");
  }

  m_ds >> header->fNeedsDefrag;
  m_ds >> header->fRepairedFile;
  m_ds >> header->fNeedsGarbageCollect;
  m_ds >> header->fHasNoEmbeddedFileObjects;
  m_ds >> header->guidAncestor;
  m_ds >> header->crcName;

  FileChunkReference64x32 fcrHashedChunkList;
  m_ds >> fcrHashedChunkList;

  if (!fcrHashedChunkList.is_fcrNil() && !fcrHashedChunkList.is_fcrZero()) {

    //    m_chunks.push_back(std::make_shared<RevisionStoreChunk>(
    //        RevisionStoreFileHeader(),
    //        RevisionStoreChunkType::File, 0u))

    //    m_chunks.push_back(headerChunk);
  }

  FileChunkReference64x32 fcrTransactionLog;
  m_ds >> fcrTransactionLog;
  if (!fcrTransactionLog.is_fcrNil() && !fcrTransactionLog.is_fcrZero()) {
  }

  FileChunkReference64x32 fcrFileNodeListRoot;
  m_ds >> fcrFileNodeListRoot;
  if (!fcrFileNodeListRoot.is_fcrNil() && !fcrFileNodeListRoot.is_fcrZero()) {

    auto fileNodeListRootChunk = std::make_shared<RevisionStoreChunkContainer>(
        std::make_shared<FileNodeListFragment>(), fcrFileNodeListRoot.stp(), fcrFileNodeListRoot.cb());

    insertChunkSorted(m_file->chunks(), fileNodeListRootChunk);

    header->fcrFileNodeListRoot = fileNodeListRootChunk;
  }

  FileChunkReference64x32 fcrFreeChunkList;
  m_ds >> fcrFreeChunkList;
  if (!fcrFreeChunkList.is_fcrNil() && !fcrFreeChunkList.is_fcrZero()) {

    auto freeChunkListFragment = std::make_shared<RevisionStoreChunkContainer>(
        std::make_shared<FreeChunkListFragment>(fcrFreeChunkList.cb()), fcrFreeChunkList.stp(), fcrFreeChunkList.cb());

    insertChunkSorted(m_file->chunks(), freeChunkListFragment);

    header->fcrFreeChunkList = freeChunkListFragment;
  }

  m_ds >> header->cbExpectedFileLength;
  m_ds >> header->cbFreeSpaceInFreeChunkList;
  m_ds >> header->guidFileVersion;
  m_ds >> header->nFileVersionGeneration;
  m_ds >> header->guidDenyReadFileVersion;
  m_ds >> header->grfDebugLogFlags;

  FileChunkReference64x32 fcrDebugLog;
  m_ds >> fcrDebugLog;
  if (!fcrDebugLog.is_fcrZero()) {
    qWarning("fcrLegacyFreeChunkList of the RevisionStoreFileHeader is invalid.");
  }

  FileChunkReference64x32 fcrAllocVerificationFreeChunkList;
  m_ds >> fcrAllocVerificationFreeChunkList;
  if (!fcrAllocVerificationFreeChunkList.is_fcrZero()) {
    qWarning("fcrLegacyFreeChunkList of the RevisionStoreFileHeader is invalid.");
  }

  m_ds >> header->bnCreated;
  m_ds >> header->bnLastWroteToThisFile;
  m_ds >> header->bnOldestWritten;
  m_ds >> header->bnNewestWritten;
  m_ds.skipRawData(header->def_reservedHeaderTailLength);

  /// \todo further Validate header
  return true;
}

RSChunkContainer_SPtr_t
RevisionStoreFileParser::parseFileNode(QDataStream& ds, const quint64 stp, RSChunkContainer_WPtr_t parent)
{

  auto fnc =
      std::make_shared<RevisionStoreChunkContainer>(std::make_shared<FileNode>(parent), stp, FileNode::minSizeInFile);

  auto fn = std::static_pointer_cast<FileNode>(fnc->getContent());

  if (ds.device()->bytesAvailable() < 4) {
    qFatal("Reached end of file stream while parsing FileNode");
  }
  quint32 temp;
  ds >> temp;

  fn->reserved     = (temp >> FileNode::shiftReserved) & FileNode::maskReserved;
  fn->baseType     = (temp >> FileNode::shiftBaseType) & FileNode::maskBaseType;
  fn->cbFormat     = (temp >> FileNode::shiftCbFormat) & FileNode::maskCbFormat;
  fn->stpFormat    = (temp >> FileNode::shiftStpFormat) & FileNode::maskStpFormat;
  fn->fileNodeSize = (temp >> FileNode::shiftFileNodeSize) & FileNode::maskFileNodeSize;
  fn->fileNodeID   = (temp >> FileNode::shiftFileNodeID) & FileNode::maskFileNodeID;

  switch (fn->getFileNodeTypeID()) {
  case FileNodeTypeID::ChunkTerminatorFND:
    fn->fnt = std::make_shared<ChunkTerminatorFND>();
    break;
  case FileNodeTypeID::DataSignatureGroupDefinitionFND:
    fn->fnt = std::make_shared<DataSignatureGroupDefinitionFND>();
    break;
    //  case FileNodeTypeID::FileDataStoreListReferenceFND:
    //    fn->fnt =
    //    std::make_shared<FileDataStoreListReferenceFND>(fn->stpFormat,
    //    fn->cbFormat); break;
    //  case FileNodeTypeID::FileDataStoreObjectReferenceFND:
    //    fn->fnt =
    //        std::make_shared<FileDataStoreObjectReferenceFND>(fn->stpFormat,
    //        fn->cbFormat);
    //    break;
  case FileNodeTypeID::GlobalIdTableEndFNDX:
    fn->fnt = std::make_shared<GlobalIdTableEndFNDX>();
    break;
  case FileNodeTypeID::GlobalIdTableEntry2FNDX:
    fn->fnt = std::make_shared<GlobalIdTableEntry2FNDX>();
    break;
  case FileNodeTypeID::GlobalIdTableEntry3FNDX:
    fn->fnt = std::make_shared<GlobalIdTableEntry3FNDX>();
    break;
  case FileNodeTypeID::GlobalIdTableEntryFNDX:
    fn->fnt = std::make_shared<GlobalIdTableEntryFNDX>();
    break;
  case FileNodeTypeID::GlobalIdTableStart2FND:
    fn->fnt = std::make_shared<GlobalIdTableStart2FND>();
    break;
  case FileNodeTypeID::GlobalIdTableStartFNDX:
    fn->fnt = std::make_shared<GlobalIdTableStartFNDX>();
    break;
  case FileNodeTypeID::HashedChunkDescriptor2FND:
    fn->fnt = std::make_shared<HashedChunkDescriptor2FND>(fn->stpFormat, fn->cbFormat);
    break;
  case FileNodeTypeID::ObjectDataEncryptionKeyV2FNDX:
    fn->fnt = std::make_shared<ObjectDataEncryptionKeyV2FNDX>(fn->stpFormat, fn->cbFormat);
    break;
  case FileNodeTypeID::ObjectDeclaration2LargeRefCountFND:
    fn->fnt = std::make_shared<ObjectDeclaration2LargeRefCountFND>(fn->stpFormat, fn->cbFormat);
    break;
  case FileNodeTypeID::ObjectDeclaration2RefCountFND:
    fn->fnt = std::make_shared<ObjectDeclaration2RefCountFND>(fn->stpFormat, fn->cbFormat);
    break;
  case FileNodeTypeID::ObjectDeclarationFileData3LargeRefCountFND:
    fn->fnt = std::make_shared<ObjectDeclarationFileData3LargeRefCountFND>();
    break;
  case FileNodeTypeID::ObjectDeclarationFileData3RefCountFND:
    fn->fnt = std::make_shared<ObjectDeclarationFileData3RefCountFND>();
    break;
  case FileNodeTypeID::ObjectDeclarationWithRefCount2FNDX:
    fn->fnt = std::make_shared<ObjectDeclarationWithRefCount2FNDX>(fn->stpFormat, fn->cbFormat);
    break;
  case FileNodeTypeID::ObjectDeclarationWithRefCountFNDX:
    fn->fnt = std::make_shared<ObjectDeclarationWithRefCountFNDX>(fn->stpFormat, fn->cbFormat);
    break;
  case FileNodeTypeID::ObjectGroupEndFND:
    fn->fnt = std::make_shared<ObjectGroupEndFND>();
    break;
  case FileNodeTypeID::ObjectGroupListReferenceFND:
    fn->fnt = std::make_shared<ObjectGroupListReferenceFND>(fn->stpFormat, fn->cbFormat);
    break;
  case FileNodeTypeID::ObjectGroupStartFND:
    fn->fnt = std::make_shared<ObjectGroupStartFND>();
    break;
  case FileNodeTypeID::ObjectInfoDependencyOverridesFND:
    fn->fnt = std::make_shared<ObjectInfoDependencyOverridesFND>(fn->stpFormat, fn->cbFormat);
    break;
  case FileNodeTypeID::ObjectRevisionWithRefCount2FNDX:
    fn->fnt = std::make_shared<ObjectRevisionWithRefCount2FNDX>(fn->stpFormat, fn->cbFormat);
    break;
  case FileNodeTypeID::ObjectRevisionWithRefCountFNDX:
    fn->fnt = std::make_shared<ObjectRevisionWithRefCountFNDX>(fn->stpFormat, fn->cbFormat);
    break;
  case FileNodeTypeID::ObjectSpaceManifestListReferenceFND:
    fn->fnt = std::make_shared<ObjectSpaceManifestListReferenceFND>(fn->stpFormat, fn->cbFormat);
    break;
  case FileNodeTypeID::ObjectSpaceManifestListStartFND:
    fn->fnt = std::make_shared<ObjectSpaceManifestListStartFND>();
    break;
  case FileNodeTypeID::ObjectSpaceManifestRootFND:
    fn->fnt = std::make_shared<ObjectSpaceManifestRootFND>();
    break;
  case FileNodeTypeID::ReadOnlyObjectDeclaration2LargeRefCountFND:
    fn->fnt = std::make_shared<ReadOnlyObjectDeclaration2LargeRefCountFND>(fn->stpFormat, fn->cbFormat);
    break;
  case FileNodeTypeID::ReadOnlyObjectDeclaration2RefCountFND:
    fn->fnt = std::make_shared<ReadOnlyObjectDeclaration2RefCountFND>(fn->stpFormat, fn->cbFormat);
    break;
  case FileNodeTypeID::RevisionManifestEndFND:
    fn->fnt = std::make_shared<RevisionManifestEndFND>();
    break;
  case FileNodeTypeID::RevisionManifestListReferenceFND:
    fn->fnt = std::make_shared<RevisionManifestListReferenceFND>(fn->stpFormat, fn->cbFormat);
    break;
  case FileNodeTypeID::RevisionManifestListStartFND:
    fn->fnt = std::make_shared<RevisionManifestListStartFND>();
    break;
  case FileNodeTypeID::RevisionManifestStart4FND:
    fn->fnt = std::make_shared<RevisionManifestStart4FND>();
    break;
  case FileNodeTypeID::RevisionManifestStart6FND:
    fn->fnt = std::make_shared<RevisionManifestStart6FND>();
    break;
  case FileNodeTypeID::RevisionManifestStart7FND:
    fn->fnt = std::make_shared<RevisionManifestStart7FND>();
    break;
  case FileNodeTypeID::RevisionRoleAndContextDeclarationFND:
    fn->fnt = std::make_shared<RevisionRoleAndContextDeclarationFND>();
    break;
  case FileNodeTypeID::RevisionRoleDeclarationFND:
    fn->fnt = std::make_shared<RevisionRoleDeclarationFND>();
    break;
  case FileNodeTypeID::RootObjectReference2FNDX:
    fn->fnt = std::make_shared<RootObjectReference2FNDX>();
    break;
  case FileNodeTypeID::RootObjectReference3FND:
    fn->fnt = std::make_shared<RootObjectReference3FND>();
    break;

  default:
    fn->fnt = nullptr;
    break;
  }

  if (fn->fnt != nullptr) {
    ds >> *fn->fnt;
  }

  return fnc;
}

void RevisionStoreFileParser::insertChunkSorted(
    std::list<RSChunkContainer_SPtr_t>& chunkList, RSChunkContainer_SPtr_t& chunk)
{
  if (chunk->getType() == RevisionStoreChunkType::RevistionStoreFileHeader) {
    qWarning("Did not add second RevistionStoreFileHeader to chunk list.");
    return;
  }

  if (chunkList.size() < 2) {
    chunkList.push_back(chunk);
    return;
  }

  const quint64 chunkInitialStp = chunk->getInitialStp();

  for (auto it = chunkList.rbegin(); it != chunkList.rend(); ++it) {
    if (it->get()->getInitialStp() < chunkInitialStp) {
      --it;
      chunkList.insert(it.base(), chunk);
      return;
    }
  }
}


} // namespace priv
} // namespace libmson
