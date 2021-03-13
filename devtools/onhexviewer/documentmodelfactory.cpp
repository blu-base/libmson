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

#include <priv/packageTypes/DataElement.h>
#include <priv/packageTypes/DataElementPackage.h>
#include <priv/packageTypes/StreamObjectHeader.h>
#include <priv/packageTypes/dataTypes/CellIdArray.h>
#include <priv/packageTypes/dataTypes/CompactExtGuid.h>
#include <priv/packageTypes/dataTypes/CompactExtGuidArray.h>
#include <priv/packageTypes/dataTypes/CompactUInt64.h>


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
    createPackageStoreModel(tree, m_fileName);
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
          revisionStoreFile, root);
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
          revisionStoreFile, root);
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
    case libmson::priv::RevisionStoreChunkType::OrphanedAllocation: {
      appendOrphanedAllocation(
          std::dynamic_pointer_cast<libmson::priv::OrphanedAllocation>(chunk),
          root);
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

  auto packageStoreFile = getPackageStoreDocument(fileName);

  auto* root = tree->root();


  quint64 stp = appendPackagingStructureHeader(packageStoreFile, root);

  //  appendPackagingStart(packageStoreFile->getPackagingStart().lock(), stp,
  //  root);

  auto packagingStart = packageStoreFile->getPackagingStart().lock();

  if (packagingStart != nullptr) {
    appendStreamObject(packagingStart, stp, root);
  }
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
      QStringLiteral("RevisionStoreFile"), stp, header->getInitialCb(), parent);

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
      QStringLiteral("fcrFileNodeListRoot"), stp, headerItem);

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
      QString::number(chunk->fileNodes().size()) + " FileNodes",
      chunk->getInitialStp(), chunk->getInitialCb(), parent);

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
      chunkItem, false);


  // compute size of contained FileNodes
  const quint64 sumFnCb = std::accumulate(
      chunk->fileNodes().begin(), chunk->fileNodes().end(), 0,
      [&](quint64 sum, const libmson::priv::FileNode_SPtr_t& fn) {
        return sum + fn->getSizeInFile();
      });

  const quint64 footerstp =
      chunk->getInitialStp() + chunk->getInitialCb() -
      libmson::priv::FileChunkReference64x32::getSizeInFile() - sizeof(quint64);

  const quint64 paddingStp = stp + sumFnCb;
  const quint64 paddingCb  = footerstp - stp - sumFnCb;


  auto* filenodes = appendNewChild(
      QStringLiteral("FileNodes"), QString(),
      QString::number(chunk->fileNodes().size()), stp, sumFnCb, chunkItem);

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
      QString("0x" + QString::number(chunk->getFileNodeID(), 16)),
      chunk->getInitialStp(), 4, fileNodeHeaderItem);
  appendNewChild(
      QStringLiteral("fileNodeSize"), QStringLiteral("uint13_t"),
      QString("0x" + QString::number(chunk->getFileNodeSize(), 16)),
      chunk->getInitialStp(), 4, fileNodeHeaderItem);


  appendNewChild(
      QStringLiteral("StpFormat"), QStringLiteral("2 bits"),
      libmson::priv::FileNodeChunkReference::fncrStpFormatString(
          chunk->getStpFormatEnum()),
      chunk->getInitialStp(), 4, fileNodeHeaderItem);

  appendNewChild(
      QStringLiteral("CbFormat"), QStringLiteral("2 bits"),
      libmson::priv::FileNodeChunkReference::fncrCbFormatString(
          chunk->getCbFormatEnum()),
      chunk->getInitialStp(), 4, fileNodeHeaderItem);


  if (chunk->getFileNodeSize() != 4) {
    auto* data = appendNewChild(
        QStringLiteral("Data"),
        libmson::priv::fileNodeTypeIDString(chunk->getFileNodeTypeID()),
        QString(), chunk->getInitialStp() + 4, chunk->getInitialCb() - 4,
        chunkItem);

    // append FileNodeData Items
    appendFileNodeData(chunk, revStoreFile, data);
  }
}

void DocumentModelFactory::appendFreeChunkListFragment(
    const libmson::priv::FreeChunkListFragment_SPtr_t& chunk,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
  auto* chunkItem = appendNewChild(
      QStringLiteral("FreeChunkListFragment"), QStringLiteral("Chunkable"),
      QString(), chunk->getInitialStp(), chunk->getInitialCb(), parent);

  quint64 stp = chunk->getInitialStp();

  appendUInt32(chunk->getCrc(), QStringLiteral("crc"), stp, chunkItem);

  appendFileChunkReference64x32(
      libmson::priv::getFcr64x32FromChunk(revStoreFile, chunk),
      QStringLiteral("fcrNextFragment"), stp, chunkItem);


  const quint64 remainingCb =
      chunk->fcrFreeChunks().size() *
      libmson::priv::FileChunkReference64::getSizeInFile();

  auto* chunks = appendNewChild(
      QStringLiteral("Chunks"), QString(),
      QString::number(chunk->getFcrFreeChunks().size()), stp, remainingCb,
      chunkItem);

  for (auto&& fch : chunk->fcrFreeChunks()) {
    appendFileChunkReference64(
        libmson::priv::getFcr64FromChunk(revStoreFile, fch),
        QStringLiteral("FreeChunk"), stp, chunks);
  }
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
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
  auto* chunkItem = appendNewChild(
      QStringLiteral("TransactionLogFragment"), QStringLiteral("Chunkable"),
      QString(), chunk->getInitialStp(), chunk->getInitialCb(), parent);

  auto* sizeTableItem = appendNewChild(
      QStringLiteral("SizeTable"), QString(), QString(), chunk->getInitialStp(),
      chunk->getSizeTable().size() * 8, chunkItem);

  quint64 ststp = chunk->getInitialStp();

  for (auto&& entry : chunk->getSizeTable()) {
    appendTransactionEntry(
        *entry, QStringLiteral("TransactionEntry"), ststp, sizeTableItem);
  }


  appendFileChunkReference64x32(
      libmson::priv::getFcr64x32FromChunk(
          revStoreFile, chunk->getNextFragment(),
          libmson::priv::FCR_INIT::ZERO),
      QStringLiteral("nextFragment"), ststp, chunkItem);

  appendNewChild(
      QStringLiteral("padding"), QStringLiteral("unspecified"), QString(),
      ststp, 4, chunkItem);
}


void DocumentModelFactory::appendFileDataStoreObject(
    const libmson::priv::FileDataStoreObject_SPtr_t& chunk,
    DocumentItem* parent)
{
  auto* chunkItem = appendNewChild(
      QStringLiteral("FileDataStoreObject"), QStringLiteral("Chunkable"),
      QString(), chunk->getInitialStp(), chunk->getInitialCb(), parent);

  quint64 stp = chunk->getInitialStp();

  appendGuid(
      libmson::priv::FileDataStoreObject::guidHeader,
      QStringLiteral("GuidHeader"), stp, chunkItem);

  appendUInt64(
      chunk->getCbLength(), QStringLiteral("cbLength"), stp, chunkItem);
  appendNewChild(
      QStringLiteral("unused"), QStringLiteral("uint32_t"), QString(), stp,
      sizeof(quint32), chunkItem);
  stp += sizeof(quint32);
  appendNewChild(
      QStringLiteral("reserved"), QStringLiteral("uint64_t"), QString(), stp,
      sizeof(quint64), chunkItem);
  stp += sizeof(quint64);

  appendNewChild(
      QStringLiteral("FileData"), QString(), QString(), stp,
      chunk->getInitialStp() - stp + chunk->getInitialCb() - sizeof(QUuid),
      chunkItem);

  quint64 footerStp =
      chunk->getInitialStp() + chunk->getInitialCb() - sizeof(QUuid);
  appendGuid(
      libmson::priv::FileDataStoreObject::guidFooter,
      QStringLiteral("GuidFooter"), footerStp, chunkItem);
}

void DocumentModelFactory::appendObjectSpaceObjectPropSet(
    const libmson::priv::ObjectSpaceObjectPropSet_SPtr_t& chunk,
    DocumentItem* parent)
{
  auto* chunkItem = appendNewChild(
      QStringLiteral("ObjectSpaceObjectPropSet"), QStringLiteral("Chunkable"),
      QString(), chunk->getInitialStp(), chunk->getInitialCb(), parent);

  quint64 stp = chunk->getInitialStp();

  appendObjectSpaceObjectStreamOfOIDs(
      chunk->OIDs(), QStringLiteral("OIDs"), stp, chunkItem);

  if (chunk->OIDs().getHeader().isOsidStreamNotPresent() == false) {
    appendObjectSpaceObjectStreamOfOSIDs(
        chunk->OSIDs(), QStringLiteral("OSIDs"), stp, chunkItem);

    if (chunk->getOSIDs().getHeader().isExtendedStreamPresent() == true) {
      appendObjectSpaceObjectStreamOfContextIDs(
          chunk->contextIDs(), QStringLiteral("ContextIDs"), stp, chunkItem);
    }
  }
  appendPropertySet(chunk->getBody(), QStringLiteral("Body"), stp, chunkItem);


  appendNewChild(
      QStringLiteral("Padding"), QString(), QString(), stp,
      chunk->getInitialStp() + chunk->getInitialCb() - stp, chunkItem);
}

void DocumentModelFactory::appendObjectInfoDependencyOverrideData(
    const libmson::priv::ObjectInfoDependencyOverrideData_SPtr_t& chunk,
    DocumentItem* parent)
{

  quint64 cstp = chunk->getInitialStp();
  appendObjectInfoDependencyOverrideData(
      *chunk.get(), QStringLiteral("ObjectInfoDependencyOverrideData"), cstp,
      parent);
}

void DocumentModelFactory::appendEncryptedData(
    const libmson::priv::EncryptedData_SPtr_t& chunk, DocumentItem* parent)
{
  auto* chunkItem = appendNewChild(
      QStringLiteral("EncryptedData"), QStringLiteral("Chunkable"), QString(),
      chunk->getInitialStp(), chunk->getInitialCb(), parent);

  quint64 stp = chunk->getInitialStp();

  appendUInt64(
      libmson::priv::EncryptedData::header, QStringLiteral("Header"), stp,
      chunkItem);

  quint64 edcb = chunk->getInitialCb() -
                 sizeof(libmson::priv::EncryptedData::header) -
                 sizeof(libmson::priv::EncryptedData::footer);

  appendNewChild(
      QStringLiteral("Encrypted Data"), QString(), QString(), stp, edcb,
      chunkItem);

  appendUInt64(
      libmson::priv::EncryptedData::footer, QStringLiteral("Footer"), stp,
      chunkItem);
}

void DocumentModelFactory::appendOrphanedAllocation(
    const libmson::priv::OrphanedAllocation_SPtr_t& chunk, DocumentItem* parent)
{
  appendNewChild(
      QStringLiteral("OrphanedAllocation"), QStringLiteral("Chunkable"),
      QString(), chunk->getInitialStp(), chunk->getInitialCb(), parent);
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
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, chunk,
        revStoreFile, parent);
    break;

  case libmson::priv::FileNodeTypeID::ObjectDeclarationWithRefCount2FNDX:
    appendObjectDeclarationWithRefCount2FNDX(
        std::dynamic_pointer_cast<
            libmson::priv::ObjectDeclarationWithRefCount2FNDX>(chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, chunk,
        revStoreFile, parent);
    break;

  case libmson::priv::FileNodeTypeID::ObjectRevisionWithRefCountFNDX:
    appendObjectRevisionWithRefCountFNDX(
        std::dynamic_pointer_cast<
            libmson::priv::ObjectRevisionWithRefCountFNDX>(chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, chunk,
        revStoreFile, parent);
    break;

  case libmson::priv::FileNodeTypeID::ObjectRevisionWithRefCount2FNDX:
    appendObjectRevisionWithRefCount2FNDX(
        std::dynamic_pointer_cast<
            libmson::priv::ObjectRevisionWithRefCount2FNDX>(chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, chunk,
        revStoreFile, parent);
    break;

  case libmson::priv::FileNodeTypeID::ObjectDataEncryptionKeyV2FNDX:
    appendObjectDataEncryptionKeyV2FNDX(
        std::dynamic_pointer_cast<libmson::priv::ObjectDataEncryptionKeyV2FNDX>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, chunk,
        revStoreFile, parent);
    break;

  case libmson::priv::FileNodeTypeID::ObjectInfoDependencyOverridesFND:
    appendObjectInfoDependencyOverridesFND(
        std::dynamic_pointer_cast<
            libmson::priv::ObjectInfoDependencyOverridesFND>(chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, chunk,
        revStoreFile, parent);
    break;

  case libmson::priv::FileNodeTypeID::FileDataStoreObjectReferenceFND:
    appendFileDataStoreObjectReferenceFND(
        std::dynamic_pointer_cast<
            libmson::priv::FileDataStoreObjectReferenceFND>(chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, chunk,
        revStoreFile, parent);
    break;

  case libmson::priv::FileNodeTypeID::ObjectDeclaration2RefCountFND:
    appendObjectDeclaration2RefCountFND(
        std::dynamic_pointer_cast<libmson::priv::ObjectDeclaration2RefCountFND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, chunk,
        revStoreFile, parent);
    break;

  case libmson::priv::FileNodeTypeID::ObjectDeclaration2LargeRefCountFND:
    appendObjectDeclaration2LargeRefCountFND(
        std::dynamic_pointer_cast<
            libmson::priv::ObjectDeclaration2LargeRefCountFND>(chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, chunk,
        revStoreFile, parent);
    break;

  case libmson::priv::FileNodeTypeID::HashedChunkDescriptor2FND:
    appendHashedChunkDescriptor2FND(
        std::dynamic_pointer_cast<libmson::priv::HashedChunkDescriptor2FND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, chunk,
        revStoreFile, parent);
    break;

  case libmson::priv::FileNodeTypeID::ReadOnlyObjectDeclaration2RefCountFND:
    appendReadOnlyObjectDeclaration2RefCountFND(
        std::dynamic_pointer_cast<
            libmson::priv::ReadOnlyObjectDeclaration2RefCountFND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, chunk,
        revStoreFile, parent);
    break;

  case libmson::priv::FileNodeTypeID::
      ReadOnlyObjectDeclaration2LargeRefCountFND:
    appendReadOnlyObjectDeclaration2LargeRefCountFND(
        std::dynamic_pointer_cast<
            libmson::priv::ReadOnlyObjectDeclaration2LargeRefCountFND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, chunk,
        revStoreFile, parent);
    break;


    // type 2
  case libmson::priv::FileNodeTypeID::FileDataStoreListReferenceFND:
    appendFileDataStoreListReferenceFND(
        std::dynamic_pointer_cast<libmson::priv::FileDataStoreListReferenceFND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, chunk,
        revStoreFile, parent);
    break;

  case libmson::priv::FileNodeTypeID::ObjectSpaceManifestListReferenceFND:
    appendObjectSpaceManifestListReferenceFND(
        std::dynamic_pointer_cast<
            libmson::priv::ObjectSpaceManifestListReferenceFND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, chunk,
        revStoreFile, parent);
    break;

  case libmson::priv::FileNodeTypeID::RevisionManifestListReferenceFND:
    appendRevisionManifestListReferenceFND(
        std::dynamic_pointer_cast<
            libmson::priv::RevisionManifestListReferenceFND>(chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, chunk,
        revStoreFile, parent);
    break;

  case libmson::priv::FileNodeTypeID::ObjectGroupListReferenceFND:
    appendObjectGroupListReferenceFND(
        std::dynamic_pointer_cast<libmson::priv::ObjectGroupListReferenceFND>(
            chunk->getFnt()),
        chunk->getInitialStp() + 4, chunk->getInitialCb() - 4, chunk,
        revStoreFile, parent);
    break;

  default:
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
  Q_UNUSED(cb);

  quint64 fndstp = stp;

  appendExtendedGuid(fnd->getGosid(), QStringLiteral("gosid"), fndstp, parent);
}

void DocumentModelFactory::appendRevisionManifestListStartFND(
    const libmson::priv::RevisionManifestListStartFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendExtendedGuid(fnd->getGosid(), QStringLiteral("gosid"), fndstp, parent);

  appendUInt32(
      fnd->getNInstance(), QStringLiteral("nInstance"), fndstp, parent);
}

void DocumentModelFactory::appendRevisionManifestStart4FND(
    const libmson::priv::RevisionManifestStart4FND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendExtendedGuid(fnd->getRid(), QStringLiteral("rid"), fndstp, parent);
  appendExtendedGuid(
      fnd->getRidDependent(), QStringLiteral("ridDependent"), fndstp, parent);

  appendUInt64(
      fnd->getTimeCreation(), QStringLiteral("timeCreation"), fndstp, parent);
  appendUInt32(
      fnd->getRevisionRole(), QStringLiteral("revisionRole"), fndstp, parent);
  appendUInt16(
      fnd->getOdcsDefault(), QStringLiteral("odcsDefault"), fndstp, parent);
}

void DocumentModelFactory::appendRevisionManifestEndFND(
    const libmson::priv::RevisionManifestEndFND_SPtr_t& fnd, const quint64 stp,
    const quint64 cb, DocumentItem* parent)
{
  // no content
  Q_UNUSED(fnd);
  Q_UNUSED(stp);
  Q_UNUSED(cb);
  Q_UNUSED(parent);
}

void DocumentModelFactory::appendRevisionManifestStart6FND(
    const libmson::priv::RevisionManifestStart6FND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendExtendedGuid(fnd->getRid(), QStringLiteral("rid"), fndstp, parent);
  appendExtendedGuid(
      fnd->getRidDependent(), QStringLiteral("ridDependent"), fndstp, parent);

  appendUInt32(
      fnd->getRevisionRole(), QStringLiteral("revisionRole"), fndstp, parent);
  appendUInt16(
      fnd->getOdcsDefault(), QStringLiteral("odcsDefault"), fndstp, parent);
}

void DocumentModelFactory::appendRevisionManifestStart7FND(
    const libmson::priv::RevisionManifestStart7FND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  auto* baseItem = appendNewChild(
      QStringLiteral("Base"), QStringLiteral("RevisionManifestStart6FND"),
      QString(), fndstp, fnd->getBase().getSizeInFile(), parent);

  appendRevisionManifestStart6FND(
      std::make_shared<libmson::priv::RevisionManifestStart6FND>(
          fnd->getBase()),
      fndstp, fnd->getBase().getSizeInFile(), baseItem);


  appendExtendedGuid(fnd->getRid(), QStringLiteral("rid"), fndstp, parent);
}

void DocumentModelFactory::appendGlobalIdTableStartFNDX(
    const libmson::priv::GlobalIdTableStartFNDX_SPtr_t& fnd, const quint64 stp,
    const quint64 cb, DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendUInt8(fnd->getReserved(), QStringLiteral("reserved"), fndstp, parent);
}

void DocumentModelFactory::appendGlobalIdTableStart2FND(
    const libmson::priv::GlobalIdTableStart2FND_SPtr_t& fnd, const quint64 stp,
    const quint64 cb, DocumentItem* parent)
{
  // no content
  Q_UNUSED(fnd);
  Q_UNUSED(stp);
  Q_UNUSED(cb);
  Q_UNUSED(parent);
}

void DocumentModelFactory::appendGlobalIdTableEntryFNDX(
    const libmson::priv::GlobalIdTableEntryFNDX_SPtr_t& fnd, const quint64 stp,
    const quint64 cb, DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendUInt32(fnd->getIndex(), QStringLiteral("Index"), fndstp, parent);

  appendGuid(fnd->getGuid(), QStringLiteral("Guid"), fndstp, parent);
}

void DocumentModelFactory::appendGlobalIdTableEntry2FNDX(
    const libmson::priv::GlobalIdTableEntry2FNDX_SPtr_t& fnd, const quint64 stp,
    const quint64 cb, DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendUInt32(
      fnd->getIIndexMapTo(), QStringLiteral("iIndexMapFrom"), fndstp, parent);

  appendUInt32(
      fnd->getIIndexMapFrom(), QStringLiteral("iIndexMapTo"), fndstp, parent);
}

void DocumentModelFactory::appendGlobalIdTableEntry3FNDX(
    const libmson::priv::GlobalIdTableEntry3FNDX_SPtr_t& fnd, const quint64 stp,
    const quint64 cb, DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendUInt32(
      fnd->getIIndexCopyFromStart(), QStringLiteral("iIndexCopyFromStart"),
      fndstp, parent);

  appendUInt32(
      fnd->getCEntriesToCopy(), QStringLiteral("cEntriesToCopy"), fndstp,
      parent, false);

  appendUInt32(
      fnd->getIIndexCopyToStart(), QStringLiteral("iIndexCopyToStart"), fndstp,
      parent);
}

void DocumentModelFactory::appendGlobalIdTableEndFNDX(
    const libmson::priv::GlobalIdTableEndFNDX_SPtr_t& fnd, const quint64 stp,
    const quint64 cb, DocumentItem* parent)
{
  // no content
  Q_UNUSED(fnd);
  Q_UNUSED(stp);
  Q_UNUSED(cb);
  Q_UNUSED(parent);
}

void DocumentModelFactory::appendRootObjectReference2FNDX(
    const libmson::priv::RootObjectReference2FNDX_SPtr_t& fnd,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendCompactID(fnd->getOidRoot(), QStringLiteral("OidRoot"), fndstp, parent);

  appendUInt32(fnd->getRootRole(), QStringLiteral("RootRole"), fndstp, parent);
}

void DocumentModelFactory::appendRootObjectReference3FND(
    const libmson::priv::RootObjectReference3FND_SPtr_t& fnd, const quint64 stp,
    const quint64 cb, DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendExtendedGuid(
      fnd->getOidRoot(), QStringLiteral("OidRoot"), fndstp, parent);

  appendUInt32(fnd->getRootRole(), QStringLiteral("RootRole"), fndstp, parent);
}

void DocumentModelFactory::appendRevisionRoleDeclarationFND(
    const libmson::priv::RevisionRoleDeclarationFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendExtendedGuid(fnd->getRid(), QStringLiteral("rid"), fndstp, parent);

  appendUInt32(
      fnd->getRevisionRole(), QStringLiteral("RevisionRole"), fndstp, parent);
}

void DocumentModelFactory::appendRevisionRoleAndContextDeclarationFND(
    const libmson::priv::RevisionRoleAndContextDeclarationFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  auto* baseItem = appendNewChild(
      QStringLiteral("Base"), QStringLiteral("RevisionRoleDeclarationFND"),
      QString(), fndstp, fnd->getBase().getSizeInFile(), parent);

  appendRevisionRoleDeclarationFND(
      std::make_shared<libmson::priv::RevisionRoleDeclarationFND>(
          fnd->getBase()),
      fndstp, fnd->getBase().getSizeInFile(), baseItem);

  fndstp += stp + fnd->getBase().getSizeInFile();

  appendExtendedGuid(
      fnd->getGctxid(), QStringLiteral("gctxid"), fndstp, parent);
}

void DocumentModelFactory::appendObjectDeclarationFileData3RefCountFND(
    const libmson::priv::ObjectDeclarationFileData3RefCountFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendCompactID(fnd->getOid(), QStringLiteral("oid"), fndstp, parent);

  appendJCID(fnd->getJcid(), QStringLiteral("jcid"), fndstp, parent);

  appendUInt8(fnd->getCRef(), QStringLiteral("cRef"), fndstp, parent);

  appendStringInStorageBuffer(
      fnd->getFileDataReference(), QStringLiteral("FileDataReference"), fndstp,
      parent);
  appendStringInStorageBuffer(
      fnd->getExtension(), QStringLiteral("Extension"), fndstp, parent);
}

void DocumentModelFactory::appendObjectDeclarationFileData3LargeRefCountFND(
    const libmson::priv::ObjectDeclarationFileData3LargeRefCountFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendCompactID(fnd->getOid(), QStringLiteral("oid"), fndstp, parent);

  appendJCID(fnd->getJcid(), QStringLiteral("jcid"), fndstp, parent);

  appendUInt32(fnd->getCRef(), QStringLiteral("cRef"), fndstp, parent, false);

  appendStringInStorageBuffer(
      fnd->getFileDataReference(), QStringLiteral("FileDataReference"), fndstp,
      parent);
  appendStringInStorageBuffer(
      fnd->getExtension(), QStringLiteral("Extenstion"), fndstp, parent);
}

void DocumentModelFactory::appendDataSignatureGroupDefinitionFND(
    const libmson::priv::DataSignatureGroupDefinitionFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb, DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendExtendedGuid(
      fnd->getDataSignatureGroup(), QStringLiteral("dataSignatureGroup"),
      fndstp, parent);
}

void DocumentModelFactory::appendObjectGroupStartFND(
    const libmson::priv::ObjectGroupStartFND_SPtr_t& fnd, const quint64 stp,
    const quint64 cb, DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendExtendedGuid(fnd->getOid(), QStringLiteral("oid"), fndstp, parent);
}

void DocumentModelFactory::appendObjectGroupEndFND(
    const libmson::priv::ObjectGroupEndFND_SPtr_t& fnd, const quint64 stp,
    const quint64 cb, DocumentItem* parent)
{
  // no content
  Q_UNUSED(fnd);
  Q_UNUSED(stp);
  Q_UNUSED(cb);
  Q_UNUSED(parent);
}

void DocumentModelFactory::appendChunkTerminatorFND(
    const libmson::priv::ChunkTerminatorFND_SPtr_t& fnd, const quint64 stp,
    const quint64 cb, DocumentItem* parent)
{
  // no content
  Q_UNUSED(fnd);
  Q_UNUSED(stp);
  Q_UNUSED(cb);
  Q_UNUSED(parent);
}


void DocumentModelFactory::appendObjectDeclarationWithRefCountFNDX(
    const libmson::priv::ObjectDeclarationWithRefCountFNDX_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::FileNode_SPtr_t& fn,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendFileNodeChunkReference(
      libmson::priv::getFncrFromChunk(
          revStoreFile, fnd->getObjectRef(), fn->getStpFormatEnum(),
          fn->getCbFormatEnum()),
      QStringLiteral("objectRef"), fndstp, parent);

  appendObjectDeclarationWithRefCountBody(
      fnd->getBody(), QStringLiteral("Body"), fndstp, parent);


  appendUInt8(fnd->getCRef(), QStringLiteral("cRef"), fndstp, parent, false);
}

void DocumentModelFactory::appendObjectDeclarationWithRefCount2FNDX(
    const libmson::priv::ObjectDeclarationWithRefCount2FNDX_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::FileNode_SPtr_t& fn,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendFileNodeChunkReference(
      libmson::priv::getFncrFromChunk(
          revStoreFile, fnd->getObjectRef(), fn->getStpFormatEnum(),
          fn->getCbFormatEnum()),
      QStringLiteral("objectRef"), fndstp, parent);

  appendObjectDeclarationWithRefCountBody(
      fnd->getBody(), QStringLiteral("Body"), fndstp, parent);


  appendUInt32(fnd->getCRef(), QStringLiteral("cRef"), fndstp, parent, false);
}

void DocumentModelFactory::appendObjectRevisionWithRefCountFNDX(
    const libmson::priv::ObjectRevisionWithRefCountFNDX_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::FileNode_SPtr_t& fn,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendFileNodeChunkReference(
      libmson::priv::getFncrFromChunk(
          revStoreFile, fnd->getRef(), fn->getStpFormatEnum(),
          fn->getCbFormatEnum()),
      QStringLiteral("ref"), fndstp, parent);

  appendCompactID(fnd->getOid(), QStringLiteral("OId"), fndstp, parent);

  appendNewChild(
      QStringLiteral("fHasOidReferences"), QStringLiteral("1bit"),
      fnd->getFHasOidReferences() ? QStringLiteral("true")
                                  : QStringLiteral("false"),
      fndstp, 1, parent);

  appendNewChild(
      QStringLiteral("fHasOsidReferences"), QStringLiteral("1bit"),
      fnd->getFHasOsidReferences() ? QStringLiteral("true")
                                   : QStringLiteral("false"),
      fndstp, 1, parent);

  appendUInt8(fnd->getCRef(), QStringLiteral("cRef"), fndstp, parent, false);
}

void DocumentModelFactory::appendObjectRevisionWithRefCount2FNDX(
    const libmson::priv::ObjectRevisionWithRefCount2FNDX_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::FileNode_SPtr_t& fn,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendFileNodeChunkReference(
      libmson::priv::getFncrFromChunk(
          revStoreFile, fnd->getRef(), fn->getStpFormatEnum(),
          fn->getCbFormatEnum()),
      QStringLiteral("ref"), fndstp, parent);

  appendCompactID(fnd->getOid(), QStringLiteral("OId"), fndstp, parent);

  appendNewChild(
      QStringLiteral("fHasOidReferences"), QStringLiteral("1bit"),
      fnd->getFHasOidReferences() ? QStringLiteral("true")
                                  : QStringLiteral("false"),
      fndstp, 1, parent);

  appendNewChild(
      QStringLiteral("fHasOsidReferences"), QStringLiteral("1bit"),
      fnd->getFHasOsidReferences() ? QStringLiteral("true")
                                   : QStringLiteral("false"),
      fndstp, 1, parent);

  fndstp += 4;

  appendUInt32(fnd->getCRef(), QStringLiteral("cRef"), fndstp, parent, false);
}

void DocumentModelFactory::appendObjectDataEncryptionKeyV2FNDX(
    const libmson::priv::ObjectDataEncryptionKeyV2FNDX_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::FileNode_SPtr_t& fn,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendFileNodeChunkReference(
      libmson::priv::getFncrFromChunk(
          revStoreFile, fnd->getBlobRef(), fn->getStpFormatEnum(),
          fn->getCbFormatEnum()),
      QStringLiteral("ref"), fndstp, parent);
}

void DocumentModelFactory::appendObjectInfoDependencyOverridesFND(
    const libmson::priv::ObjectInfoDependencyOverridesFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::FileNode_SPtr_t& fn,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{

  Q_UNUSED(cb);
  quint64 fndstp = stp;


  auto ref = fnd->getRef().lock();

  appendFileNodeChunkReference(
      libmson::priv::getFncrFromChunk(
          revStoreFile, ref, fn->getStpFormatEnum(), fn->getCbFormatEnum()),
      QStringLiteral("ref"), fndstp, parent);

  if (ref == nullptr) {
    appendObjectInfoDependencyOverrideData(
        fnd->getData(), QStringLiteral("Data"), fndstp, parent);
  }
}

void DocumentModelFactory::appendFileDataStoreObjectReferenceFND(
    const libmson::priv::FileDataStoreObjectReferenceFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::FileNode_SPtr_t& fn,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendFileNodeChunkReference(
      libmson::priv::getFncrFromChunk(
          revStoreFile, fnd->getBlobRef(), fn->getStpFormatEnum(),
          fn->getCbFormatEnum()),
      QStringLiteral("ref"), fndstp, parent);

  appendGuid(
      fnd->getGuidReference(), QStringLiteral("GuidReference"), fndstp, parent);
}

void DocumentModelFactory::appendObjectDeclaration2RefCountFND(
    const libmson::priv::ObjectDeclaration2RefCountFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::FileNode_SPtr_t& fn,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendFileNodeChunkReference(
      libmson::priv::getFncrFromChunk(
          revStoreFile, fnd->getBlobRef(), fn->getStpFormatEnum(),
          fn->getCbFormatEnum()),
      QStringLiteral("blobRef"), fndstp, parent);

  appendObjectDeclaration2Body(
      fnd->getBody(), QStringLiteral("Body"), fndstp, parent);
  appendUInt8(fnd->getCRef(), QStringLiteral("cRef"), fndstp, parent, false);
}

void DocumentModelFactory::appendObjectDeclaration2LargeRefCountFND(
    const libmson::priv::ObjectDeclaration2LargeRefCountFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::FileNode_SPtr_t& fn,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendFileNodeChunkReference(
      libmson::priv::getFncrFromChunk(
          revStoreFile, fnd->getBlobRef(), fn->getStpFormatEnum(),
          fn->getCbFormatEnum()),
      QStringLiteral("blobRef"), fndstp, parent);

  appendObjectDeclaration2Body(
      fnd->getBody(), QStringLiteral("Body"), fndstp, parent);
  appendUInt32(fnd->getCRef(), QStringLiteral("cRef"), fndstp, parent, false);
}

void DocumentModelFactory::appendHashedChunkDescriptor2FND(
    const libmson::priv::HashedChunkDescriptor2FND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::FileNode_SPtr_t& fn,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendFileNodeChunkReference(
      libmson::priv::getFncrFromChunk(
          revStoreFile, fnd->getBlobRef(), fn->getStpFormatEnum(),
          fn->getCbFormatEnum()),
      QStringLiteral("ref"), fndstp, parent);

  appendNewChild(
      QStringLiteral("GuidHash"), QStringLiteral("MD5"),
      fnd->getGuidHash().toHex(), fndstp, fnd->getGuidHash().size(), parent);
}

void DocumentModelFactory::appendReadOnlyObjectDeclaration2RefCountFND(
    const libmson::priv::ReadOnlyObjectDeclaration2RefCountFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::FileNode_SPtr_t& fn,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendFileNodeChunkReference(
      libmson::priv::getFncrFromChunk(
          revStoreFile, fnd->getBlobRef(), fn->getStpFormatEnum(),
          fn->getCbFormatEnum()),
      QStringLiteral("objectRef"), fndstp, parent);

  appendObjectDeclaration2Body(
      fnd->getBody(), QStringLiteral("Body"), fndstp, parent);

  appendUInt8(fnd->getCRef(), QStringLiteral("cRef"), fndstp, parent, false);

  appendNewChild(
      QStringLiteral("MD5Hash"), QStringLiteral("byte array"),
      fnd->getMd5hash().toHex(), fndstp, fnd->getMd5hash().size(), parent);
}

void DocumentModelFactory::appendReadOnlyObjectDeclaration2LargeRefCountFND(
    const libmson::priv::ReadOnlyObjectDeclaration2LargeRefCountFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::FileNode_SPtr_t& fn,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendFileNodeChunkReference(
      libmson::priv::getFncrFromChunk(
          revStoreFile, fnd->getBlobRef(), fn->getStpFormatEnum(),
          fn->getCbFormatEnum()),
      QStringLiteral("objectRef"), fndstp, parent);

  appendObjectDeclaration2Body(
      fnd->getBody(), QStringLiteral("Body"), fndstp, parent);

  appendUInt32(fnd->getCRef(), QStringLiteral("cRef"), fndstp, parent, false);

  appendNewChild(
      QStringLiteral("MD5Hash"), QStringLiteral("byte array"),
      fnd->getMd5hash().toHex(), fndstp, fnd->getMd5hash().size(), parent);
}

void DocumentModelFactory::appendFileDataStoreListReferenceFND(
    const libmson::priv::FileDataStoreListReferenceFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::FileNode_SPtr_t& fn,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendFileNodeChunkReference(
      libmson::priv::getFncrFromChunk(
          revStoreFile, fnd->getRef(), fn->getStpFormatEnum(),
          fn->getCbFormatEnum()),
      QStringLiteral("ref"), fndstp, parent);
}

void DocumentModelFactory::appendObjectSpaceManifestListReferenceFND(
    const libmson::priv::ObjectSpaceManifestListReferenceFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::FileNode_SPtr_t& fn,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendFileNodeChunkReference(
      libmson::priv::getFncrFromChunk(
          revStoreFile, fnd->getRef(), fn->getStpFormatEnum(),
          fn->getCbFormatEnum()),
      QStringLiteral("ref"), fndstp, parent);

  appendExtendedGuid(fnd->getGosid(), QStringLiteral("gosid"), fndstp, parent);
}

void DocumentModelFactory::appendRevisionManifestListReferenceFND(
    const libmson::priv::RevisionManifestListReferenceFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::FileNode_SPtr_t& fn,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendFileNodeChunkReference(
      libmson::priv::getFncrFromChunk(
          revStoreFile, fnd->getRef(), fn->getStpFormatEnum(),
          fn->getCbFormatEnum()),
      QStringLiteral("ref"), fndstp, parent);
}

void DocumentModelFactory::appendObjectGroupListReferenceFND(
    const libmson::priv::ObjectGroupListReferenceFND_SPtr_t& fnd,
    const quint64 stp, const quint64 cb,
    const libmson::priv::FileNode_SPtr_t& fn,
    const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
    DocumentItem* parent)
{
  Q_UNUSED(cb);
  quint64 fndstp = stp;

  appendFileNodeChunkReference(
      libmson::priv::getFncrFromChunk(
          revStoreFile, fnd->getRef(), fn->getStpFormatEnum(),
          fn->getCbFormatEnum()),
      QStringLiteral("ref"), fndstp, parent);

  appendExtendedGuid(
      fnd->getObjectGroupID(), QStringLiteral("ObjectGroupID"), fndstp, parent);
}

DocumentItem* DocumentModelFactory::appendTransactionEntry(
    const libmson::priv::TransactionEntry& entry, const QString& name,
    quint64& stp, DocumentItem* parent)
{
  const quint64 cb = libmson::priv::TransactionEntry::getSizeInFile();

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("TransactionEntry"),
      "0x" + QString::number(entry.getSrcID(), 16) + ", 0x" +
          QString::number(entry.getTransactionEntrySwitch(), 16),
      stp, cb, parent);

  appendUInt32(entry.getSrcID(), QStringLiteral("srcID"), stp, item);
  appendUInt32(
      entry.getTransactionEntrySwitch(),
      QStringLiteral("TransactionEntrySwitch"), stp, item);

  return item;
}


DocumentItem* DocumentModelFactory::appendObjectSpaceObjectStreamHeader(
    const libmson::priv::ObjectSpaceObjectStreamHeader& streamHeader,
    const QString& name, quint64& stp, DocumentItem* parent)
{
  const quint64 cb = sizeof(quint32);

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("ObjectSpaceObjectStreamHeader"), QString(), stp, cb,
      parent);

  appendNewChild(
      QStringLiteral("Count"), QStringLiteral("uint24_t"),
      QString::number(streamHeader.getCount()), stp, 3, item);

  stp += 3;

  appendNewChild(
      QStringLiteral("ExtendedStreamsPresent"), QStringLiteral("1 bit"),
      streamHeader.isExtendedStreamPresent() ? QStringLiteral("true")
                                             : QStringLiteral("false"),
      stp, 1, item);
  appendNewChild(
      QStringLiteral("OsidStreamNotPresent"), QStringLiteral("1 bit"),
      streamHeader.isOsidStreamNotPresent() ? QStringLiteral("true")
                                            : QStringLiteral("false"),
      stp, 1, item);
  stp++;

  return item;
}

DocumentItem* DocumentModelFactory::appendObjectSpaceObjectStreamOfOIDs(
    const libmson::priv::ObjectSpaceObjectStreamOfOIDs& stream,
    const QString& name, quint64& stp, DocumentItem* parent)
{
  const quint64 cb = stream.getSizeInFile();


  DocumentItem* item = appendNewChild(
      name, QStringLiteral("ObjectSpaceObjectStreamOfOIDs"),
      QString::number(stream.getHeader().getCount()) + " IDs", stp, cb, parent);

  appendObjectSpaceObjectStreamHeader(
      stream.getHeader(), QStringLiteral("Header"), stp, item);

  auto* ids = appendNewChild(
      QStringLiteral("Ids"), QString(), QString(), stp,
      stream.getBody().size() * libmson::priv::CompactID::getSizeInFile(),
      item);

  for (auto&& entry : stream.getBody()) {
    appendCompactID(entry, QStringLiteral("ObjectIdentity"), stp, ids);
  }

  return item;
}

DocumentItem* DocumentModelFactory::appendObjectSpaceObjectStreamOfOSIDs(
    const libmson::priv::ObjectSpaceObjectStreamOfOSIDs& stream,
    const QString& name, quint64& stp, DocumentItem* parent)
{
  const quint64 cb = stream.getSizeInFile();


  DocumentItem* item = appendNewChild(
      name, QStringLiteral("ObjectSpaceObjectStreamOfOSIDs"),
      QString::number(stream.getHeader().getCount()) + " IDs", stp, cb, parent);

  appendObjectSpaceObjectStreamHeader(
      stream.getHeader(), QStringLiteral("Header"), stp, item);

  auto* ids = appendNewChild(
      QStringLiteral("Ids"), QString(), QString(), stp,
      stream.getBody().size() * libmson::priv::CompactID::getSizeInFile(),
      item);

  for (auto&& entry : stream.getBody()) {
    appendCompactID(entry, QStringLiteral("ObjectSpaceIdentity"), stp, ids);
  }

  return item;
}

DocumentItem* DocumentModelFactory::appendObjectSpaceObjectStreamOfContextIDs(
    const libmson::priv::ObjectSpaceObjectStreamOfContextIDs& stream,
    const QString& name, quint64& stp, DocumentItem* parent)
{
  const quint64 cb = stream.getSizeInFile();


  DocumentItem* item = appendNewChild(
      name, QStringLiteral("ObjectSpaceObjectStreamOfContextIDs"),
      QString::number(stream.getHeader().getCount()) + " IDs", stp, cb, parent);

  appendObjectSpaceObjectStreamHeader(
      stream.getHeader(), QStringLiteral("Header"), stp, item);

  auto* ids = appendNewChild(
      QStringLiteral("Ids"), QString(), QString(), stp,
      stream.getBody().size() * libmson::priv::CompactID::getSizeInFile(),
      item);

  for (auto&& entry : stream.getBody()) {
    appendCompactID(entry, QStringLiteral("ContextIdentity"), stp, ids);
  }

  return item;
}

DocumentItem* DocumentModelFactory::appendPropertySet(
    const libmson::priv::PropertySet& prop, const QString& name, quint64& stp,
    DocumentItem* parent)
{
  const quint64 cb = prop.getSizeInFile();


  DocumentItem* item = appendNewChild(
      name, QStringLiteral("PropertySet"), QString(), stp, cb, parent);

  appendUInt16(
      prop.cProperties(), QStringLiteral("cProperties"), stp, item, false);

  auto* prids = appendNewChild(
      QStringLiteral("rgPropertyIds"), QString(), QString(), stp,
      prop.cProperties() * libmson::priv::PropertyID::getSizeInFile(), item);
  for (auto&& id : prop.rgPrids()) {
    appendPropertyID(id, stp, prids);
  }

  const auto vec = prop.rgData();

  quint64 cbData = std::accumulate(
      vec.begin(), vec.end(), 0,
      [](quint64 sum, const libmson::priv::IPropertyType_SPtr_t& pt) {
        return sum + pt->getSizeInFile();
      });

  auto* rgData = appendNewChild(
      QStringLiteral("rgData"), QString(), QString(), stp, cbData, item);

  for (const auto& entry : vec) {


    switch (entry->getType()) {
    case libmson::priv::PropertyIDType::NoData:
    case libmson::priv::PropertyIDType::Bool:
    case libmson::priv::PropertyIDType::ContextID:
    case libmson::priv::PropertyIDType::ObjectSpaceID:
    case libmson::priv::PropertyIDType::ObjectID:
      appendPTNoData(stp, rgData);
      break;

    case libmson::priv::PropertyIDType::ArrayOfObjectIDs:
    case libmson::priv::PropertyIDType::ArrayOfObjectSpaceIDs:
    case libmson::priv::PropertyIDType::ArrayOfContextIDs:
    case libmson::priv::PropertyIDType::ArrayNumber:
      appendPTArrayNumber(
          std::static_pointer_cast<libmson::priv::PropertyType_ArrayNumber>(
              entry),
          stp, rgData);
      break;

    case libmson::priv::PropertyIDType::OneByteOfData:
      appendPTOneByteOfData(
          std::dynamic_pointer_cast<libmson::priv::PropertyType_OneByteOfData>(
              entry),
          stp, rgData);
      break;

    case libmson::priv::PropertyIDType::TwoBytesOfData:
      appendPTTwoBytesOfData(
          std::dynamic_pointer_cast<libmson::priv::PropertyType_TwoBytesOfData>(
              entry),
          stp, rgData);
      break;

    case libmson::priv::PropertyIDType::FourBytesOfData:
      appendPTFourBytesOfData(
          std::dynamic_pointer_cast<
              libmson::priv::PropertyType_FourBytesOfData>(entry),
          stp, rgData);
      break;

    case libmson::priv::PropertyIDType::EightBytesOfData:
      appendPTEightBytesOfData(
          std::dynamic_pointer_cast<
              libmson::priv::PropertyType_EightBytesOfData>(entry),
          stp, rgData);
      break;

    case libmson::priv::PropertyIDType::FourBytesOfLengthFollowedByData:
      appendPTFourBytesOfLengthFollowedByData(
          std::dynamic_pointer_cast<
              libmson::priv::PropertyType_FourBytesOfLengthFollowedByData>(
              entry),
          stp, rgData);
      break;

    case libmson::priv::PropertyIDType::ArrayOfPropertyValues:
      appendPTArrayOfPropertyValues(
          std::dynamic_pointer_cast<
              libmson::priv::PropertyType_ArrayOfPropertyValues>(entry),
          stp, rgData);
      break;

    case libmson::priv::PropertyIDType::PropertySet:
      appendPTPropertySet(
          std::dynamic_pointer_cast<libmson::priv::PropertyType_PropertySet>(
              entry),
          stp, rgData);
      break;

    default:
      break;
    }
  }

  return item;
}


DocumentItem* DocumentModelFactory::appendPropertyID(
    const libmson::priv::PropertyID& propId, quint64& stp, DocumentItem* parent)
{
  const quint64 cb = libmson::priv::PropertyID::getSizeInFile();

  DocumentItem* item = appendNewChild(
      propId.idToString(), QStringLiteral("PropertyID"), propId.typeToString(),
      stp, cb, parent);

  appendNewChild(
      QStringLiteral("Id"), QStringLiteral("uint26_t"), propId.idToString(),
      stp, cb, item);

  appendNewChild(
      QStringLiteral("Type"), QStringLiteral("uint5_t"), propId.typeToString(),
      stp + 3, 1, item);

  appendNewChild(
      QStringLiteral("BoolValue"), QStringLiteral("1 bit"),
      propId.boolValue() ? QStringLiteral("true") : QStringLiteral("false"),
      stp + 3, 1, item);

  appendUInt32(propId.value(), QStringLiteral("Composite ID"), stp, item);

  return item;
}

DocumentItem* DocumentModelFactory::appendPTArrayNumber(
    const libmson::priv::PropertyType_ArrayNumber_SPtr_t& pt, quint64& stp,
    DocumentItem* parent)
{
  const quint64 cb = sizeof(quint32);

  DocumentItem* item = appendNewChild(
      QStringLiteral("ArrayNumber"), QString(),
      QString(QString::number(pt->cCIDs()) + " IDs"), stp, cb, parent);

  appendUInt32(pt->cCIDs(), QStringLiteral("cIDs"), stp, item, false);

  return item;
}

DocumentItem* DocumentModelFactory::appendPTArrayOfPropertyValues(
    const libmson::priv::PropertyType_ArrayOfPropertyValues_SPtr_t& pt,
    quint64& stp, DocumentItem* parent)
{
  const quint64 cb = pt->getSizeInFile();

  DocumentItem* item = appendNewChild(
      QStringLiteral("ArrayOfPropertyValues"), QString(), QString(), stp, cb,
      parent);

  appendUInt32(
      pt->cProperties(), QStringLiteral("cProperties"), stp, item, false);

  appendPropertyID(pt->prid(), stp, item);

  const auto vec = pt->data();

  quint64 propsetsize = std::accumulate(
      vec.begin(), vec.end(), 0,
      [](quint64 sum, const libmson::priv::PropertySet& set) {
        return sum + set.getSizeInFile();
      });

  auto* propsets = appendNewChild(
      QStringLiteral("PropertySets"), QString(), QString(), stp, propsetsize,
      item);

  for (auto&& propset : pt->data()) {
    appendPropertySet(propset, QStringLiteral("PropertySet"), stp, propsets);
  }

  return item;
}

DocumentItem* DocumentModelFactory::appendPTEightBytesOfData(
    const libmson::priv::PropertyType_EightBytesOfData_SPtr_t& pt, quint64& stp,
    DocumentItem* parent)
{
  const quint64 cb = sizeof(quint64);

  DocumentItem* item = appendNewChild(
      QStringLiteral("EightBytesOfData"), QString(), pt->data().toHex(), stp,
      cb, parent);
  stp += cb;
  return item;
}

DocumentItem* DocumentModelFactory::appendPTFourBytesOfData(
    const libmson::priv::PropertyType_FourBytesOfData_SPtr_t& pt, quint64& stp,
    DocumentItem* parent)
{
  const quint64 cb = sizeof(quint32);

  DocumentItem* item = appendNewChild(
      QStringLiteral("FourBytesOfData"), QString(), pt->data().toHex(), stp, cb,
      parent);
  stp += cb;
  return item;
}

DocumentItem* DocumentModelFactory::appendPTFourBytesOfLengthFollowedByData(
    const libmson::priv::PropertyType_FourBytesOfLengthFollowedByData_SPtr_t&
        pt,
    quint64& stp, DocumentItem* parent)
{
  const quint64 cb = pt->getSizeInFile();

  DocumentItem* item = appendNewChild(
      QStringLiteral("FourBytesOfLengthFollowedByData"), QString(),
      QString(QString::number(pt->cb()) + " bytes"), stp, cb, parent);

  appendUInt32(pt->cb(), QStringLiteral("Length"), stp, item, false);

  appendNewChild(
      QStringLiteral("Data"), QString(), pt->data().toHex(), stp, cb - 4, item);

  stp += cb - 4;
  return item;
}

DocumentItem* DocumentModelFactory::appendPTOneByteOfData(
    const libmson::priv::PropertyType_OneByteOfData_SPtr_t& pt, quint64& stp,
    DocumentItem* parent)
{
  const quint64 cb = sizeof(quint8);

  DocumentItem* item = appendNewChild(
      QStringLiteral("TwoBytesOfData"), QString(), pt->data().toHex(), stp, cb,
      parent);
  stp += cb;
  return item;
}

DocumentItem* DocumentModelFactory::appendPTPropertySet(
    const libmson::priv::PropertyType_PropertySet_SPtr_t& pt, quint64& stp,
    DocumentItem* parent)
{

  DocumentItem* item =
      appendPropertySet(pt->data(), "PropertySet", stp, parent);

  return item;
}


DocumentItem* DocumentModelFactory::appendPTTwoBytesOfData(
    const libmson::priv::PropertyType_TwoBytesOfData_SPtr_t& pt, quint64& stp,
    DocumentItem* parent)
{
  const quint64 cb = sizeof(quint16);

  DocumentItem* item = appendNewChild(
      QStringLiteral("TwoBytesOfData"), QString(), pt->data().toHex(), stp, cb,
      parent);
  stp += cb;
  return item;
}

DocumentItem*
DocumentModelFactory::appendPTNoData(quint64& stp, DocumentItem* parent)
{

  DocumentItem* item = appendNewChild(
      QStringLiteral("NoData"), QString(), QString(), stp, 0, parent);

  return item;
}


quint64 DocumentModelFactory::appendPackagingStructureHeader(
    const libmson::packStore::PackageStoreFile_SPtr_t& packStoreFile,
    DocumentItem* parent)
{
  auto header = packStoreFile->getHeader();

  quint64 stp = 0;

  // add Header
  auto* headerItem = appendNewChild(
      QStringLiteral("Header"), QStringLiteral("PackagingStructure"),
      QStringLiteral("PackageStoreFile"), stp, header.getSizeInFile(), parent);

  appendGuid(
      header.getGuidFileType(), QStringLiteral("GuidFileType"), stp,
      headerItem);

  appendGuid(header.getGuidFile(), QStringLiteral("GuidFile"), stp, headerItem);

  appendGuid(
      header.getGuidLegacyFileVersion(),
      QStringLiteral("GuidLegacyFileVersion"), stp, headerItem);

  appendGuid(
      header.getGuidFileFormat(), QStringLiteral("GuidFileFormat"), stp,
      headerItem);

  appendNewChild(
      QStringLiteral("reserved"), QString(), QString(), stp, 4, headerItem);
  stp += 4;

  return stp;
}

DocumentItem* DocumentModelFactory::appendStreamObject(
    const libmson::fsshttpb::IStreamObject_SPtr_t& obj, quint64& stp,
    DocumentItem* parent)
{

  DocumentItem* composite;

  switch (obj->getType()) {
    //  case libmson::fsshttpb::StreamObjectType::Invalid:
    //    break;
  case libmson::fsshttpb::StreamObjectType::DataElement: {
    auto cast = std::static_pointer_cast<libmson::fsshttpb::DataElement>(obj);
    composite = appendDataElement(cast, stp, parent);
    break;
  }
  case libmson::fsshttpb::StreamObjectType::ObjectDataBLOB: {
    auto cast =
        std::static_pointer_cast<libmson::fsshttpb::ObjectDataBLOB>(obj);
    composite = appendObjectDataBLOB(cast, stp, parent);
    break;
  }
  case libmson::fsshttpb::StreamObjectType::ObjectGroupObjectExcludedData: {
    auto cast = std::static_pointer_cast<
        libmson::fsshttpb::ObjectGroupObjectExcludedData>(obj);
    composite = appendObjectGroupObjectExcludedData(cast, stp, parent);
    break;
  }
    //  case libmson::fsshttpb::StreamObjectType::WaterlineKnowledgeEntry:
    //    break;
  case libmson::fsshttpb::StreamObjectType::
      ObjectGroupObjectDataBLOBDeclaration: {
    auto cast = std::static_pointer_cast<
        libmson::fsshttpb::ObjectGroupObjectDataBLOBDeclaration>(obj);
    composite = appendObjectGroupObjectDataBLOBDeclaration(cast, stp, parent);
    break;
  }
  case libmson::fsshttpb::StreamObjectType::DataElementHash: {
    auto cast =
        std::static_pointer_cast<libmson::fsshttpb::DataElementHash>(obj);
    composite = appendDataElementHash(cast, stp, parent);
    break;
  }
  case libmson::fsshttpb::StreamObjectType::StorageManifestRootDeclare: {
    auto cast =
        std::static_pointer_cast<libmson::fsshttpb::StorageManifestRootDeclare>(
            obj);
    composite = appendStorageManifestRootDeclare(cast, stp, parent);
    break;
  }
  case libmson::fsshttpb::StreamObjectType::RevisionManifestRootDeclare: {
    auto cast = std::static_pointer_cast<
        libmson::fsshttpb::RevisionManifestRootDeclare>(obj);
    composite = appendRevisionManifestRootDeclare(cast, stp, parent);
    break;
  }
  case libmson::fsshttpb::StreamObjectType::CellManifestCurrentRevision: {
    auto cast = std::static_pointer_cast<
        libmson::fsshttpb::CellManifestCurrentRevision>(obj);
    composite = appendCellManifestCurrentRevision(cast, stp, parent);
    break;
  }
  case libmson::fsshttpb::StreamObjectType::StorageManifestSchemaGUID: {
    auto cast =
        std::static_pointer_cast<libmson::fsshttpb::StorageManifestSchemaGUID>(
            obj);
    composite = appendStorageManifestSchemaGUID(cast, stp, parent);
    break;
  }
  case libmson::fsshttpb::StreamObjectType::StorageIndexRevisionMapping: {
    auto cast = std::static_pointer_cast<
        libmson::fsshttpb::StorageIndexRevisionMapping>(obj);
    composite = appendStorageIndexRevisionMapping(cast, stp, parent);
    break;
  }
  case libmson::fsshttpb::StreamObjectType::StorageIndexCellMapping: {
    auto cast =
        std::static_pointer_cast<libmson::fsshttpb::StorageIndexCellMapping>(
            obj);
    composite = appendStorageIndexCellMapping(cast, stp, parent);
    break;
  }
    //  case libmson::fsshttpb::StreamObjectType::CellKnowledgeRange:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::Knowledge:
    //    break;
  case libmson::fsshttpb::StreamObjectType::StorageIndexManifestMapping: {
    auto cast = std::static_pointer_cast<
        libmson::fsshttpb::StorageIndexManifestMapping>(obj);
    composite = appendStorageIndexManifestMapping(cast, stp, parent);
    break;
  }
    //  case libmson::fsshttpb::StreamObjectType::CellKnowledge:
    //    break;
  case libmson::fsshttpb::StreamObjectType::DataElementPackage: {
    auto cast =
        std::static_pointer_cast<libmson::fsshttpb::DataElementPackage>(obj);
    composite = appendDataElementPackage(cast, stp, parent);
    break;
  }
  case libmson::fsshttpb::StreamObjectType::ObjectGroupObjectData: {
    auto cast =
        std::static_pointer_cast<libmson::fsshttpb::ObjectGroupObjectData>(obj);
    composite = appendObjectGroupObjectData(cast, stp, parent);
    break;
  }
    //  case libmson::fsshttpb::StreamObjectType::CellKnowledgeEntry:
    //    break;
  case libmson::fsshttpb::StreamObjectType::ObjectGroupObjectDeclare: {
    auto cast =
        std::static_pointer_cast<libmson::fsshttpb::ObjectGroupObjectDeclare>(
            obj);
    composite = appendObjectGroupObjectDeclare(cast, stp, parent);
    break;
  }
  case libmson::fsshttpb::StreamObjectType::
      RevisionManifestObjectGroupReference: {
    auto cast = std::static_pointer_cast<
        libmson::fsshttpb::RevisionManifestObjectGroupReference>(obj);
    composite = appendRevisionManifestObjectGroupReference(cast, stp, parent);
    break;
  }
  case libmson::fsshttpb::StreamObjectType::RevisionManifest: {
    auto cast =
        std::static_pointer_cast<libmson::fsshttpb::RevisionManifest>(obj);
    composite = appendRevisionManifest(cast, stp, parent);
    break;
  }
  case libmson::fsshttpb::StreamObjectType::
      ObjectGroupObjectDataBLOBReference: {
    auto cast = std::static_pointer_cast<
        libmson::fsshttpb::ObjectGroupObjectDataBLOBReference>(obj);
    composite = appendObjectGroupObjectDataBLOBReference(cast, stp, parent);
    break;
  }
  case libmson::fsshttpb::StreamObjectType::ObjectGroupDeclarations: {
    auto cast =
        std::static_pointer_cast<libmson::fsshttpb::ObjectGroupDeclarations>(
            obj);
    composite = appendObjectGroupDeclarations(cast, stp, parent);
    break;
  }
  case libmson::fsshttpb::StreamObjectType::ObjectGroupData: {
    auto cast =
        std::static_pointer_cast<libmson::fsshttpb::ObjectGroupData>(obj);
    composite = appendObjectGroupData(cast, stp, parent);
    break;
  }
    //  case libmson::fsshttpb::StreamObjectType::WaterlineKnowledge:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::ContentTagKnowledge:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::ContentTagKnowledgeEntry:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::QueryChangesVersioning:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::Request:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::Subresponse:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::Subrequest:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::ReadAccessResponse:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::SpecializedKnowledge:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::WriteAccessResponse:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::QueryChangesFilter:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::ErrorWin32:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::ErrorProtocol:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::Error:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::ErrorStringSupplementalInfo:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::UserAgentVersion:
    //    break;
    //  case
    //  libmson::fsshttpb::StreamObjectType::QueryChangesFilterSchemaSpecific:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::QueryChangesRequest:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::ErrorHRESULT:
    //    break;
    //  case
    //  libmson::fsshttpb::StreamObjectType::QueryChangesFilterDataElementIDs:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::UserAgentGUID:
    //    break;
    //  case
    //  libmson::fsshttpb::StreamObjectType::QueryChangesFilterDataElementType:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::QueryChangesDataConstraint:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::PutChangesRequest:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::QueryChangesRequestArguments:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::QueryChangesFilterCellID:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::UserAgent:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::QueryChangesResponse:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::QueryChangesFilterHierarchy:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::Response:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::ErrorCell:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::QueryChangesFilterFlags:
    //    break;
  case libmson::fsshttpb::StreamObjectType::DataElementFragment: {
    auto cast =
        std::static_pointer_cast<libmson::fsshttpb::DataElementFragment>(obj);
    composite = appendDataElementFragment(cast, stp, parent);
    break;
  }
    //  case libmson::fsshttpb::StreamObjectType::FragmentKnowledge:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::FragmentKnowledgeEntry:
    //    break;
  case libmson::fsshttpb::StreamObjectType::ObjectGroupMetadata: {
    auto cast =
        std::static_pointer_cast<libmson::fsshttpb::ObjectGroupMetadata>(obj);
    composite = appendObjectGroupMetadata(cast, stp, parent);
    break;
  }
  case libmson::fsshttpb::StreamObjectType::ObjectGroupMetadataDeclarations: {
    auto cast = std::static_pointer_cast<
        libmson::fsshttpb::ObjectGroupMetadataDeclarations>(obj);
    composite = appendObjectGroupMetadataDeclarations(cast, stp, parent);
    break;
  }
  case libmson::fsshttpb::StreamObjectType::ONPackageStart: {
    auto cast =
        std::static_pointer_cast<libmson::fsshttpb::PackagingStart>(obj);
    composite = appendPackagingStart(cast, stp, parent);
    break;
  }
    //  case
    //  libmson::fsshttpb::StreamObjectType::AllocateExtendedGUIDRangeRequest:
    //    break;
    //  case
    //  libmson::fsshttpb::StreamObjectType::AllocateExtendedGUIDRangeResponse:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::TargetPartitionId:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::PutChangesLockId:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::AdditionalFlags:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::PutChangesResponse:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::RequestHashingOptions:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::DiagnosticRequestOptionOutput:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::DiagnosticRequestOptionInput:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::UserAgentClientAndPlatform:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::VersionTokenKnowledge:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::CellRoundtripOptions:
    //    break;
    //  case libmson::fsshttpb::StreamObjectType::FileHash:
    //    break;
  default:
    composite = appendIStreamObject(obj, stp, parent);
    break;
  }

  auto children = obj->getObjects();

  quint64 cbChildren = std::accumulate(
      children.begin(), children.end(), 0, [](quint64 sum, const auto& ptr) {
        return sum + ptr.lock()->getSizeInFile();
      });


  if (obj->isCompound()) {
    auto* childrenItem = appendNewChild(
        QStringLiteral("Children"), QString(),
        QString::number(obj->size()) + QString(" objects"), stp, cbChildren,
        composite);

    libmson::fsshttpb::IStreamObject_SPtr_t child;
    for (const auto& ptr : obj->getObjects()) {

      child = ptr.lock();
      if (child != nullptr) {
        appendStreamObject(child, stp, childrenItem);
      }
    }

    appendStreamObjectHeaderEnd(obj->getType(), stp, composite);
  }


  return composite;
}

DocumentItem* DocumentModelFactory::appendIStreamObject(
    const libmson::fsshttpb::IStreamObject_SPtr_t& obj, quint64& stp,
    DocumentItem* parent)
{


  auto item = appendNewChild(
      QStringLiteral("IStreamObject"),
      libmson::fsshttpb::streamObjectTypeToString(obj->getType()), QString(),
      stp, obj->getSizeInFile(), parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);
  stp += obj->getCbNextHeader();

  return item;
}

DocumentItem* DocumentModelFactory::appendCellManifestCurrentRevision(
    const libmson::fsshttpb::CellManifestCurrentRevision_SPtr_t& obj,
    quint64& stp, DocumentItem* parent)
{
  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("CellManifestCurrentRevision"),
      QStringLiteral("StreamObject"), QString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);

  appendCompactExtGuid(
      obj->getExtendedGuid(), QStringLiteral("Current Revision"), stp, item);


  return item;
}

DocumentItem* DocumentModelFactory::appendPackagingStart(
    const libmson::fsshttpb::PackagingStart_SPtr_t& obj, quint64& stp,
    DocumentItem* parent)
{

  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("PackagingStart"), QStringLiteral("StreamObject"),
      QString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);

  appendCompactExtGuid(
      obj->getStorageIndex(), QStringLiteral("StorageIndexExtendedGUID"), stp,
      item);

  appendGuid(
      obj->getGuidCellSchemaId(), QStringLiteral("guidCellSchemaId"), stp,
      item);

  return item;
}

DocumentItem* DocumentModelFactory::appendRevisionManifest(
    const libmson::fsshttpb::RevisionManifest_SPtr_t& obj, quint64& stp,
    DocumentItem* parent)
{
  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("RevisionManifest"), QStringLiteral("StreamObject"),
      QString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);

  appendCompactExtGuid(
      obj->getRevisionId(), QStringLiteral("RevisionId"), stp, item);

  appendCompactExtGuid(
      obj->getBaseRevisionId(), QStringLiteral("BaseRevisionId"), stp, item);

  return item;
}

DocumentItem* DocumentModelFactory::appendRevisionManifestRootDeclare(
    const libmson::fsshttpb::RevisionManifestRootDeclare_SPtr_t& obj,
    quint64& stp, DocumentItem* parent)
{

  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("RevisionManifestRootDeclare"),
      QStringLiteral("StreamObject"), QString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);

  appendCompactExtGuid(
      obj->getRootGUID(), QStringLiteral("RootExtendedGUID"), stp, item);

  appendCompactExtGuid(
      obj->getObjectGUID(), QStringLiteral("ObjectExtendedGUID"), stp, item);

  return item;
}

DocumentItem* DocumentModelFactory::appendRevisionManifestObjectGroupReference(
    const libmson::fsshttpb::RevisionManifestObjectGroupReference_SPtr_t& obj,
    quint64& stp, DocumentItem* parent)
{
  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("RevisionManifestObjectGroupReferenc"),
      QStringLiteral("StreamObject"), QString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);

  appendCompactExtGuid(
      obj->getObjectGroup(), QStringLiteral("ObjectGroup"), stp, item);

  return item;
}

DocumentItem* DocumentModelFactory::appendStorageIndexCellMapping(
    const libmson::fsshttpb::StorageIndexCellMapping_SPtr_t& obj, quint64& stp,
    DocumentItem* parent)
{
  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("StorageIndexCellMapping"), QStringLiteral("StreamObject"),
      QString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);

  appendCellId(obj->getCellId(), QStringLiteral("Cell ID"), stp, item);

  appendCompactExtGuid(
      obj->getExtendedGuid(), QStringLiteral("Cell Mapping"), stp, item);

  appendLongExtGuid(
      obj->getSerialNumber(), QStringLiteral("Serial Number"), stp, item);

  return item;
}

DocumentItem* DocumentModelFactory::appendStorageIndexManifestMapping(
    const libmson::fsshttpb::StorageIndexManifestMapping_SPtr_t& obj,
    quint64& stp, DocumentItem* parent)
{
  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("StorageIndexManifestMapping"),
      QStringLiteral("StreamObject"), QString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);

  appendCompactExtGuid(
      obj->getExtendedGuid(), QStringLiteral("Manifest Mapping"), stp, item);

  appendLongExtGuid(
      obj->getSerialNumber(), QStringLiteral("Serial Number"), stp, item);

  return item;
}

DocumentItem* DocumentModelFactory::appendStorageIndexRevisionMapping(
    const libmson::fsshttpb::StorageIndexRevisionMapping_SPtr_t& obj,
    quint64& stp, DocumentItem* parent)
{
  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("StorageIndexRevisionMapping"),
      QStringLiteral("StreamObject"), QString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);

  appendCompactExtGuid(
      obj->getRevision(), QStringLiteral("Revision"), stp, item);

  appendCompactExtGuid(
      obj->getExtendedGuid(), QStringLiteral("Revision Mapping"), stp, item);

  appendLongExtGuid(
      obj->getSerialNumber(), QStringLiteral("Serial Number"), stp, item);

  return item;
}

DocumentItem* DocumentModelFactory::appendStorageManifestRootDeclare(
    const libmson::fsshttpb::StorageManifestRootDeclare_SPtr_t& obj,
    quint64& stp, DocumentItem* parent)
{
  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("StorageIndexRevisionMapping"),
      QStringLiteral("StreamObject"), QString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);

  appendCompactExtGuid(
      obj->getExtendedGuid(), QStringLiteral("Root"), stp, item);

  appendCellId(obj->getCellId(), QStringLiteral("Cell ID"), stp, item);


  return item;
}

DocumentItem* DocumentModelFactory::appendStorageManifestSchemaGUID(
    const libmson::fsshttpb::StorageManifestSchemaGUID_SPtr_t& obj,
    quint64& stp, DocumentItem* parent)
{
  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("StorageIndexRevisionMapping"),
      QStringLiteral("StreamObject"), QString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);
  appendGuid(obj->getGuid(), QStringLiteral("Schema GUID"), stp, item);

  return item;
}

DocumentItem* DocumentModelFactory::appendDataElementPackage(
    const libmson::fsshttpb::DataElementPackage_SPtr_t& obj, quint64& stp,
    DocumentItem* parent)
{
  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("DataElementPackage"), QStringLiteral("StreamObject"),
      QString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);

  appendUInt8(0, QStringLiteral("reserved"), stp, item);

  return item;
}

DocumentItem* DocumentModelFactory::appendObjectDataBLOB(
    const libmson::fsshttpb::ObjectDataBLOB_SPtr_t& obj, quint64& stp,
    DocumentItem* parent)
{
  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("ObjectDataBLOB"), QStringLiteral("StreamObject"),
      QString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);

  appendNewChild(
      QStringLiteral("Data"), QStringLiteral("ByteArray"),
      obj->getData().toHex(), stp, obj->getData().size(), item);
  stp += obj->getData().size();

  return item;
}

DocumentItem* DocumentModelFactory::appendObjectGroupData(
    const libmson::fsshttpb::ObjectGroupData_SPtr_t& obj, quint64& stp,
    DocumentItem* parent)
{
  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("ObjectGroupData"), QStringLiteral("StreamObject"),
      QString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);

  return item;
}

DocumentItem* DocumentModelFactory::appendObjectGroupDeclarations(
    const libmson::fsshttpb::ObjectGroupDeclarations_SPtr_t& obj, quint64& stp,
    DocumentItem* parent)
{
  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("ObjectGroupDeclarations"), QStringLiteral("StreamObject"),
      QString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);

  return item;
}

DocumentItem* DocumentModelFactory::appendObjectGroupMetadata(
    const libmson::fsshttpb::ObjectGroupMetadata_SPtr_t& obj, quint64& stp,
    DocumentItem* parent)
{
  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("ObjectGroupMetadata"), QStringLiteral("StreamObject"),
      QString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);

  appendCompactU64(
      obj->getObjectChangeFrequency(),
      QStringLiteral("Object Change Frequency"), stp, item);

  return item;
}

DocumentItem* DocumentModelFactory::appendObjectGroupMetadataDeclarations(
    const libmson::fsshttpb::ObjectGroupMetadataDeclarations_SPtr_t& obj,
    quint64& stp, DocumentItem* parent)
{
  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("ObjectGroupMetadata"), QStringLiteral("StreamObject"),
      QString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);

  return item;
}

DocumentItem* DocumentModelFactory::appendObjectGroupObjectData(
    const libmson::fsshttpb::ObjectGroupObjectData_SPtr_t& obj, quint64& stp,
    DocumentItem* parent)
{
  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("ObjectGroupObjectData"), QStringLiteral("StreamObject"),
      QString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);

  appendCompactExtGuidArray(
      obj->getExtendedGuidArray(), QStringLiteral("ObjectExtendedGuidArray"),
      stp, item);
  appendCellIdArray(
      obj->getCellIdArray(), QStringLiteral("CellIDArray"), stp, item);


  auto size = obj->getData().size();
  appendCompactU64(size, QStringLiteral("DataSize"), stp, item);
  if (size >= 0) {
    appendNewChild(
        QStringLiteral("Data"), QStringLiteral("ByteArray"),
        obj->getData().toHex(), stp, size, item);
    stp += size;
  }

  return item;
}

DocumentItem* DocumentModelFactory::appendObjectGroupObjectDataBLOBDeclaration(
    const libmson::fsshttpb::ObjectGroupObjectDataBLOBDeclaration_SPtr_t& obj,
    quint64& stp, DocumentItem* parent)
{
  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("GroupObjectDataBLOBDeclaration"),
      QStringLiteral("StreamObject"), QString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);

  appendCompactExtGuid(
      obj->getExtendedGuid(), QStringLiteral("ObjectExtendedGUID"), stp, item);
  appendCompactExtGuid(
      obj->getBlobExtendedGuid(), QStringLiteral("Object Data BLOB EXGUID"),
      stp, item);

  appendCompactU64(
      obj->getPartitionId(), QStringLiteral("PartitionID"), stp, item);
  appendCompactU64(
      obj->getObjectReferencesCount(), QStringLiteral("ObjectReferencesCount"),
      stp, item);
  appendCompactU64(
      obj->getCellReferencesCount(), QStringLiteral("CellReferencesCount"), stp,
      item);


  return item;
}

DocumentItem* DocumentModelFactory::appendObjectGroupObjectDataBLOBReference(
    const libmson::fsshttpb::ObjectGroupObjectDataBLOBReference_SPtr_t& obj,
    quint64& stp, DocumentItem* parent)
{
  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("GroupObjectDataBLOBReference"),
      QStringLiteral("StreamObject"), QString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);

  appendCompactExtGuidArray(
      obj->getObjectExtGuidArray(),
      QStringLiteral("Object Extended GUID Array"), stp, item);
  appendCellIdArray(
      obj->getCellIdArray(), QStringLiteral("Cell ID Array"), stp, item);
  appendCompactExtGuid(
      obj->getExtendedGuid(), QStringLiteral("BLOB Extended GUID"), stp, item);


  return item;
}

DocumentItem* DocumentModelFactory::appendObjectGroupObjectDeclare(
    const libmson::fsshttpb::ObjectGroupObjectDeclare_SPtr_t& obj, quint64& stp,
    DocumentItem* parent)
{
  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("GroupObjectDeclare"), QStringLiteral("StreamObject"),
      QString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);

  appendCompactExtGuid(
      obj->getExtendedGuid(), QStringLiteral("ObjectExtendedGUID"), stp, item);

  appendCompactU64(
      obj->getPartitionId(), QStringLiteral("PartitionID"), stp, item);
  appendCompactU64(obj->getDataSize(), QStringLiteral("DataSize"), stp, item);
  appendCompactU64(
      obj->getObjectReferencesCount(), QStringLiteral("ObjectReferencesCount"),
      stp, item);
  appendCompactU64(
      obj->getCellReferencesCount(), QStringLiteral("CellReferencesCount"), stp,
      item);


  return item;
}

DocumentItem* DocumentModelFactory::appendObjectGroupObjectExcludedData(
    const libmson::fsshttpb::ObjectGroupObjectExcludedData_SPtr_t& obj,
    quint64& stp, DocumentItem* parent)
{

  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("ObjectGroupObjectExcludedData"),
      QStringLiteral("StreamObject"), QString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);

  appendCompactExtGuidArray(
      obj->getExtendedGuidArray(), QStringLiteral("ObjectExtendedGuidArray"),
      stp, item);
  appendCellIdArray(
      obj->getCellIdArray(), QStringLiteral("CellIDArray"), stp, item);


  auto size = obj->getDataSize();
  appendCompactU64(size, QStringLiteral("DataSize"), stp, item);
  //  if (size >= 0) {
  //    appendNewChild(
  //        QStringLiteral("Data"), QStringLiteral("ByteArray"),
  //        obj->getData().toHex(), stp, size, item);
  //    stp += size;
  //  }

  return item;
}

DocumentItem* DocumentModelFactory::appendDataElement(
    const libmson::fsshttpb::DataElement_SPtr_t& obj, quint64& stp,
    DocumentItem* parent)
{
  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("DataElement"), QStringLiteral("StreamObject"),
      obj->dataElementTypeToString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);

  appendCompactExtGuid(
      obj->getDataElementExtGuid(), QStringLiteral("DataElementExtendedGUID"),
      stp, item);

  appendLongExtGuid(
      obj->getSerialNumber(), QStringLiteral("Serial Number"), stp, item);

  appendCompactU64(
      obj->getDataElementType(), QStringLiteral("DataElementType"), stp, item);


  return item;
}

DocumentItem* DocumentModelFactory::appendDataElementHash(
    const libmson::fsshttpb::DataElementHash_SPtr_t& obj, quint64& stp,
    DocumentItem* parent)
{
  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("DataElementHash"), QStringLiteral("StreamObject"),
      QString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);


  appendCompactU64(obj->getScheme(), QStringLiteral("Hash Scheme"), stp, item);


  appendCompactU64(
      obj->getData().size(), QStringLiteral("Hash Data Size"), stp, item);
  appendNewChild(
      QStringLiteral("Hash Data"), QStringLiteral("ByteArray"),
      obj->getData().toHex(), stp, obj->getData().size(), item);
  stp += obj->getData().size();

  return item;
}

DocumentItem* DocumentModelFactory::appendDataElementFragment(
    const libmson::fsshttpb::DataElementFragment_SPtr_t& obj, quint64& stp,
    DocumentItem* parent)
{
  auto cb = obj->getSizeInFile();

  auto* item = appendNewChild(
      QStringLiteral("DataElementFragment"), QStringLiteral("StreamObject"),
      QString(), stp, cb, parent);

  appendStreamObjectHeader(obj->getType(), obj->getCbNextHeader(), stp, item);

  appendCompactExtGuid(
      obj->getExtendedGuid(), QStringLiteral("Fragment Extended GUID"), stp,
      item);
  appendCompactU64(
      obj->getSize(), QStringLiteral("Fragment Data Element Size"), stp, item);
  appendCompactU64(
      obj->getFileChunkStart(), QStringLiteral("FileChunkStart"), stp, item);
  appendCompactU64(
      obj->getFileChunkSize(), QStringLiteral("FileChunkSizee"), stp, item);

  appendNewChild(
      QStringLiteral("Data"), QStringLiteral("ByteArray"),
      obj->getData().toHex(), stp, obj->getData().size(), item);
  stp += obj->getData().size();

  return item;
}

DocumentItem* DocumentModelFactory::appendStreamObjectHeader(
    libmson::fsshttpb::StreamObjectType type, quint64 cbNextHeader,
    quint64& stp, DocumentItem* parent)
{

  auto headerSize =
      libmson::fsshttpb::StreamObjectHeader::getSizeInFile(cbNextHeader, type);

  auto streamObjectType = libmson::fsshttpb::streamObjectTypeToString(type);

  auto* headerItem = appendNewChild(
      QStringLiteral("StreamObjectHeader"), QString(), streamObjectType, stp,
      headerSize, parent);


  if (headerSize == 2) {
    appendNewChild(
        QStringLiteral("HeaderType"), QStringLiteral("2bit"),
        QStringLiteral("16 bit Header"), stp, 1, headerItem);
  }
  else {
    appendNewChild(
        QStringLiteral("HeaderType"), QStringLiteral("2bit"),
        QStringLiteral("32 bit Header"), stp, 1, headerItem);
  }


  appendNewChild(
      QStringLiteral("isCompound"), QStringLiteral("1 bit"),
      libmson::fsshttpb::compoundType.at(type) ? QStringLiteral("True")
                                               : QStringLiteral("False"),
      stp, 1, headerItem);

  if (headerSize == 2) {
    appendNewChild(
        QStringLiteral("StreamObjectType"), QStringLiteral("6 bits"),
        streamObjectType, stp, 2, headerItem);
  }
  else {
    appendNewChild(
        QStringLiteral("StreamObjectType"), QStringLiteral("14 bits"),
        streamObjectType, stp, 2, headerItem);
  }

  if (headerSize == 2) {
    appendNewChild(
        QStringLiteral("Length"), QStringLiteral("uint7_t"),
        "0x" + QString::number(cbNextHeader, 16), stp + 1, 1, headerItem);
    stp += 2;
    return headerItem;
  }
  else if (headerSize == 4) {
    appendNewChild(
        QStringLiteral("Length"), QStringLiteral("uint15_t"),
        "0x" + QString::number(cbNextHeader, 16), stp + 2, 2, headerItem);
    stp += 4;
    return headerItem;
  }

  // LargeLength
  appendNewChild(
      QStringLiteral("Large Length switch"), QString(), QString(), stp + 2, 2,
      headerItem);
  stp += 4;

  appendCompactU64(cbNextHeader, QStringLiteral("Length"), stp, headerItem);

  return headerItem;
}

DocumentItem* DocumentModelFactory::appendStreamObjectHeaderEnd(
    libmson::fsshttpb::StreamObjectType type, quint64& stp,
    DocumentItem* parent)
{

  auto streamObjectType = libmson::fsshttpb::streamObjectTypeToString(type);
  auto headerSize =
      libmson::fsshttpb::StreamObjectHeaderEnd::getSizeInFile(type);


  auto* headerItem = appendNewChild(
      QStringLiteral("StreamObjectHeaderEnd"), QString(), streamObjectType, stp,
      headerSize, parent);


  if (headerSize == 1) {
    appendNewChild(
        QStringLiteral("HeaderType"), QStringLiteral("2bit"),
        QStringLiteral("8 bit End"), stp, 1, headerItem);
    appendNewChild(
        QStringLiteral("StreamObjectType"), QStringLiteral("6 bits"),
        streamObjectType, stp, 1, headerItem);

    stp += 1;
  }
  else {
    appendNewChild(
        QStringLiteral("HeaderType"), QStringLiteral("2bit"),
        QStringLiteral("16 bit End"), stp, 1, headerItem);
    appendNewChild(
        QStringLiteral("StreamObjectType"), QStringLiteral("14 bits"),
        streamObjectType, stp, 2, headerItem);

    stp += 2;
  }

  return headerItem;
}


DocumentItem* DocumentModelFactory::appendCompactU64(
    const quint64 val, const QString& name, quint64& stp, DocumentItem* parent,
    const bool asHex)
{
  const quint64 cb = libmson::fsshttpb::CompactUInt64::getSizeInFile(val);

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("CompactUInt64"),
      QString((asHex ? "0x" : "") + QString::number(val, asHex ? 16 : 10)), stp,
      cb, parent);
  stp += cb;
  return item;
}

DocumentItem* DocumentModelFactory::appendCompactExtGuid(
    const libmson::priv::ExtendedGUID& eguid, const QString& name, quint64& stp,
    DocumentItem* parent)
{
  auto ceg = libmson::fsshttpb::CompactExtGuid(eguid);

  const quint64 cb = ceg.getSizeInFile();

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("CompactExtGuid"), eguid.toString(), stp, cb,
      parent);

  appendNewChild(
      QStringLiteral("type"), QStringLiteral("CompactExtGuidWidth"),
      libmson::fsshttpb::CompactExtGuid::typeToString(ceg.getWidthType()), stp,
      1, item);


  switch (ceg.getWidthType()) {
  case libmson::fsshttpb::CompactExtGuidWidth::CompressedNull:
    appendNewChild(
        QStringLiteral("Guid"), QString(), eguid.toString(), stp, 1, item);
    stp += 1;
    return item;
  case libmson::fsshttpb::CompactExtGuidWidth::CompressedN5Bit:
    appendNewChild(
        QStringLiteral("value"), QStringLiteral("uint5_t"),
        QString::number(ceg.getN()), stp, 1, item);
    stp += 1;
    break;
  case libmson::fsshttpb::CompactExtGuidWidth::CompressedN10Bit:
    appendNewChild(
        QStringLiteral("value"), QStringLiteral("uint10_t"),
        QString::number(ceg.getN()), stp, 2, item);
    stp += 2;
    break;
  case libmson::fsshttpb::CompactExtGuidWidth::CompressedN17Bit:
    appendNewChild(
        QStringLiteral("value"), QStringLiteral("uint17_t"),
        QString::number(ceg.getN()), stp, 3, item);
    stp += 3;
    break;
  case libmson::fsshttpb::CompactExtGuidWidth::Uncompressed:
    stp += 1;
    appendUInt32(ceg.getN(), QStringLiteral("value"), stp, item, false);
    break;
  case libmson::fsshttpb::CompactExtGuidWidth::Auto:
    break;
  }

  appendGuid(eguid.getGuid(), QStringLiteral("Guid"), stp, item);

  return item;
}

DocumentItem* DocumentModelFactory::appendCompactExtGuidArray(
    const std::vector<libmson::priv::ExtendedGUID>& eguids, const QString& name,
    quint64& stp, DocumentItem* parent)
{
  auto cb = libmson::fsshttpb::CompactExtGuidArray::getSizeInFile(eguids);

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("CompactExtGuidArray"),
      QString::number(eguids.size()) + " eguids", stp, cb, parent);


  appendCompactU64(eguids.size(), QStringLiteral("Size"), stp, item, false);

  for (const auto& eg : eguids) {
    appendCompactExtGuid(eg, QString(), stp, item);
  }

  return item;
}

DocumentItem* DocumentModelFactory::appendLongExtGuid(
    const libmson::fsshttpb::LongExtGuid& sn, const QString& name, quint64& stp,
    DocumentItem* parent)
{
  const quint64 cb = sn.getSizeInFile();

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("SerialNumber"), sn.toString(), stp, cb, parent);

  appendNewChild(
      QStringLiteral("type"), cb == 1 ? "NullWidth" : "FullWidth", QString(),
      stp, 1, item);
  stp += 1;
  appendGuid(sn.getGuid(), QStringLiteral("Guid"), stp, item);
  appendUInt64(sn.getSerialNumber(), QStringLiteral("Value"), stp, item, false);

  return item;
}

DocumentItem* DocumentModelFactory::appendCellId(
    const libmson::fsshttpb::CellId& cellId, const QString& name, quint64& stp,
    DocumentItem* parent)
{
  const quint64 cb = cellId.getSizeInFile();

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("CellId"), QString(), stp, cb, parent);

  appendCompactExtGuid(
      cellId.getExguid1(), QStringLiteral("ExtGuid1"), stp, item);
  appendCompactExtGuid(
      cellId.getExguid2(), QStringLiteral("ExtGuid2"), stp, item);

  return item;
}

DocumentItem* DocumentModelFactory::appendCellIdArray(
    const std::vector<libmson::fsshttpb::CellId>& cellIds, const QString& name,
    quint64& stp, DocumentItem* parent)
{
  auto cb = libmson::fsshttpb::CellIdArray::getSizeInFile(cellIds);

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("CompactExtGuidArray"),
      QString::number(cellIds.size()) + " cellIds", stp, cb, parent);

  appendCompactU64(cellIds.size(), QStringLiteral("Size"), stp, item, false);

  for (const auto& id : cellIds) {
    appendCellId(id, QString(), stp, item);
  }

  return item;
}


DocumentItem* DocumentModelFactory::appendUInt8(
    const quint8 val, const QString& name, quint64& stp, DocumentItem* parent,
    const bool asHex)
{
  const quint64 cb = sizeof(quint8);

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("uint8_t"),
      QString((asHex ? "0x" : "") + QString::number(val, asHex ? 16 : 10)), stp,
      cb, parent);
  stp += cb;
  return item;
}

DocumentItem* DocumentModelFactory::appendUInt16(
    const quint16 val, const QString& name, quint64& stp, DocumentItem* parent,
    const bool asHex)
{
  const quint64 cb = sizeof(quint16);

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("uint16_t"),
      QString((asHex ? "0x" : "") + QString::number(val, asHex ? 16 : 10)), stp,
      cb, parent);
  stp += cb;
  return item;
}

DocumentItem* DocumentModelFactory::appendUInt32(
    const quint32 val, const QString& name, quint64& stp, DocumentItem* parent,
    const bool asHex)
{
  const quint64 cb = sizeof(quint32);

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("uint32_t"),
      QString((asHex ? "0x" : "") + QString::number(val, asHex ? 16 : 10)), stp,
      cb, parent);
  stp += cb;
  return item;
}

DocumentItem* DocumentModelFactory::appendUInt64(
    const quint64 val, const QString& name, quint64& stp, DocumentItem* parent,
    const bool asHex)
{
  const quint64 cb = sizeof(quint64);

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("uint64_t"),
      QString((asHex ? "0x" : "") + QString::number(val, asHex ? 16 : 10)), stp,
      cb, parent);
  stp += cb;
  return item;
}

DocumentItem* DocumentModelFactory::appendInt8(
    const qint8 val, const QString& name, quint64& stp, DocumentItem* parent,
    const bool asHex)
{
  const quint64 cb = sizeof(qint8);

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("int8_t"),
      QString((asHex ? "0x" : "") + QString::number(val, asHex ? 16 : 10)), stp,
      cb, parent);
  stp += cb;
  return item;
}

DocumentItem* DocumentModelFactory::appendInt16(
    const qint16 val, const QString& name, quint64& stp, DocumentItem* parent,
    const bool asHex)
{
  const quint64 cb = sizeof(qint16);

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("int16_t"),
      QString(asHex ? "0x" : "" + QString::number(val, asHex ? 16 : 10)), stp,
      cb, parent);
  stp += cb;
  return item;
}

DocumentItem* DocumentModelFactory::appendInt32(
    const qint32 val, const QString& name, quint64& stp, DocumentItem* parent,
    const bool asHex)
{
  const quint64 cb = sizeof(qint32);

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("uint32_t"),
      QString((asHex ? "0x" : "") + QString::number(val, asHex ? 16 : 10)), stp,
      cb, parent);
  stp += cb;
  return item;
}

DocumentItem* DocumentModelFactory::appendInt64(
    const qint64 val, const QString& name, quint64& stp, DocumentItem* parent,
    const bool asHex)
{
  const quint64 cb = sizeof(qint64);

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("uint64_t"),
      QString((asHex ? "0x" : "") + QString::number(val, asHex ? 16 : 10)), stp,
      cb, parent);
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

DocumentItem* DocumentModelFactory::appendCompactID(
    const libmson::priv::CompactID& cid, const QString& name, quint64& stp,
    DocumentItem* parent)
{
  const quint64 cb{libmson::priv::CompactID::getSizeInFile()};

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("CompactId"), cid.toString(), stp, cb, parent);

  appendNewChild(
      QStringLiteral("n"), QStringLiteral("uint8_t"), cid.getN(), stp, 1, item);
  stp += 1;

  appendNewChild(
      QStringLiteral("GuidIndex"), QStringLiteral("uint24_t"),
      cid.getGuidIndex(), stp, 3, item);
  stp += 3;


  return item;
}

DocumentItem* DocumentModelFactory::appendObjectInfoDependencyOverrideData(
    const libmson::priv::ObjectInfoDependencyOverrideData& objInfo,
    const QString& name, quint64& stp, DocumentItem* parent)
{
  const quint64 cb{objInfo.getSizeInFile()};

  auto* chunkItem = appendNewChild(
      name, QStringLiteral("ObjectInfoDependencyOverrideData"), QString(), stp,
      cb, parent);


  appendUInt32(
      objInfo.getC8BitOverrides(), QStringLiteral("c8BitOverrides"), stp,
      chunkItem, false);
  appendUInt32(
      objInfo.getC32BitOverrides(), QStringLiteral("c32BitOverrides"), stp,
      chunkItem, false);
  appendUInt32(objInfo.getCrc(), QStringLiteral("crc"), stp, chunkItem);

  auto* overrides1 = appendNewChild(
      QStringLiteral("Overrides1"), QString(),
      QString::number(objInfo.getC8BitOverrides()), stp,
      libmson::priv::ObjectInfoDependencyOverride8::getSizeInFile() *
          objInfo.getC8BitOverrides(),
      chunkItem);

  for (auto&& item : objInfo.getOverrides1()) {
    appendObjectInfoDependencyOverride8(
        item, QStringLiteral("8BitOverride"), stp, overrides1);
  }


  auto* overrides2 = appendNewChild(
      QStringLiteral("Overrides2"), QString(),
      QString::number(objInfo.getC32BitOverrides()), stp,
      libmson::priv::ObjectInfoDependencyOverride32::getSizeInFile() *
          objInfo.getC32BitOverrides(),
      chunkItem);

  for (auto&& item : objInfo.getOverrides2()) {
    appendObjectInfoDependencyOverride32(
        item, QStringLiteral("32BitOverride"), stp, overrides2);
  }

  return chunkItem;
}

DocumentItem* DocumentModelFactory::appendObjectInfoDependencyOverride8(
    const libmson::priv::ObjectInfoDependencyOverride8& objInfo,
    const QString& name, quint64& stp, DocumentItem* parent)
{
  const quint64 cb{
      libmson::priv::ObjectInfoDependencyOverride8::getSizeInFile()};

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("ObjectInfoDependencyOverride8"), QString(), stp, cb,
      parent);

  appendCompactID(objInfo.getOid(), QStringLiteral("oid"), stp, item);
  appendUInt8(objInfo.getCRef(), QStringLiteral("cRef"), stp, item);

  return item;
}
DocumentItem* DocumentModelFactory::appendObjectInfoDependencyOverride32(
    const libmson::priv::ObjectInfoDependencyOverride32& objInfo,
    const QString& name, quint64& stp, DocumentItem* parent)
{
  const quint64 cb{
      libmson::priv::ObjectInfoDependencyOverride32::getSizeInFile()};

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("ObjectInfoDependencyOverride32"), QString(), stp,
      cb, parent);

  appendCompactID(objInfo.getOid(), QStringLiteral("oid"), stp, item);
  appendUInt32(objInfo.getCRef(), QStringLiteral("cRef"), stp, item);

  return item;
}


DocumentItem* DocumentModelFactory::appendJCID(
    const libmson::priv::JCID& jcid, const QString& name, quint64& stp,
    DocumentItem* parent)
{
  const quint64 cb{libmson::priv::JCID::getSizeInFile()};

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("JCID"), jcid.typeToString(), stp, cb, parent);

  appendUInt16(jcid.index(), QStringLiteral("Index"), stp, item);

  const QString falseStr = QStringLiteral("false");
  const QString trueStr  = QStringLiteral("true");

  appendNewChild(
      QStringLiteral("isBinary"), QStringLiteral("1 bit"),
      jcid.IsBinary() ? trueStr : falseStr, stp, 1, item);

  appendNewChild(
      QStringLiteral("isPropertySet"), QStringLiteral("1 bit"),
      jcid.IsPropertySet() ? trueStr : falseStr, stp, 1, item);

  appendNewChild(
      QStringLiteral("isGraphNode"), QStringLiteral("1 bit"),
      jcid.IsGraphNode() ? trueStr : falseStr, stp, 1, item);

  appendNewChild(
      QStringLiteral("isFileData"), QStringLiteral("1 bit"),
      jcid.IsFileData() ? trueStr : falseStr, stp, 1, item);

  appendNewChild(
      QStringLiteral("isReadOnly"), QStringLiteral("1 bit"),
      jcid.IsReadOnly() ? trueStr : falseStr, stp, 1, item);

  stp += 2;

  return item;
}

DocumentItem* DocumentModelFactory::appendStringInStorageBuffer(
    const libmson::priv::StringInStorageBuffer& buffer, const QString& name,
    quint64& stp, DocumentItem* parent)
{
  const quint64 cb{buffer.getSizeInFile()};

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("StringInStorageBuffer"), buffer.getStringData(),
      stp, cb, parent);

  appendUInt32(buffer.getCch(), QStringLiteral("cCh"), stp, item, false);


  appendNewChild(
      QStringLiteral("RawString"), QStringLiteral("char array"),
      buffer.getStringData(), stp, buffer.getCch() * 2, item);

  stp += buffer.getCch() * 2;

  return item;
}

DocumentItem* DocumentModelFactory::appendObjectDeclarationWithRefCountBody(
    const libmson::priv::ObjectDeclarationWithRefCountBody& declBody,
    const QString& name, quint64& stp, DocumentItem* parent)
{
  const quint64 cb{
      libmson::priv::ObjectDeclarationWithRefCountBody::getSizeInFile()};

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("ObjectDeclarationWithRefCountBody"), QString(), stp,
      cb, parent);


  appendCompactID(declBody.getOid(), QStringLiteral("oid"), stp, item);

  appendNewChild(
      QStringLiteral("jci"), QStringLiteral("10 bit"), declBody.getJci(), stp,
      2, item);
  appendNewChild(
      QStringLiteral("odcs"), QStringLiteral("4 bit"), declBody.getOdc(), stp,
      2, item);
  stp += 2;

  appendNewChild(
      QStringLiteral("fHasOidReferences"), QStringLiteral("1bit"),
      declBody.getFHasOidReferences() ? QStringLiteral("true")
                                      : QStringLiteral("false"),
      stp, 4, item);

  appendNewChild(
      QStringLiteral("fHasOsidReferences"), QStringLiteral("1bit"),
      declBody.getFHasOsidReferences() ? QStringLiteral("true")
                                       : QStringLiteral("false"),
      stp, 4, item);

  stp += 4;

  return item;
}

DocumentItem* DocumentModelFactory::appendObjectDeclaration2Body(
    const libmson::priv::ObjectDeclaration2Body& declBody, const QString& name,
    quint64& stp, DocumentItem* parent)
{
  const quint64 cb{libmson::priv::ObjectDeclaration2Body::getSizeInFile()};

  DocumentItem* item = appendNewChild(
      name, QStringLiteral("ObjectDeclaration2Body"), QString(), stp, cb,
      parent);


  appendCompactID(declBody.getOid(), QStringLiteral("oid"), stp, item);

  appendJCID(declBody.getJcid(), QStringLiteral("jcid"), stp, item);


  appendNewChild(
      QStringLiteral("fHasOidReferences"), QStringLiteral("1bit"),
      declBody.getFHasOidReferences() ? QStringLiteral("true")
                                      : QStringLiteral("false"),
      stp, 1, item);

  appendNewChild(
      QStringLiteral("fHasOsidReferences"), QStringLiteral("1bit"),
      declBody.getFHasOsidReferences() ? QStringLiteral("true")
                                       : QStringLiteral("false"),
      stp, 1, item);

  stp += 1;

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
      QString("0x" + QString::number(ref.stp(), 16)), stp, sizeof(quint32),
      item);
  appendNewChild(
      QStringLiteral("Cb"), QStringLiteral("uint32_t"),
      QString("0x" + QString::number(ref.cb(), 16)), stp + sizeof(quint32),
      sizeof(quint32), item);

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
      QString("0x" + QString::number(ref.stp(), 16)), stp, sizeof(quint64),
      item);

  appendNewChild(
      QStringLiteral("Cb"), QStringLiteral("uint32_t"),
      QString("0x" + QString::number(ref.cb(), 16)), stp + sizeof(quint64),
      sizeof(quint32), item);

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
      QString("0x" + QString::number(ref.stp(), 16)), stp, sizeof(quint64),
      item);
  appendNewChild(
      QStringLiteral("Cb"), QStringLiteral("uint64_t"),
      QString("0x" + QString::number(ref.cb(), 16)), stp + sizeof(quint64),
      sizeof(quint64), item);

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


  quint8 stpSize = 0;
  switch (ref.getStpFormat()) {
  case libmson::priv::FNCR_STP_FORMAT::UNCOMPRESED_8BYTE:
    stpSize = 8;
    break;
  case libmson::priv::FNCR_STP_FORMAT::UNCOMPRESED_4BYTE:
  case libmson::priv::FNCR_STP_FORMAT::COMPRESSED_4BYTE:
    stpSize = 4;
    break;
  case libmson::priv::FNCR_STP_FORMAT::COMPRESSED_2BYTE:
    stpSize = 2;
    break;
  }

  quint8 cbSize = 0;
  switch (ref.getCbFormat()) {
  case libmson::priv::FNCR_CB_FORMAT::UNCOMPRESED_8BYTE:
    cbSize = 8;
    break;
  case libmson::priv::FNCR_CB_FORMAT::UNCOMPRESED_4BYTE:
    cbSize = 4;
    break;
  case libmson::priv::FNCR_CB_FORMAT::COMPRESSED_2BYTE:
    cbSize = 2;
    break;
  case libmson::priv::FNCR_CB_FORMAT::COMPRESSED_1BYTE:
    cbSize = 1;
    break;
  }

  appendNewChild(
      QStringLiteral("Stp"),
      libmson::priv::FileNodeChunkReference::fncrStpFormatString(
          ref.getStpFormat()),
      QString("0x" + QString::number(ref.stp(), 16)), stp, stpSize, item);
  appendNewChild(
      QStringLiteral("Cb"),
      libmson::priv::FileNodeChunkReference::fncrCbFormatString(
          ref.getCbFormat()),
      QString("0x" + QString::number(ref.cb(), 16)), stp + stpSize, cbSize,
      item);

  stp += cb;

  return item;
}
