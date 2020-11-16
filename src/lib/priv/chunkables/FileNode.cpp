#include "FileNode.h"

#include "fileNodeTypes/IFileNodeType.h"

namespace libmson {
namespace priv {

FileNode::FileNode(
    std::weak_ptr<FileNodeListFragment> parent, const quint64 initialStp,
    const quint64 initialCb)
    : Chunkable(initialStp, initialCb), m_parent(parent),
      fileNodeID(static_cast<quint16>(FileNodeTypeID::InvalidFND)),
      fileNodeSize(minSizeInFile),
      stpFormat(static_cast<quint8>(FNCR_STP_FORMAT::UNCOMPRESED_8BYTE)),
      cbFormat(static_cast<quint8>(FNCR_CB_FORMAT::UNCOMPRESED_8BYTE)),
      baseType(0)
{
}

std::weak_ptr<FileNodeListFragment> FileNode::getParent() { return m_parent; }

quint64 FileNode::cb() const
{
  if (fnt != nullptr) {
    return minSizeInFile + fnt->getSizeInFile();
  }
  return minSizeInFile;
}

RevisionStoreChunkType FileNode::getType() const
{
  return RevisionStoreChunkType::FileNode;
}

quint16 FileNode::getFileNodeID() const { return fileNodeID; }

void FileNode::setFileNodeID(const quint16& value) { fileNodeID = value; }

FileNodeTypeID FileNode::getFileNodeTypeID() const
{
  return static_cast<FileNodeTypeID>(fileNodeID);
}

quint16 FileNode::getFileNodeSize() const { return fileNodeSize; }

void FileNode::setFileNodeSize(const quint16& value) { fileNodeSize = value; }

quint8 FileNode::getStpFormat() const { return stpFormat; }

FNCR_STP_FORMAT FileNode::getStpFormatEnum() const
{
  return static_cast<FNCR_STP_FORMAT>(stpFormat);
}

void FileNode::setStpFormat(const quint8& value) { stpFormat = value; }

quint8 FileNode::getCbFormat() const { return cbFormat; }

FNCR_CB_FORMAT FileNode::getCbFormatEnum() const
{
  return static_cast<FNCR_CB_FORMAT>(cbFormat);
}

void FileNode::setCbFormat(const quint8& value) { cbFormat = value; }

quint8 FileNode::getBaseType() const { return baseType; }

void FileNode::setBaseType(const quint8& value) { baseType = value; }

void FileNode::setFileNodeType(const std::shared_ptr<IFileNodeType>& value)
{
  fnt = value;
}

std::shared_ptr<IFileNodeType> FileNode::getFnt() const { return fnt; }

quint8 FileNode::getFileNodeChunkReferenceSize()
{
  return FileNodeChunkReference::getSizeInFile(
      getStpFormatEnum(), getCbFormatEnum());
}

} // namespace priv
} // namespace libmson
