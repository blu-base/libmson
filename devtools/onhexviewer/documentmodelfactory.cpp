#include "documentmodelfactory.h"

#include <QFileInfo>

#include "../../../src/lib/FormatIdentifier.h"
#include "../../../src/lib/priv/PackageStoreFile.h"
#include "../../../src/lib/priv/PackageStoreFileParser.h"
#include "../../../src/lib/priv/RevisionStoreFile.h"
#include "../../../src/lib/priv/RevisionStoreFileParser.h"
//#include "../../../src/lib/priv/chunkables/Chunkable.h"
//#include "../../../src/lib/priv/chunkables/Chunkable.h"
//#include "../../../src/lib/priv/chunkables/RevisionStoreFileHeader.h"

#include "../../../src/lib/priv/commonTypes/ExtendedGUID.h"
#include "../../../src/lib/priv/commonTypes/FileChunkReference32.h"
#include "../../../src/lib/priv/commonTypes/FileChunkReference64.h"
#include "../../../src/lib/priv/commonTypes/FileChunkReference64x32.h"
#include "../../../src/lib/priv/commonTypes/FileNodeChunkReference.h"

#include "../../../src/lib/priv/chunkables/fileNodeTypes/FileNodeTypeIDs.h"


DocumentModelFactory::DocumentModelFactory(const QString& fileName)
    : m_fileName(fileName)
{
}

void DocumentModelFactory::createModel(DocumentModel* tree)
{
  QFileInfo fileInfo(m_fileName);

  if (!fileInfo.exists()) {
    return;
  }

  auto fileFormatIdentifier =
      libmson::FormatIdentifier(m_fileName.toStdString());

  switch (fileFormatIdentifier.getFormat()) {
  case libmson::OnFormat::One03_revStore:
  case libmson::OnFormat::OneToc03_revStore:
  case libmson::OnFormat::OnePkg:
  case libmson::OnFormat::Unrecoqnized:
    break;

  case libmson::OnFormat::One10_revStore:
  case libmson::OnFormat::OneToc10_revStore:
    createRevisionStoreModel(tree, m_fileName);
    break;

  case libmson::OnFormat::One_packStore:
  case libmson::OnFormat::OneToc_packStore:
    //    createPackageStoreModel(tree, m_fileName);
    break;
  }
}

DocumentModel* DocumentModelFactory::createModel(QObject* parent)
{
  auto* model = new DocumentModel(parent);
  createModel(model);

  return model;
}


void DocumentModelFactory::createRevisionStoreModel(
    DocumentModel* tree, const QString& fileName)
{

  auto revisionStoreFile = getRevisionStoreDocument(fileName);

  auto* root = tree->root();


  appendRevisionStoreFileHeader(revisionStoreFile, root);


  for (const auto& chunk : revisionStoreFile->getChunks()) {

    switch (chunk->type()) {

    case libmson::priv::RevisionStoreChunkType::FileNodeListFragment: {
      appendFileNodeListFragment(
          std::dynamic_pointer_cast<libmson::priv::FileNodeListFragment>(chunk),
          revisionStoreFile, root);
      break;
    }
    case libmson::priv::RevisionStoreChunkType::FileNode: {
      appendFileNode(
          std::dynamic_pointer_cast<libmson::priv::FileNode>(chunk),
          revisionStoreFile, root);
      break;
    }
    case libmson::priv::RevisionStoreChunkType::FreeChunkListFragment: {
      appendFreeChunkListFragment(
          std::dynamic_pointer_cast<libmson::priv::FreeChunkListFragment>(
              chunk),
          root);
      break;
    }
    case libmson::priv::RevisionStoreChunkType::FreeChunk: {
      appendFreeChunk(
          std::dynamic_pointer_cast<libmson::priv::FreeChunk>(chunk), root);
      break;
    }
    case libmson::priv::RevisionStoreChunkType::TransactionLogFragment: {
      appendTransactionLogFragment(
          std::dynamic_pointer_cast<libmson::priv::TransactionLogFragment>(
              chunk),
          root);
      break;
    }
    case libmson::priv::RevisionStoreChunkType::FileDataStoreObject: {
      appendFileDataStoreObject(
          std::dynamic_pointer_cast<libmson::priv::FileDataStoreObject>(chunk),
          root);
      break;
    }
    case libmson::priv::RevisionStoreChunkType::ObjectSpaceObjectPropSet: {
      appendObjectSpaceObjectPropSet(
          std::dynamic_pointer_cast<libmson::priv::ObjectSpaceObjectPropSet>(
              chunk),
          root);
      break;
    }
    case libmson::priv::RevisionStoreChunkType::
        ObjectInfoDependencyOverrideData: {
      appendObjectInfoDependencyOverrideData(
          std::dynamic_pointer_cast<
              libmson::priv::ObjectInfoDependencyOverrideData>(chunk),
          root);
      break;
    }
    case libmson::priv::RevisionStoreChunkType::EncryptedData: {
      appendEncryptedData(
          std::dynamic_pointer_cast<libmson::priv::EncryptedData>(chunk), root);
      break;
    }
    case libmson::priv::RevisionStoreChunkType::UnknownBlob: {
      appendUnknownBlob(
          std::dynamic_pointer_cast<libmson::priv::UnknownBlob>(chunk), root);
      break;
    }
    case libmson::priv::RevisionStoreChunkType::RevisionStoreFileHeader:
    case libmson::priv::RevisionStoreChunkType::Invalid: {
      break;
    }
    }
  }
}

void DocumentModelFactory::createPackageStoreModel(
    DocumentModel* tree, const QString& fileName)
{
}

std::shared_ptr<libmson::priv::RevisionStoreFile>
DocumentModelFactory::getRevisionStoreDocument(const QString& fileName)
{
  QFileInfo fileInfo(fileName);

  QString baseFileName =
      fileInfo.fileName().left(fileInfo.fileName().lastIndexOf('.'));

  // parse file
  QFile msonFile(fileName);
  bool couldopen = msonFile.open(QIODevice::ReadOnly);

  if (!couldopen) {
    qFatal("Could not open file.");
  }

  QDataStream input(&msonFile);

  auto fileParser =
      libmson::priv::RevisionStoreFileParser(input, baseFileName + ".one");
  auto revisionStoreFile = fileParser.parse();

  msonFile.close();

  return revisionStoreFile;
}


std::shared_ptr<libmson::packStore::PackageStoreFile>
DocumentModelFactory::getPackageStoreDocument(const QString& fileName)
{
  QFileInfo fileInfo(fileName);

  QString baseFileName =
      fileInfo.fileName().left(fileInfo.fileName().lastIndexOf('.'));

  // parse file
  QFile msonFile(fileName);
  bool couldopen = msonFile.open(QIODevice::ReadOnly);

  if (!couldopen) {
    qFatal("Could not open file.");
  }

  QDataStream input(&msonFile);

  auto fileParser =
      libmson::packStore::PackageStoreFileParser(input, baseFileName + ".one");

  auto packageStoreFile = fileParser.parse();

  msonFile.close();

  return packageStoreFile;
}


DocumentItem* DocumentModelFactory::appendNewChild(
    const QString& name, const QString& type, const QVariant& value,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
  auto* item = new DocumentItem(
      QVector<QVariant>() << name << type << value << QString::number(stp, 16)
                          << QString::number(cb, 16),
      parent);

  parent->appendChild(item);
  return item;
}

void DocumentModelFactory::appendRevisionStoreFileHeader(
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{

  auto header = revStoreFile->getHeader();
  quint64 stp = header->getInitialStp();

  // add Header
  auto* headerItem = appendNewChild(
      QStringLiteral("Header"), QStringLiteral("Chunkable"),
      revStoreFile->getFileName(), stp, header->getInitialCb(), parent);

  appendGuid(
      header->getGuidFileType(), QStringLiteral("GuidFileType"), stp,
      headerItem);

  appendGuid(
      header->getGuidFile(), QStringLiteral("GuidFile"), stp, headerItem);

  appendGuid(
      header->getGuidLegacyFileVersion(),
      QStringLiteral("GuidLegacyFileVersion"), stp, headerItem);

  appendGuid(
      header->getGuidFileFormat(), QStringLiteral("GuidFileFormat"), stp,
      headerItem);

  appendUInt32(
      header->getFfvLastWriterVersion(), QStringLiteral("ffvLastWriterVersion"),
      stp, headerItem);

  appendUInt32(
      header->getFfvOldestWriterVersion(),
      QStringLiteral("ffvOldestWriterVersion"), stp, headerItem);

  appendUInt32(
      header->getFfvNewestWriterVersion(),
      QStringLiteral("ffvNewestWriterVersion"), stp, headerItem);

  appendUInt32(
      header->getFfvOldestReader(), QStringLiteral("ffvOldestReader"), stp,
      headerItem);

  appendFileChunkReference32(
      header->getFcrLegacyFreeChunkList(),
      QStringLiteral("fcrLegacyFreeChunkList"), stp, headerItem);

  appendFileChunkReference32(
      header->getFcrLegacyTransactionLog(),
      QStringLiteral("fcrLegacyTransactionLog"), stp, headerItem);

  appendUInt32(
      header->getCTransactionsInLog(), QStringLiteral("cTransactionsInLog"),
      stp, headerItem);

  appendUInt32(
      header->getCbLegacyExpectedFileLength(),
      QStringLiteral("cbLegacyExpectedFileLength"), stp, headerItem);

  appendUInt64(
      header->getRgbPlaceholder(), QStringLiteral("rgbPlaceholder"), stp,
      headerItem);

  appendFileChunkReference32(
      header->getFcrLegacyFileNodeListRoot(),
      QStringLiteral("fcrLegacyFileNodeListRoot"), stp, headerItem);

  appendUInt32(
      header->getCbLegacyFreeSpaceInFreeChunkList(),
      QStringLiteral("cbLegacyFreeSpaceInFreeChunkList"), stp, headerItem);

  appendUInt8(
      header->getFNeedsDefrag(), QStringLiteral("fNeedsDefrag"), stp,
      headerItem);

  appendUInt8(
      header->getFRepairedFile(), QStringLiteral("fRepairedFile"), stp,
      headerItem);

  appendUInt8(
      header->getFNeedsGarbageCollect(), QStringLiteral("fNeedsGarbageCollect"),
      stp, headerItem);

  appendUInt8(
      header->getFHasNoEmbeddedFileObjects(),
      QStringLiteral("fHasNoEmbeddedFileObjects"), stp, headerItem);

  appendGuid(
      header->getGuidAncestor(), QStringLiteral("guidAncestor"), stp,
      headerItem);

  appendUInt32(
      header->getCrcName(), QStringLiteral("crcName"), stp, headerItem);

  appendFileChunkReference64x32(
      libmson::priv::getFcr64x32FromChunk(
          revStoreFile, header->getFcrHashedChunkList()),
      QStringLiteral("fcrHashedChunkList"), stp, headerItem);

  appendFileChunkReference64x32(
      libmson::priv::getFcr64x32FromChunk(
          revStoreFile, header->getFcrTransactionLog()),
      QStringLiteral("fcrTransactionLog"), stp, headerItem);

  appendFileChunkReference64x32(
      libmson::priv::getFcr64x32FromChunk(
          revStoreFile, header->getFcrFileNodeListRoot()),
      QStringLiteral("m_fcrFileNodeListRoot"), stp, headerItem);

  appendFileChunkReference64x32(
      libmson::priv::getFcr64x32FromChunk(
          revStoreFile, header->getFcrFreeChunkList()),
      QStringLiteral("fcrFreeChunkList"), stp, headerItem);

  appendUInt64(
      header->getCbExpectedFileLength(), QStringLiteral("cbExpectedFileLength"),
      stp, headerItem);

  appendUInt64(
      header->getCbFreeSpaceInFreeChunkList(),
      QStringLiteral("cbFreeSpaceInFreeChunkList"), stp, headerItem);

  appendGuid(
      header->getGuidFileVersion(), QStringLiteral("guidFileVersion"), stp,
      headerItem);

  appendUInt64(
      header->getNFileVersionGeneration(),
      QStringLiteral("nFileVersionGeneration"), stp, headerItem);

  appendGuid(
      header->getGuidDenyReadFileVersion(),
      QStringLiteral("guidDenyReadFileVersion"), stp, headerItem);

  appendUInt32(
      header->getGrfDebugLogFlags(), QStringLiteral("grfDebugLogFlags"), stp,
      headerItem);

  appendFileChunkReference64x32(
      header->getFcrDebugLog(), QStringLiteral("fcrDebugLog"), stp, headerItem);

  appendFileChunkReference64x32(
      header->getFcrAllocVerificationFreeChunkList(),
      QStringLiteral("fcrAllocVerificationFreeChunkList"), stp, headerItem);


  appendUInt32(
      header->getBnCreated(), QStringLiteral("bnCreated"), stp, headerItem);

  appendUInt32(
      header->getBnLastWroteToThisFile(),
      QStringLiteral("bnLastWroteToThisFile"), stp, headerItem);

  appendUInt32(
      header->getBnOldestWritten(), QStringLiteral("bnOldestWritten"), stp,
      headerItem);

  appendUInt32(
      header->getBnNewestWritten(), QStringLiteral("bnNewestWritten"), stp,
      headerItem);

  appendNewChild(
      QStringLiteral("Padding"), QString(), QString(), stp,
      libmson::priv::RevisionStoreFileHeader::def_reservedHeaderTailLength,
      headerItem);
}

void DocumentModelFactory::appendFileNodeListFragment(
    const libmson::priv::FileNodeListFragment_SPtr_t& chunk,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
  auto* chunkItem = appendNewChild(
      QStringLiteral("FileNodeListFragment"), QStringLiteral("Chunkable"),
      QString(), chunk->getInitialStp(), chunk->getInitialCb(), parent);

  quint64 stp = chunk->getInitialStp();


  appendNewChild(
      QStringLiteral("FileNodeListFragmentHeader"), QStringLiteral("uint64_t"),
      QString(), stp, sizeof(quint64), chunkItem);
  stp += sizeof(quint64);


  appendUInt32(
      chunk->getFileNodeListID(), QStringLiteral("fileNodeListID"), stp,
      chunkItem);

  appendUInt32(
      chunk->getNFragmentSequence(), QStringLiteral("nFragmentSequence"), stp,
      chunkItem);


  // compute size of contained FileNodes
  const quint64 sumFnCb = std::accumulate(
      chunk->fileNodes().begin(), chunk->fileNodes().end(), 0,
      [&](quint64 sum, libmson::priv::FileNode_SPtr_t fn) {
        return sum + fn->getSizeInFile();
      });

  const quint64 footerstp =
      chunk->getInitialStp() + chunk->getInitialCb() -
      libmson::priv::FileChunkReference64x32::getSizeInFile() - sizeof(quint64);

  const quint64 paddingStp = stp + sumFnCb;
  const quint64 paddingCb  = footerstp - stp - sumFnCb;


  auto* filenodes = appendNewChild(
      QStringLiteral("FileNodes"), QString(), QString(), stp, sumFnCb,
      chunkItem);

  for (auto&& fn : chunk->fileNodes()) {
    appendFileNode(fn, revStoreFile, filenodes);
  }


  // padding
  appendNewChild(
      QStringLiteral("Padding"), QString(), QString(), paddingStp, paddingCb,
      chunkItem);

  // footer

  quint64 fstp = footerstp;

  appendFileChunkReference64x32(
      libmson::priv::getFcr64x32FromChunk(
          revStoreFile, chunk->getNextFragment()),
      QStringLiteral("nextFragment"), fstp, chunkItem);

  appendNewChild(
      QStringLiteral("FileNodeListFragmentFooter"), QStringLiteral("uint64_t"),
      QString(), fstp, sizeof(quint64), chunkItem);
}

void DocumentModelFactory::appendFileNode(
    const libmson::priv::FileNode_SPtr_t& chunk,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
  auto* chunkItem = appendNewChild(
      QStringLiteral("FileNode"),
      libmson::priv::fileNodeTypeIDString(chunk->getFileNodeTypeID()),
      QString(), chunk->getInitialStp(), chunk->getInitialCb(), parent);

  auto* fileNodeHeaderItem = appendNewChild(
      QStringLiteral("Header"), QString(), QString(), chunk->getInitialStp(), 4,
      chunkItem);

  appendNewChild(
      QStringLiteral("fileNodeId"), QStringLiteral("uint10_t"),
      QString::number(chunk->getFileNodeID(), 16), chunk->getInitialStp(), 4,
      fileNodeHeaderItem);
  appendNewChild(
      QStringLiteral("fileNodeSize"), QStringLiteral("uint13_t"),
      QString::number(chunk->getFileNodeSize(), 16), chunk->getInitialStp(), 4,
      fileNodeHeaderItem);


  appendNewChild(
      QStringLiteral("StpFormat"), QStringLiteral("2 bits"),
      libmson::priv::FileNodeChunkReference::fncrStpFormatString(
          chunk->getStpFormatEnum()),
      chunk->getInitialStp(), 4, fileNodeHeaderItem);

  //  appendNewChild(
  //      QStringLiteral("CbFormat"), QStringLiteral("2 bits"),
  //      libmson::priv::fncrCbFormatString(chunk->getCbFormatEnum()),
  //      chunk->getInitialStp(), 4, chunkItem);

  auto* data = appendNewChild(
      QStringLiteral("Data"),
      libmson::priv::fileNodeTypeIDString(chunk->getFileNodeTypeID()),
      QString(), chunk->getInitialStp() + 4, chunk->getInitialCb() - 4,
      chunkItem);

  // append FileNodeData Items
  appendFileNodeData(chunk, revStoreFile, data);
}

void DocumentModelFactory::appendFreeChunkListFragment(
    const libmson::priv::FreeChunkListFragment_SPtr_t& chunk,
    DocumentItem* parent)
{
  auto* chunkItem = appendNewChild(
      QStringLiteral("FreeChunkListFragment"), QStringLiteral("Chunkable"),
      QString(), chunk->getInitialStp(), chunk->getInitialCb(), parent);
}

void DocumentModelFactory::appendFreeChunk(
    const libmson::priv::FreeChunk_SPtr_t& chunk, DocumentItem* parent)
{
  appendNewChild(
      QStringLiteral("FreeChunk"), QStringLiteral("Chunkable"), QString(),
      chunk->getInitialStp(), chunk->getInitialCb(), parent);
}

void DocumentModelFactory::appendTransactionLogFragment(
    const libmson::priv::TransactionLogFragment_SPtr_t& chunk,
    DocumentItem* parent)
{
  auto* chunkItem = appendNewChild(
      QStringLiteral("TransactionLogFragment"), QStringLiteral("Chunkable"),
      QString(), chunk->getInitialStp(), chunk->getInitialCb(), parent);
}

void DocumentModelFactory::appendFileDataStoreObject(
    const libmson::priv::FileDataStoreObject_SPtr_t& chunk,
    DocumentItem* parent)
{
  auto* chunkItem = appendNewChild(
      QStringLiteral("FileDataStoreObject"), QStringLiteral("Chunkable"),
      QString(), chunk->getInitialStp(), chunk->getInitialCb(), parent);
}

void DocumentModelFactory::appendObjectSpaceObjectPropSet(
    const libmson::priv::ObjectSpaceObjectPropSet_SPtr_t& chunk,
    DocumentItem* parent)
{
  auto* chunkItem = appendNewChild(
      QStringLiteral("ObjectSpaceObjectPropSet"), QStringLiteral("Chunkable"),
      QString(), chunk->getInitialStp(), chunk->getInitialCb(), parent);
}

void DocumentModelFactory::appendObjectInfoDependencyOverrideData(
    const libmson::priv::ObjectInfoDependencyOverrideData_SPtr_t& chunk,
    DocumentItem* parent)
{
  auto* chunkItem = appendNewChild(
      QStringLiteral("ObjectInfoDependencyOverrideData"),
      QStringLiteral("Chunkable"), QString(), chunk->getInitialStp(),
      chunk->getInitialCb(), parent);
}

void DocumentModelFactory::appendEncryptedData(
    const libmson::priv::EncryptedData_SPtr_t& chunk, DocumentItem* parent)
{
  auto* chunkItem = appendNewChild(
      QStringLiteral("EncryptedData"), QStringLiteral("Chunkable"), QString(),
      chunk->getInitialStp(), chunk->getInitialCb(), parent);
}

void DocumentModelFactory::appendUnknownBlob(
    const libmson::priv::UnknownBlob_SPtr_t& chunk, DocumentItem* parent)
{
  appendNewChild(
      QStringLiteral("UnknownBlob"), QStringLiteral("Chunkable"), QString(),
      chunk->getInitialStp(), chunk->getInitialCb(), parent);
}

void DocumentModelFactory::appendFileNodeData(
    const libmson::priv::FileNode_SPtr_t& chunk,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
  switch (chunk->getFileNodeTypeID()) {
    // type 0
  case libmson::priv::FileNodeTypeID::ObjectSpaceManifestRootFND:
    appendObjectSpaceManifestRootFND(
        std::dynamic_pointer_cast<libmson::priv::ObjectSpaceManifestRootFND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;

  case libmson::priv::FileNodeTypeID::ObjectSpaceManifestListStartFND:
    appendObjectSpaceManifestListStartFND(
        std::dynamic_pointer_cast<
            libmson::priv::ObjectSpaceManifestListStartFND>(chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;

  case libmson::priv::FileNodeTypeID::RevisionManifestListStartFND:
    appendRevisionManifestListStartFND(
        std::dynamic_pointer_cast<libmson::priv::RevisionManifestListStartFND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;

  case libmson::priv::FileNodeTypeID::RevisionManifestStart4FND:
    appendRevisionManifestStart4FND(
        std::dynamic_pointer_cast<libmson::priv::RevisionManifestStart4FND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;

  case libmson::priv::FileNodeTypeID::RevisionManifestEndFND:
    appendRevisionManifestEndFND(
        std::dynamic_pointer_cast<libmson::priv::RevisionManifestEndFND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;

  case libmson::priv::FileNodeTypeID::RevisionManifestStart6FND:
    appendRevisionManifestStart6FND(
        std::dynamic_pointer_cast<libmson::priv::RevisionManifestStart6FND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;

  case libmson::priv::FileNodeTypeID::RevisionManifestStart7FND:
    appendRevisionManifestStart7FND(
        std::dynamic_pointer_cast<libmson::priv::RevisionManifestStart7FND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;

  case libmson::priv::FileNodeTypeID::GlobalIdTableStartFNDX:
    appendGlobalIdTableStartFNDX(
        std::dynamic_pointer_cast<libmson::priv::GlobalIdTableStartFNDX>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;

  case libmson::priv::FileNodeTypeID::GlobalIdTableStart2FND:
    appendGlobalIdTableStart2FND(
        std::dynamic_pointer_cast<libmson::priv::GlobalIdTableStart2FND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;

  case libmson::priv::FileNodeTypeID::GlobalIdTableEntryFNDX:
    appendGlobalIdTableEntryFNDX(
        std::dynamic_pointer_cast<libmson::priv::GlobalIdTableEntryFNDX>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;

  case libmson::priv::FileNodeTypeID::GlobalIdTableEntry2FNDX:
    appendGlobalIdTableEntry2FNDX(
        std::dynamic_pointer_cast<libmson::priv::GlobalIdTableEntry2FNDX>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;

  case libmson::priv::FileNodeTypeID::GlobalIdTableEntry3FNDX:
    appendGlobalIdTableEntry3FNDX(
        std::dynamic_pointer_cast<libmson::priv::GlobalIdTableEntry3FNDX>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;

  case libmson::priv::FileNodeTypeID::GlobalIdTableEndFNDX:
    appendGlobalIdTableEndFNDX(
        std::dynamic_pointer_cast<libmson::priv::GlobalIdTableEndFNDX>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;

  case libmson::priv::FileNodeTypeID::RootObjectReference2FNDX:
    appendRootObjectReference2FNDX(
        std::dynamic_pointer_cast<libmson::priv::RootObjectReference2FNDX>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;

  case libmson::priv::FileNodeTypeID::RootObjectReference3FND:
    appendRootObjectReference3FND(
        std::dynamic_pointer_cast<libmson::priv::RootObjectReference3FND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;

  case libmson::priv::FileNodeTypeID::RevisionRoleDeclarationFND:
    appendRevisionRoleDeclarationFND(
        std::dynamic_pointer_cast<libmson::priv::RevisionRoleDeclarationFND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;

  case libmson::priv::FileNodeTypeID::RevisionRoleAndContextDeclarationFND:
    appendRevisionRoleAndContextDeclarationFND(
        std::dynamic_pointer_cast<
            libmson::priv::RevisionRoleAndContextDeclarationFND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;

  case libmson::priv::FileNodeTypeID::ObjectDeclarationFileData3RefCountFND:
    appendObjectDeclarationFileData3RefCountFND(
        std::dynamic_pointer_cast<
            libmson::priv::ObjectDeclarationFileData3RefCountFND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;

  case libmson::priv::FileNodeTypeID::
      ObjectDeclarationFileData3LargeRefCountFND:
    appendObjectDeclarationFileData3LargeRefCountFND(
        std::dynamic_pointer_cast<
            libmson::priv::ObjectDeclarationFileData3LargeRefCountFND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;

  case libmson::priv::FileNodeTypeID::DataSignatureGroupDefinitionFND:
    appendDataSignatureGroupDefinitionFND(
        std::dynamic_pointer_cast<
            libmson::priv::DataSignatureGroupDefinitionFND>(chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;

  case libmson::priv::FileNodeTypeID::ObjectGroupStartFND:
    appendObjectGroupStartFND(
        std::dynamic_pointer_cast<libmson::priv::ObjectGroupStartFND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;

  case libmson::priv::FileNodeTypeID::ObjectGroupEndFND:
    appendObjectGroupEndFND(
        std::dynamic_pointer_cast<libmson::priv::ObjectGroupEndFND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;

  case libmson::priv::FileNodeTypeID::HashedChunkDescriptor2FND:
    appendHashedChunkDescriptor2FND(
        std::dynamic_pointer_cast<libmson::priv::HashedChunkDescriptor2FND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;

  case libmson::priv::FileNodeTypeID::ChunkTerminatorFND:
    appendChunkTerminatorFND(
        std::dynamic_pointer_cast<libmson::priv::ChunkTerminatorFND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, parent);
    break;


    // type 1
  case libmson::priv::FileNodeTypeID::ObjectDeclarationWithRefCountFNDX:
    appendObjectDeclarationWithRefCountFNDX(
        std::dynamic_pointer_cast<
            libmson::priv::ObjectDeclarationWithRefCountFNDX>(chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, revStoreFile,
        parent);
    break;

  case libmson::priv::FileNodeTypeID::ObjectDeclarationWithRefCount2FNDX:
    appendObjectDeclarationWithRefCount2FNDX(
        std::dynamic_pointer_cast<
            libmson::priv::ObjectDeclarationWithRefCount2FNDX>(chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, revStoreFile,
        parent);
    break;

  case libmson::priv::FileNodeTypeID::ObjectRevisionWithRefCountFNDX:
    appendObjectRevisionWithRefCountFNDX(
        std::dynamic_pointer_cast<
            libmson::priv::ObjectRevisionWithRefCountFNDX>(chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, revStoreFile,
        parent);
    break;

  case libmson::priv::FileNodeTypeID::ObjectRevisionWithRefCount2FNDX:
    appendObjectRevisionWithRefCount2FNDX(
        std::dynamic_pointer_cast<
            libmson::priv::ObjectRevisionWithRefCount2FNDX>(chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, revStoreFile,
        parent);
    break;

  case libmson::priv::FileNodeTypeID::ObjectDataEncryptionKeyV2FNDX:
    appendObjectDataEncryptionKeyV2FNDX(
        std::dynamic_pointer_cast<libmson::priv::ObjectDataEncryptionKeyV2FNDX>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, revStoreFile,
        parent);
    break;

  case libmson::priv::FileNodeTypeID::ObjectInfoDependencyOverridesFND:
    appendObjectInfoDependencyOverridesFND(
        std::dynamic_pointer_cast<
            libmson::priv::ObjectInfoDependencyOverridesFND>(chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, revStoreFile,
        parent);
    break;

  case libmson::priv::FileNodeTypeID::FileDataStoreObjectReferenceFND:
    appendFileDataStoreObjectReferenceFND(
        std::dynamic_pointer_cast<
            libmson::priv::FileDataStoreObjectReferenceFND>(chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, revStoreFile,
        parent);
    break;

  case libmson::priv::FileNodeTypeID::ObjectDeclaration2RefCountFND:
    appendObjectDeclaration2RefCountFND(
        std::dynamic_pointer_cast<libmson::priv::ObjectDeclaration2RefCountFND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, revStoreFile,
        parent);
    break;

  case libmson::priv::FileNodeTypeID::ObjectDeclaration2LargeRefCountFND:
    appendObjectDeclaration2LargeRefCountFND(
        std::dynamic_pointer_cast<
            libmson::priv::ObjectDeclaration2LargeRefCountFND>(chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, revStoreFile,
        parent);
    break;

  case libmson::priv::FileNodeTypeID::ReadOnlyObjectDeclaration2RefCountFND:
    appendReadOnlyObjectDeclaration2RefCountFND(
        std::dynamic_pointer_cast<
            libmson::priv::ReadOnlyObjectDeclaration2RefCountFND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, revStoreFile,
        parent);
    break;

  case libmson::priv::FileNodeTypeID::
      ReadOnlyObjectDeclaration2LargeRefCountFND:
    appendReadOnlyObjectDeclaration2LargeRefCountFND(
        std::dynamic_pointer_cast<
            libmson::priv::ReadOnlyObjectDeclaration2LargeRefCountFND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, revStoreFile,
        parent);
    break;


    // type 2
  case libmson::priv::FileNodeTypeID::FileDataStoreListReferenceFND:
    appendFileDataStoreListReferenceFND(
        std::dynamic_pointer_cast<libmson::priv::FileDataStoreListReferenceFND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, revStoreFile,
        parent);
    break;

  case libmson::priv::FileNodeTypeID::ObjectSpaceManifestListReferenceFND:
    appendObjectSpaceManifestListReferenceFND(
        std::dynamic_pointer_cast<
            libmson::priv::ObjectSpaceManifestListReferenceFND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, revStoreFile,
        parent);
    break;

  case libmson::priv::FileNodeTypeID::RevisionManifestListReferenceFND:
    appendRevisionManifestListReferenceFND(
        std::dynamic_pointer_cast<
            libmson::priv::RevisionManifestListReferenceFND>(chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, revStoreFile,
        parent);
    break;

  case libmson::priv::FileNodeTypeID::ObjectGroupListReferenceFND:
    appendObjectGroupListReferenceFND(
        std::dynamic_pointer_cast<libmson::priv::ObjectGroupListReferenceFND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, revStoreFile,
        parent);
    break;
  }
}

void DocumentModelFactory::appendObjectSpaceManifestRootFND(
    const libmson::priv::ObjectSpaceManifestRootFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
  Q_UNUSED(cb);

  quint64 fndstp = stp;

  appendExtendedGuid(
      fnd->getGosidRoot(), QStringLiteral("gosidRoot"), fndstp, parent);
}

void DocumentModelFactory::appendObjectSpaceManifestListStartFND(
    const libmson::priv::ObjectSpaceManifestListStartFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
}

void DocumentModelFactory::appendRevisionManifestListStartFND(
    const libmson::priv::RevisionManifestListStartFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
}

void DocumentModelFactory::appendRevisionManifestStart4FND(
    const libmson::priv::RevisionManifestStart4FND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
}

void DocumentModelFactory::appendRevisionManifestEndFND(
    const libmson::priv::RevisionManifestEndFND_SPtr_t& fnd, const quint64 stp,
    const quint64 cb, DocumentItem* parent)
{
}

void DocumentModelFactory::appendRevisionManifestStart6FND(
    const libmson::priv::RevisionManifestStart6FND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
}

void DocumentModelFactory::appendRevisionManifestStart7FND(
    const libmson::priv::RevisionManifestStart7FND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
}

void DocumentModelFactory::appendGlobalIdTableStartFNDX(
    const libmson::priv::GlobalIdTableStartFNDX_SPtr_t& fnd, const quint64 stp,
    const quint64 cb, DocumentItem* parent)
{
}

void DocumentModelFactory::appendGlobalIdTableStart2FND(
    const libmson::priv::GlobalIdTableStart2FND_SPtr_t& fnd, const quint64 stp,
    const quint64 cb, DocumentItem* parent)
{
}

void DocumentModelFactory::appendGlobalIdTableEntryFNDX(
    const libmson::priv::GlobalIdTableEntryFNDX_SPtr_t& fnd, const quint64 stp,
    const quint64 cb, DocumentItem* parent)
{
}

void DocumentModelFactory::appendGlobalIdTableEntry2FNDX(
    const libmson::priv::GlobalIdTableEntry2FNDX_SPtr_t& fnd, const quint64 stp,
    const quint64 cb, DocumentItem* parent)
{
}

void DocumentModelFactory::appendGlobalIdTableEntry3FNDX(
    const libmson::priv::GlobalIdTableEntry3FNDX_SPtr_t& fnd, const quint64 stp,
    const quint64 cb, DocumentItem* parent)
{
}

void DocumentModelFactory::appendGlobalIdTableEndFNDX(
    const libmson::priv::GlobalIdTableEndFNDX_SPtr_t& fnd, const quint64 stp,
    const quint64 cb, DocumentItem* parent)
{
}

void DocumentModelFactory::appendRootObjectReference2FNDX(
    const libmson::priv::RootObjectReference2FNDX_SPtr_t& fnd,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
}

void DocumentModelFactory::appendRootObjectReference3FND(
    const libmson::priv::RootObjectReference3FND_SPtr_t& fnd, const quint64 stp,
    const quint64 cb, DocumentItem* parent)
{
}

void DocumentModelFactory::appendRevisionRoleDeclarationFND(
    const libmson::priv::RevisionRoleDeclarationFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
}

void DocumentModelFactory::appendRevisionRoleAndContextDeclarationFND(
    const libmson::priv::RevisionRoleAndContextDeclarationFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
}

void DocumentModelFactory::appendObjectDeclarationFileData3RefCountFND(
    const libmson::priv::ObjectDeclarationFileData3RefCountFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
}

void DocumentModelFactory::appendObjectDeclarationFileData3LargeRefCountFND(
    const libmson::priv::ObjectDeclarationFileData3LargeRefCountFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
}

void DocumentModelFactory::appendDataSignatureGroupDefinitionFND(
    const libmson::priv::DataSignatureGroupDefinitionFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
}

void DocumentModelFactory::appendObjectGroupStartFND(
    const libmson::priv::ObjectGroupStartFND_SPtr_t& fnd, const quint64 stp,
    const quint64 cb, DocumentItem* parent)
{
}

void DocumentModelFactory::appendObjectGroupEndFND(
    const libmson::priv::ObjectGroupEndFND_SPtr_t& fnd, const quint64 stp,
    const quint64 cb, DocumentItem* parent)
{
}

void DocumentModelFactory::appendHashedChunkDescriptor2FND(
    const libmson::priv::HashedChunkDescriptor2FND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
}

void DocumentModelFactory::appendChunkTerminatorFND(
    const libmson::priv::ChunkTerminatorFND_SPtr_t& fnd, const quint64 stp,
    const quint64 cb, DocumentItem* parent)
{
}

void DocumentModelFactory::appendObjectDeclarationWithRefCountFNDX(
    const libmson::priv::ObjectDeclarationWithRefCountFNDX_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
}

void DocumentModelFactory::appendObjectDeclarationWithRefCount2FNDX(
    const libmson::priv::ObjectDeclarationWithRefCount2FNDX_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
}

void DocumentModelFactory::appendObjectRevisionWithRefCountFNDX(
    const libmson::priv::ObjectRevisionWithRefCountFNDX_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
}

void DocumentModelFactory::appendObjectRevisionWithRefCount2FNDX(
    const libmson::priv::ObjectRevisionWithRefCount2FNDX_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
}

void DocumentModelFactory::appendObjectDataEncryptionKeyV2FNDX(
    const libmson::priv::ObjectDataEncryptionKeyV2FNDX_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
}

void DocumentModelFactory::appendObjectInfoDependencyOverridesFND(
    const libmson::priv::ObjectInfoDependencyOverridesFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
}

void DocumentModelFactory::appendFileDataStoreObjectReferenceFND(
    const libmson::priv::FileDataStoreObjectReferenceFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
}

void DocumentModelFactory::appendObjectDeclaration2RefCountFND(
    const libmson::priv::ObjectDeclaration2RefCountFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
}

void DocumentModelFactory::appendObjectDeclaration2LargeRefCountFND(
    const libmson::priv::ObjectDeclaration2LargeRefCountFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
}

void DocumentModelFactory::appendReadOnlyObjectDeclaration2RefCountFND(
    const libmson::priv::ReadOnlyObjectDeclaration2RefCountFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
}

void DocumentModelFactory::appendReadOnlyObjectDeclaration2LargeRefCountFND(
    const libmson::priv::ReadOnlyObjectDeclaration2LargeRefCountFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
}

void DocumentModelFactory::appendFileDataStoreListReferenceFND(
    const libmson::priv::FileDataStoreListReferenceFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
}

void DocumentModelFactory::appendObjectSpaceManifestListReferenceFND(
    const libmson::priv::ObjectSpaceManifestListReferenceFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
}

void DocumentModelFactory::appendRevisionManifestListReferenceFND(
    const libmson::priv::RevisionManifestListReferenceFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
}

void DocumentModelFactory::appendObjectGroupListReferenceFND(
    const libmson::priv::ObjectGroupListReferenceFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
}


DocumentItem* DocumentModelFactory::appendUInt8(
    const quint8 val, const QString& name, quint64& stp, DocumentItem* parent)
{
  const quint64 cb = sizeof(quint8);

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("uint8_t"), QString::number(val, 16), stp, cb,
      parent);
  stp += cb;
  return item;
}

DocumentItem* DocumentModelFactory::appendUInt16(
    const quint16 val, const QString& name, quint64& stp, DocumentItem* parent)
{
  const quint64 cb = sizeof(quint16);

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("uint16_t"), QString::number(val, 16), stp, cb,
      parent);
  stp += cb;
  return item;
}

DocumentItem* DocumentModelFactory::appendUInt32(
    const quint32 val, const QString& name, quint64& stp, DocumentItem* parent)
{
  const quint64 cb = sizeof(quint32);

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("uint32_t"), QString::number(val, 16), stp, cb,
      parent);
  stp += cb;
  return item;
}

DocumentItem* DocumentModelFactory::appendUInt64(
    const quint64 val, const QString& name, quint64& stp, DocumentItem* parent)
{
  const quint64 cb = sizeof(quint64);

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("uint64_t"), QString::number(val, 16), stp, cb,
      parent);
  stp += cb;
  return item;
}

DocumentItem* DocumentModelFactory::appendInt8(
    const qint8 val, const QString& name, quint64& stp, DocumentItem* parent)
{
  const quint64 cb = sizeof(qint8);

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("int8_t"), QString::number(val, 16), stp, cb,
      parent);
  stp += cb;
  return item;
}

DocumentItem* DocumentModelFactory::appendInt16(
    const qint16 val, const QString& name, quint64& stp, DocumentItem* parent)
{
  const quint64 cb = sizeof(qint16);

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("int16_t"), QString::number(val, 16), stp, cb,
      parent);
  stp += cb;
  return item;
}

DocumentItem* DocumentModelFactory::appendInt32(
    const qint32 val, const QString& name, quint64& stp, DocumentItem* parent)
{
  const quint64 cb = sizeof(qint32);

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("uint32_t"), QString::number(val, 16), stp, cb,
      parent);
  stp += cb;
  return item;
}

DocumentItem* DocumentModelFactory::appendInt64(
    const qint64 val, const QString& name, quint64& stp, DocumentItem* parent)
{
  const quint64 cb = sizeof(qint64);

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("uint64_t"), QString::number(val, 16), stp, cb,
      parent);
  stp += cb;
  return item;
}

DocumentItem* DocumentModelFactory::appendGuid(
    const QUuid& guid, const QString& name, quint64& stp, DocumentItem* parent)
{
  const quint64 cb = sizeof(QUuid);

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("Guid"), guid.toString(), stp, cb, parent);
  stp += cb;
  return item;
}

DocumentItem* DocumentModelFactory::appendExtendedGuid(
    const libmson::priv::ExtendedGUID& eguid, const QString& name, quint64& stp,
    DocumentItem* parent)
{
  const quint64 cb{libmson::priv::ExtendedGUID::getSizeInFile()};

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("ExtendedGuid"), eguid.toString(), stp, cb, parent);


  appendGuid(eguid.getGuid(), QStringLiteral("Guid"), stp, item);

  appendUInt32(eguid.getN(), QStringLiteral("n"), stp, item);

  return item;
}

DocumentItem* DocumentModelFactory::appendFileChunkReference32(
    const libmson::priv::FileChunkReference32& ref, const QString& name,
    quint64& stp, DocumentItem* parent)
{
  const quint64 cb    = libmson::priv::FileChunkReference32::getSizeInFile();
  const QString value = ref.is_fcrZero()  ? QStringLiteral("fcrZero")
                        : ref.is_fcrNil() ? QStringLiteral("fcrNil")
                                          : QString();


  DocumentItem* item = appendNewChild(
      name, QStringLiteral("FileChunkReference32"), value, stp, cb, parent);


  appendNewChild(
      QStringLiteral("Stp"), QStringLiteral("uint32_t"),
      QString::number(ref.stp(), 16), stp, sizeof(quint32), item);
  appendNewChild(
      QStringLiteral("Cb"), QStringLiteral("uint32_t"),
      QString::number(ref.cb(), 16), stp + sizeof(quint32), sizeof(quint32),
      item);

  stp += cb;
  return item;
}

DocumentItem* DocumentModelFactory::appendFileChunkReference64x32(
    const libmson::priv::FileChunkReference64x32& ref, const QString& name,
    quint64& stp, DocumentItem* parent)
{
  const quint64 cb    = libmson::priv::FileChunkReference64x32::getSizeInFile();
  const QString value = ref.is_fcrZero()  ? QStringLiteral("fcrZero")
                        : ref.is_fcrNil() ? QStringLiteral("fcrNil")
                                          : QString();

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("FileChunkReference64x32"), value, stp, cb, parent);


  appendNewChild(
      QStringLiteral("Stp"), QStringLiteral("uint64_t"),
      QString::number(ref.stp(), 16), stp, sizeof(quint64), item);

  appendNewChild(
      QStringLiteral("Cb"), QStringLiteral("uint32_t"),
      QString::number(ref.cb(), 16), stp + sizeof(quint64), sizeof(quint32),
      item);

  stp += cb;
  return item;
}

DocumentItem* DocumentModelFactory::appendFileChunkReference64(
    const libmson::priv::FileChunkReference64& ref, const QString& name,
    quint64& stp, DocumentItem* parent)
{
  const quint64 cb    = libmson::priv::FileChunkReference64::getSizeInFile();
  const QString value = ref.is_fcrZero()  ? QStringLiteral("fcrZero")
                        : ref.is_fcrNil() ? QStringLiteral("fcrNil")
                                          : QString();

  auto* item = appendNewChild(
      name, QStringLiteral("FileChunkReference64"), value, stp, cb, parent);


  appendNewChild(
      QStringLiteral("Stp"), QStringLiteral("uint64_t"),
      QString::number(ref.stp(), 16), stp, sizeof(quint64), item);
  appendNewChild(
      QStringLiteral("Cb"), QStringLiteral("uint64_t"),
      QString::number(ref.cb(), 16), stp + sizeof(quint64), sizeof(quint64),
      item);

  stp += cb;
  return item;
}

DocumentItem* DocumentModelFactory::appendFileNodeChunkReference(
    const libmson::priv::FileNodeChunkReference& ref, const QString& name,
    quint64& stp, DocumentItem* parent)
{
  const quint64 cb    = ref.getSizeInFile();
  const QString value = ref.is_fcrZero()  ? QStringLiteral("fcrZero")
                        : ref.is_fcrNil() ? QStringLiteral("fcrNil")
                                          : QString();

  auto* item = appendNewChild(
      name, QStringLiteral("FileNodeChunkReference"), value, stp, cb, parent);
  stp += cb;


  appendNewChild(
      QStringLiteral("Stp"), QStringLiteral("uint64_t"),
      QString::number(ref.stp(), 16), stp, sizeof(quint64), item);
  appendNewChild(
      QStringLiteral("Cb"), QStringLiteral("uint64_t"),
      QString::number(ref.cb(), 16), stp + sizeof(quint64), sizeof(quint64),
      item);

  return item;
}
