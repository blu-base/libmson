#include "FileNode.h"

namespace libmson {
namespace priv {

FileNode::FileNode(
    RSChunkContainer_WPtr_t parent_fileNodeListFragment)
    : m_parent(parent_fileNodeListFragment) {}

RSChunkContainer_WPtr_t FileNode::getParent() {
  return m_parent;
}

quint64 FileNode::cb() const {
  return minSizeInFile + fnt->getSizeInFile();
}

RevisionStoreChunkType FileNode::getType() const {
  return RevisionStoreChunkType::FileNode;
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

} // namespace priv
} // namespace libmson
