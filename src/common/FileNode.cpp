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
IFileNodeType *FileNode::getFnt() const { return fnt; }

FileNode::FileNode()
    : fileNodeID{}, fileNodeSize{4}, stpFormat{}, cbFormat{}, baseType{},
      reserved{}, fnt{nullptr} {}

FileNode::FileNode(const FileNode &source)
    : fileNodeID{source.fileNodeID}, fileNodeSize{source.fileNodeSize},
      stpFormat{source.stpFormat}, cbFormat{source.cbFormat},
      baseType{source.baseType}, reserved{}, fnt{source.fnt} {}

FileNode::~FileNode() {}

void FileNode::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("FileNode");

  xmlWriter.writeAttribute("fileNodeID", qStringHex(fileNodeID, 3));
  xmlWriter.writeAttribute("fileNodeSize", qStringHex(fileNodeSize, 4));
  xmlWriter.writeAttribute("stpFormat", QString::number(stpFormat));
  xmlWriter.writeAttribute("cbFormat", QString::number(cbFormat));
  xmlWriter.writeAttribute("baseType", qStringHex(baseType, 2));

  ///\todo IFileNodeType *fnt;
  ///
  xmlWriter.writeStartElement("FileNodeType");
  if (fnt != nullptr) {
    fnt->generateXml(xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();
}

QDataStream &operator>>(QDataStream &ds, FileNode &obj) {
  //  if (!ds.byteOrder()) {
  //    ds.setByteOrder(QDataStream::LittleEndian);
  //  }
  ds.setByteOrder(QDataStream::LittleEndian);
  quint32 temp;
  ds >> temp;

  obj.reserved = (temp >> FileNode_shiftReserved) & FileNode_maskReserved;
  obj.baseType = (temp >> FileNode_shiftBaseType) & FileNode_maskBaseType;
  obj.cbFormat = (temp >> FileNode_shiftCbFormat) & FileNode_maskCbFormat;
  obj.stpFormat = (temp >> FileNode_shiftStpFormat) & FileNode_maskStpFormat;
  obj.fileNodeSize =
      (temp >> FileNode_shiftFileNodeSize) & FileNode_maskFileNodeSize;
  obj.fileNodeID = (temp >> FileNode_shiftFileNodeID) & FileNode_maskFileNodeID;

  switch (static_cast<FileNodeTypeID>(obj.fileNodeID)) {
  case FileNodeTypeID::ChunkTerminatorFND:
    obj.fnt = new ChunkTerminatorFND();
    break;
  case FileNodeTypeID::DataSignatureGroupDefinitionFND:
    obj.fnt = new DataSignatureGroupDefinitionFND();
    break;
  case FileNodeTypeID::FileDataStoreListReferenceFND:
    obj.fnt = new FileDataStoreListReferenceFND(obj.stpFormat, obj.cbFormat);
    break;
  case FileNodeTypeID::FileDataStoreObjectReferenceFND:
    obj.fnt = new FileDataStoreObjectReferenceFND(obj.stpFormat, obj.cbFormat);
    break;
  case FileNodeTypeID::GlobalIdTableEndFNDX:
    obj.fnt = new GlobalIdTableEndFNDX();
    break;
  case FileNodeTypeID::GlobalIdTableEntry2FNDX:
    obj.fnt = new GlobalIdTableEntry2FNDX();
    break;
  case FileNodeTypeID::GlobalIdTableEntry3FNDX:
    obj.fnt = new GlobalIdTableEntry3FNDX();
    break;
  case FileNodeTypeID::GlobalIdTableEntryFNDX:
    obj.fnt = new GlobalIdTableEntryFNDX();
    break;
  case FileNodeTypeID::GlobalIdTableStart2FND:
    obj.fnt = new GlobalIdTableStart2FND();
    break;
  case FileNodeTypeID::GlobalIdTableStartFNDX:
    obj.fnt = new GlobalIdTableStartFNDX();
    break;
  case FileNodeTypeID::HashedChunkDescriptor2FND:
    obj.fnt = new HashedChunkDescriptor2FND(obj.stpFormat, obj.cbFormat);
    break;
  case FileNodeTypeID::ObjectDataEncryptionKeyV2FNDX:
    obj.fnt = new ObjectDataEncryptionKeyV2FNDX(obj.stpFormat, obj.cbFormat);
    break;
  case FileNodeTypeID::ObjectDeclaration2LargeRefCountFND:
    obj.fnt =
        new ObjectDeclaration2LargeRefCountFND(obj.stpFormat, obj.cbFormat);
    break;
  case FileNodeTypeID::ObjectDeclaration2RefCountFND:
    obj.fnt = new ObjectDeclaration2RefCountFND(obj.stpFormat, obj.cbFormat);
    break;
  case FileNodeTypeID::ObjectDeclarationFileData3LargeRefCountFND:
    obj.fnt = new ObjectDeclarationFileData3LargeRefCountFND();
    break;
  case FileNodeTypeID::ObjectDeclarationFileData3RefCountFND:
    obj.fnt = new ObjectDeclarationFileData3RefCountFND();
    break;
  case FileNodeTypeID::ObjectDeclarationWithRefCount2FNDX:
    obj.fnt =
        new ObjectDeclarationWithRefCount2FNDX(obj.stpFormat, obj.cbFormat);
    break;
  case FileNodeTypeID::ObjectDeclarationWithRefCountFNDX:
    obj.fnt =
        new ObjectDeclarationWithRefCountFNDX(obj.stpFormat, obj.cbFormat);
    break;
  case FileNodeTypeID::ObjectGroupEndFND:
    obj.fnt = new ObjectGroupEndFND();
    break;
  case FileNodeTypeID::ObjectGroupListReferenceFND:
    obj.fnt = new ObjectGroupListReferenceFND(obj.stpFormat, obj.cbFormat);
    break;
  case FileNodeTypeID::ObjectGroupStartFND:
    obj.fnt = new ObjectGroupStartFND();
    break;
  case FileNodeTypeID::ObjectInfoDependencyOverridesFND:
    obj.fnt = new ObjectInfoDependencyOverridesFND(obj.stpFormat, obj.cbFormat);
    break;
  case FileNodeTypeID::ObjectRevisionWithRefCount2FNDX:
    obj.fnt = new ObjectRevisionWithRefCount2FNDX(obj.stpFormat, obj.cbFormat);
    break;
  case FileNodeTypeID::ObjectRevisionWithRefCountFNDX:
    obj.fnt = new ObjectRevisionWithRefCountFNDX(obj.stpFormat, obj.cbFormat);
    break;
  case FileNodeTypeID::ObjectSpaceManifestListReferenceFND:
    obj.fnt =
        new ObjectSpaceManifestListReferenceFND(obj.stpFormat, obj.cbFormat);
    break;
  case FileNodeTypeID::ObjectSpaceManifestListStartFND:
    obj.fnt = new ObjectSpaceManifestListStartFND();
    break;
  case FileNodeTypeID::ObjectSpaceManifestRootFND:
    obj.fnt = new ObjectSpaceManifestRootFND();
    break;
  case FileNodeTypeID::ReadOnlyObjectDeclaration2LargeRefCountFND:
    obj.fnt = new ReadOnlyObjectDeclaration2LargeRefCountFND(obj.stpFormat,
                                                             obj.cbFormat);
    break;
  case FileNodeTypeID::ReadOnlyObjectDeclaration2RefCountFND:
    obj.fnt =
        new ReadOnlyObjectDeclaration2RefCountFND(obj.stpFormat, obj.cbFormat);
    break;
  case FileNodeTypeID::RevisionManifestEndFND:
    obj.fnt = new RevisionManifestEndFND();
    break;
  case FileNodeTypeID::RevisionManifestListReferenceFND:
    obj.fnt = new RevisionManifestListReferenceFND(obj.stpFormat, obj.cbFormat);
    break;
  case FileNodeTypeID::RevisionManifestListStartFND:
    obj.fnt = new RevisionManifestListStartFND();
    break;
  case FileNodeTypeID::RevisionManifestStart4FND:
    obj.fnt = new RevisionManifestStart4FND();
    break;
  case FileNodeTypeID::RevisionManifestStart6FND:
    obj.fnt = new RevisionManifestStart6FND();
    break;
  case FileNodeTypeID::RevisionManifestStart7FND:
    obj.fnt = new RevisionManifestStart7FND();
    break;
  case FileNodeTypeID::RevisionRoleAndContextDeclarationFND:
    obj.fnt = new RevisionRoleAndContextDeclarationFND();
    break;
  case FileNodeTypeID::RevisionRoleDeclarationFND:
    obj.fnt = new RevisionRoleDeclarationFND();
    break;
  case FileNodeTypeID::RootObjectReference2FNDX:
    obj.fnt = new RootObjectReference2FNDX();
    break;
  case FileNodeTypeID::RootObjectReference3FND:
    obj.fnt = new RootObjectReference3FND();
    break;

  default:
    obj.fnt = nullptr;
    break;
  }

  if (obj.fnt != nullptr) {
    ds >> *obj.fnt;
  }

  return ds;
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
} // namespace MSONcommon
