#include "FileNode.h"

#include <QDataStream>
#include <QDebug>
#include <QtEndian>

#include "FileNodeTypes/FileDataStoreListReferenceFND.h"
#include "FileNodeTypes/ObjectSpaceManifestListReferenceFND.h"
#include "FileNodeTypes/ObjectSpaceManifestRootFND.h"

IFileNodeType *FileNode::getFnt() const { return fnt; }

FileNode::FileNode()
    : fileNodeID{}, fileNodeSize{}, stpFormat{}, cbFormat{}, baseType{},
      reserved{}, fnt{nullptr} {}

FileNode::FileNode(const FileNode &source)
    : fileNodeID{source.fileNodeID}, fileNodeSize{source.fileNodeSize},
      stpFormat{source.stpFormat}, cbFormat{source.cbFormat},
      baseType{source.baseType}, reserved{}, fnt{nullptr}

// TODO filenodetype
{}

FileNode::~FileNode() {}

QDataStream &operator>>(QDataStream &ds, FileNode &obj) {
  //  if (!ds.byteOrder()) {
  //    ds.setByteOrder(QDataStream::LittleEndian);
  //  }
  ds.setByteOrder(QDataStream::LittleEndian);

  quint32 temp;

  ds >> temp;

  obj.reserved = (temp >> FileNode::shiftReserved) & FileNode::maskReserved;
  obj.baseType = (temp >> FileNode::shiftBaseType) & FileNode::maskBaseType;
  obj.cbFormat = (temp >> FileNode::shiftCbFormat) & FileNode::maskCbFormat;
  obj.stpFormat = (temp >> FileNode::shiftStpFormat) & FileNode::maskStpFormat;
  obj.fileNodeSize =
      (temp >> FileNode::shiftFileNodeSize) & FileNode::maskFileNodeSize;
  obj.fileNodeID =
      (temp >> FileNode::shiftFileNodeID) & FileNode::maskFileNodeID;

  if (obj.fileNodeID == 0x08) {
    obj.fnt =
        new ObjectSpaceManifestListReferenceFND(obj.stpFormat, obj.cbFormat);
  } else if (obj.fileNodeID == 0x04) {
    obj.fnt = new ObjectSpaceManifestRootFND();
  } else if (obj.fileNodeID == 0x90) {
    obj.fnt = new FileDataStoreListReferenceFND(obj.stpFormat, obj.cbFormat);
  } else {
    obj.fnt = nullptr;
  }

  if (obj.fnt != nullptr) {
    ds >> *obj.fnt;
  }

  ////  switch(obj.baseType ) {
  ////    case FileNodeType::ObjectSpaceManifestListReferenceFND:
  //      obj.fileNodeType = new
  //      ObjectSpaceManifestListReferenceFND(obj.stpFormat,obj.cbFormat); ds
  //      >>
  //      *(obj.fileNodeType);
  ////      break;
  ////  }

  return ds;
}

QDebug operator<<(QDebug dbg, const FileNode &obj) {
  QDebugStateSaver saver(dbg);

  dbg.noquote() << "FileNode. ID: "
                << QString("0x%1").arg(obj.fileNodeID, 3, 16, QLatin1Char('0'))
                << " Size: "
                << QString("0x%1").arg(obj.fileNodeSize, 4, 16,
                                       QLatin1Char('0'))
                << " Stp/Cb format: " << obj.stpFormat << "/" << obj.cbFormat
                << " BaseType: " << obj.baseType << '\n';

  if (obj.fnt != nullptr) {
    dbg << *obj.fnt;
  } else {
    dbg << "FileNodeType is not declared.";
  }

  return dbg;
}

quint16 FileNode::getFileNodeID() const { return fileNodeID; }

void FileNode::setFileNodeID(const quint16 &value) { fileNodeID = value; }

quint16 FileNode::getFileNodeSize() const { return fileNodeSize; }

void FileNode::setFileNodeSize(const quint16 &value) { fileNodeSize = value; }

quint8 FileNode::getStpFormat() const { return stpFormat; }

void FileNode::setStpFormat(const quint8 &value) { stpFormat = value; }

quint8 FileNode::getCbFormat() const { return cbFormat; }

void FileNode::setCbFormat(const quint8 &value) { cbFormat = value; }

quint8 FileNode::getBaseType() const { return baseType; }

void FileNode::setBaseType(const quint8 &value) { baseType = value; }
