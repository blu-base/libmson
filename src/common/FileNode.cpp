#include "FileNode.h"

#include <QDataStream>
#include <QDebug>
#include <QtEndian>

#include <bitset>

#include "FileNodeTypes/ChunkTerminatorFND.h"
#include "FileNodeTypes/DataSignatureGroupDefinitionFND.h"
#include "FileNodeTypes/FileDataStoreListReferenceFND.h"
#include "FileNodeTypes/FileDataStoreObjectReferenceFND.h"
#include "FileNodeTypes/GlobalIdTableEndFNDX.h"
#include "FileNodeTypes/GlobalIdTableEntry2FNDX.h"
#include "FileNodeTypes/GlobalIdTableEntry3FNDX.h"
#include "FileNodeTypes/GlobalIdTableEntryFNDX.h"
#include "FileNodeTypes/GlobalIdTableStart2FND.h"
#include "FileNodeTypes/GlobalIdTableStartFNDX.h"
#include "FileNodeTypes/HashedChunkDescriptor2FND.h"
#include "FileNodeTypes/ObjectDataEncryptionKeyV2FNDX.h"
#include "FileNodeTypes/ObjectDeclaration2LargeRefCountFND.h"
#include "FileNodeTypes/ObjectDeclaration2RefCountFND.h"
#include "FileNodeTypes/ObjectDeclarationFileData3LargeRefCountFND.h"
#include "FileNodeTypes/ObjectDeclarationFileData3RefCountFND.h"
#include "FileNodeTypes/ObjectDeclarationWithRefCount2FNDX.h"
#include "FileNodeTypes/ObjectDeclarationWithRefCountFNDX.h"
#include "FileNodeTypes/ObjectGroupEndFND.h"
#include "FileNodeTypes/ObjectGroupListReferenceFND.h"
#include "FileNodeTypes/ObjectGroupStartFND.h"
#include "FileNodeTypes/ObjectInfoDependencyOverridesFND.h"
#include "FileNodeTypes/ObjectRevisionWithRefCount2FNDX.h"
#include "FileNodeTypes/ObjectRevisionWithRefCountFNDX.h"
#include "FileNodeTypes/ObjectSpaceManifestListReferenceFND.h"
#include "FileNodeTypes/ObjectSpaceManifestListStartFND.h"
#include "FileNodeTypes/ObjectSpaceManifestRootFND.h"
#include "FileNodeTypes/ReadOnlyObjectDeclaration2LargeRefCountFND.h"
#include "FileNodeTypes/ReadOnlyObjectDeclaration2RefCountFND.h"
#include "FileNodeTypes/RevisionManifestEndFND.h"
#include "FileNodeTypes/RevisionManifestListReferenceFND.h"
#include "FileNodeTypes/RevisionManifestListStartFND.h"
#include "FileNodeTypes/RevisionManifestStart4FND.h"
#include "FileNodeTypes/RevisionManifestStart6FND.h"
#include "FileNodeTypes/RevisionManifestStart7FND.h"
#include "FileNodeTypes/RevisionRoleAndContextDeclarationFND.h"
#include "FileNodeTypes/RevisionRoleDeclarationFND.h"
#include "FileNodeTypes/RootObjectReference2FNDX.h"
#include "FileNodeTypes/RootObjectReference3FND.h"

#include "helper/Helper.h"

namespace MSONcommon {

std::shared_ptr<IFileNodeType> FileNode::getFnt() const { return fnt; }

FileNode::FileNode()
    : stp{}, fileNodeID{}, fileNodeSize{4}, stpFormat{}, cbFormat{}, baseType{},
      reserved{}, fnt{nullptr} {}

FileNode::FileNode(const FileNode &source)
    : stp{source.stp}, fileNodeID{source.fileNodeID},
      fileNodeSize{source.fileNodeSize}, stpFormat{source.stpFormat},
      cbFormat{source.cbFormat}, baseType{source.baseType}, reserved{},
      fnt{source.fnt} {}

FileNode::~FileNode() {}

void FileNode::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("FileNode");

  xmlWriter.writeAttribute("stp", qStringHex(getStp(), 16));

  xmlWriter.writeAttribute("fileNodeID", qStringHex(fileNodeID, 3));
  xmlWriter.writeAttribute("fileNodeSize", qStringHex(fileNodeSize, 4));
  xmlWriter.writeAttribute("stpFormat", QString::number(stpFormat));
  xmlWriter.writeAttribute("cbFormat", QString::number(cbFormat));
  xmlWriter.writeAttribute("baseType", qStringHex(baseType, 2));

  if (fnt != nullptr) {
    xmlWriter << *fnt;
  } else {
    xmlWriter.writeStartElement("NoFileNodeType");
    xmlWriter.writeEndElement();
  }

  xmlWriter.writeEndElement();
}

void MSONcommon::FileNode::serialize(QDataStream &ds) const {}

void MSONcommon::FileNode::deserialize(QDataStream &ds) {

  //  if (!ds.byteOrder()) {
  //    ds.setByteOrder(QDataStream::LittleEndian);
  //  }
  ds.setByteOrder(QDataStream::LittleEndian);
  stp = ds.device()->pos();
  //  qDebug() << "FileNode stp: "<< qStringHex(stp, 16);
  quint32 temp;
  ds >> temp;

  reserved = (temp >> FileNode_shiftReserved) & FileNode_maskReserved;
  baseType = (temp >> FileNode_shiftBaseType) & FileNode_maskBaseType;
  cbFormat = (temp >> FileNode_shiftCbFormat) & FileNode_maskCbFormat;
  stpFormat = (temp >> FileNode_shiftStpFormat) & FileNode_maskStpFormat;
  fileNodeSize =
      (temp >> FileNode_shiftFileNodeSize) & FileNode_maskFileNodeSize;
  fileNodeID = (temp >> FileNode_shiftFileNodeID) & FileNode_maskFileNodeID;

  switch (static_cast<FileNodeTypeID>(fileNodeID)) {
  case FileNodeTypeID::ChunkTerminatorFND:
    fnt = std::make_shared<ChunkTerminatorFND>();
    break;
  case FileNodeTypeID::DataSignatureGroupDefinitionFND:
    fnt = std::make_shared<DataSignatureGroupDefinitionFND>();
    break;
  case FileNodeTypeID::FileDataStoreListReferenceFND:
    fnt = std::make_shared<FileDataStoreListReferenceFND>(stpFormat, cbFormat);
    break;
  case FileNodeTypeID::FileDataStoreObjectReferenceFND:
    fnt =
        std::make_shared<FileDataStoreObjectReferenceFND>(stpFormat, cbFormat);
    break;
  case FileNodeTypeID::GlobalIdTableEndFNDX:
    fnt = std::make_shared<GlobalIdTableEndFNDX>();
    break;
  case FileNodeTypeID::GlobalIdTableEntry2FNDX:
    fnt = std::make_shared<GlobalIdTableEntry2FNDX>();
    break;
  case FileNodeTypeID::GlobalIdTableEntry3FNDX:
    fnt = std::make_shared<GlobalIdTableEntry3FNDX>();
    break;
  case FileNodeTypeID::GlobalIdTableEntryFNDX:
    fnt = std::make_shared<GlobalIdTableEntryFNDX>();
    break;
  case FileNodeTypeID::GlobalIdTableStart2FND:
    fnt = std::make_shared<GlobalIdTableStart2FND>();
    break;
  case FileNodeTypeID::GlobalIdTableStartFNDX:
    fnt = std::make_shared<GlobalIdTableStartFNDX>();
    break;
  case FileNodeTypeID::HashedChunkDescriptor2FND:
    fnt = std::make_shared<HashedChunkDescriptor2FND>(stpFormat, cbFormat);
    break;
  case FileNodeTypeID::ObjectDataEncryptionKeyV2FNDX:
    fnt = std::make_shared<ObjectDataEncryptionKeyV2FNDX>(stpFormat, cbFormat);
    break;
  case FileNodeTypeID::ObjectDeclaration2LargeRefCountFND:
    fnt = std::make_shared<ObjectDeclaration2LargeRefCountFND>(stpFormat,
                                                               cbFormat);
    break;
  case FileNodeTypeID::ObjectDeclaration2RefCountFND:
    fnt = std::make_shared<ObjectDeclaration2RefCountFND>(stpFormat, cbFormat);
    break;
  case FileNodeTypeID::ObjectDeclarationFileData3LargeRefCountFND:
    fnt = std::make_shared<ObjectDeclarationFileData3LargeRefCountFND>();
    break;
  case FileNodeTypeID::ObjectDeclarationFileData3RefCountFND:
    fnt = std::make_shared<ObjectDeclarationFileData3RefCountFND>();
    break;
  case FileNodeTypeID::ObjectDeclarationWithRefCount2FNDX:
    fnt = std::make_shared<ObjectDeclarationWithRefCount2FNDX>(stpFormat,
                                                               cbFormat);
    break;
  case FileNodeTypeID::ObjectDeclarationWithRefCountFNDX:
    fnt = std::make_shared<ObjectDeclarationWithRefCountFNDX>(stpFormat,
                                                              cbFormat);
    break;
  case FileNodeTypeID::ObjectGroupEndFND:
    fnt = std::make_shared<ObjectGroupEndFND>();
    break;
  case FileNodeTypeID::ObjectGroupListReferenceFND:
    fnt = std::make_shared<ObjectGroupListReferenceFND>(stpFormat, cbFormat);
    break;
  case FileNodeTypeID::ObjectGroupStartFND:
    fnt = std::make_shared<ObjectGroupStartFND>();
    break;
  case FileNodeTypeID::ObjectInfoDependencyOverridesFND:
    fnt =
        std::make_shared<ObjectInfoDependencyOverridesFND>(stpFormat, cbFormat);
    break;
  case FileNodeTypeID::ObjectRevisionWithRefCount2FNDX:
    fnt =
        std::make_shared<ObjectRevisionWithRefCount2FNDX>(stpFormat, cbFormat);
    break;
  case FileNodeTypeID::ObjectRevisionWithRefCountFNDX:
    fnt = std::make_shared<ObjectRevisionWithRefCountFNDX>(stpFormat, cbFormat);
    break;
  case FileNodeTypeID::ObjectSpaceManifestListReferenceFND:
    fnt = std::make_shared<ObjectSpaceManifestListReferenceFND>(stpFormat,
                                                                cbFormat);
    break;
  case FileNodeTypeID::ObjectSpaceManifestListStartFND:
    fnt = std::make_shared<ObjectSpaceManifestListStartFND>();
    break;
  case FileNodeTypeID::ObjectSpaceManifestRootFND:
    fnt = std::make_shared<ObjectSpaceManifestRootFND>();
    break;
  case FileNodeTypeID::ReadOnlyObjectDeclaration2LargeRefCountFND:
    fnt = std::make_shared<ReadOnlyObjectDeclaration2LargeRefCountFND>(
        stpFormat, cbFormat);
    break;
  case FileNodeTypeID::ReadOnlyObjectDeclaration2RefCountFND:
    fnt = std::make_shared<ReadOnlyObjectDeclaration2RefCountFND>(stpFormat,
                                                                  cbFormat);
    break;
  case FileNodeTypeID::RevisionManifestEndFND:
    fnt = std::make_shared<RevisionManifestEndFND>();
    break;
  case FileNodeTypeID::RevisionManifestListReferenceFND:
    fnt =
        std::make_shared<RevisionManifestListReferenceFND>(stpFormat, cbFormat);
    break;
  case FileNodeTypeID::RevisionManifestListStartFND:
    fnt = std::make_shared<RevisionManifestListStartFND>();
    break;
  case FileNodeTypeID::RevisionManifestStart4FND:
    fnt = std::make_shared<RevisionManifestStart4FND>();
    break;
  case FileNodeTypeID::RevisionManifestStart6FND:
    fnt = std::make_shared<RevisionManifestStart6FND>();
    break;
  case FileNodeTypeID::RevisionManifestStart7FND:
    fnt = std::make_shared<RevisionManifestStart7FND>();
    break;
  case FileNodeTypeID::RevisionRoleAndContextDeclarationFND:
    fnt = std::make_shared<RevisionRoleAndContextDeclarationFND>();
    break;
  case FileNodeTypeID::RevisionRoleDeclarationFND:
    fnt = std::make_shared<RevisionRoleDeclarationFND>();
    break;
  case FileNodeTypeID::RootObjectReference2FNDX:
    fnt = std::make_shared<RootObjectReference2FNDX>();
    break;
  case FileNodeTypeID::RootObjectReference3FND:
    fnt = std::make_shared<RootObjectReference3FND>();
    break;

  default:
    fnt = nullptr;
    break;
  }

  if (fnt != nullptr) {
    ds >> *fnt;
  }
}

QDebug operator<<(QDebug dbg, const FileNode &obj) {
  QDebugStateSaver saver(dbg);

  dbg.noquote() << "FileNode. ID: " << qStringHex(obj.fileNodeID, 3)
                << " Size: " << qStringHex(obj.fileNodeSize, 4)
                << " Stp/Cb format: " << obj.stpFormat << "/" << obj.cbFormat
                << " BaseType: " << obj.baseType << '\n';

  if (obj.fnt != nullptr) {
    dbg << *obj.fnt;
  } else {
    dbg << "FileNodeType is not declared.\n";
  }

  return dbg;
}

quint16 FileNode::getFileNodeID() const { return fileNodeID; }

void FileNode::setFileNodeID(const quint16 &value) { fileNodeID = value; }

FileNodeTypeID FileNode::getFileNodeTypeID() const {
  return static_cast<FileNodeTypeID>(fileNodeID);
}

quint16 FileNode::getFileNodeSize() const { return fileNodeSize; }

void FileNode::setFileNodeSize(const quint16 &value) { fileNodeSize = value; }

quint8 FileNode::getStpFormat() const { return stpFormat; }

void FileNode::setStpFormat(const quint8 &value) { stpFormat = value; }

quint8 FileNode::getCbFormat() const { return cbFormat; }

void FileNode::setCbFormat(const quint8 &value) { cbFormat = value; }

quint8 FileNode::getBaseType() const { return baseType; }

void FileNode::setBaseType(const quint8 &value) { baseType = value; }

quint64 FileNode::getStp() const { return stp; }

} // namespace MSONcommon
