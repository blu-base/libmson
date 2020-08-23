#ifndef FILENODE_H
#define FILENODE_H

#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QtCore/qglobal.h>
#include <QXmlStreamWriter>

#include "FileNodeTypes/IFileNodeType.h"

#include "commonTypes/Enums.h"
namespace MSONcommon {

static constexpr const quint32 FileNode_maskReserved = 0x1;
static constexpr const quint32 FileNode_maskBaseType = 0xF;
static constexpr const quint32 FileNode_maskCbFormat = 0x3;
static constexpr const quint32 FileNode_maskStpFormat = 0x3;
static constexpr const quint32 FileNode_maskFileNodeSize = 0x1FFF;
static constexpr const quint32 FileNode_maskFileNodeID = 0x3FF;

static constexpr const quint32 FileNode_shiftReserved = 31;
static constexpr const quint32 FileNode_shiftBaseType = 27;
static constexpr const quint32 FileNode_shiftCbFormat = 25;
static constexpr const quint32 FileNode_shiftStpFormat = 23;
static constexpr const quint32 FileNode_shiftFileNodeSize = 10;
static constexpr const quint32 FileNode_shiftFileNodeID = 0;

class FileNode {
protected:
  // nonessential. position in byte stream. for debug purposes.
  quint64 stp;

  quint16 fileNodeID;
  quint16 fileNodeSize;

  quint8 stpFormat;
  quint8 cbFormat;

  quint8 baseType;

  quint8 reserved;

  //  FileNodeType *fileNodeType;

  IFileNodeType *fnt;

  /**
   * @brief maskReserved
   *
   * masks and shifts for parsing filenode
   */

public:
  FileNode();
  FileNode(const FileNode &source);

  ~FileNode();

  //  FileNode(const FileNode& source); // copy constructor
  //  FileNode(FileNode&& source);      // move constructor

  //  FileNode& operator=(const FileNode& rhs); // copy assignment
  //  FileNode& operator=(FileNode&& rhs);      // move assignment

  friend QDataStream &operator<<(QDataStream &ds, const FileNode &obj);
  friend QDataStream &operator>>(QDataStream &ds, FileNode &obj);

  friend QDebug operator<<(QDebug dbg, const FileNode &obj);

  void generateXml(QXmlStreamWriter &xmlWriter) const;


  bool isValid();
  quint16 getFileNodeID() const;
  void setFileNodeID(const quint16 &value);
  FileNodeTypeID getFileNodeTypeID() const;
  quint16 getFileNodeSize() const;
  void setFileNodeSize(const quint16 &value);
  quint8 getStpFormat() const;
  void setStpFormat(const quint8 &value);
  quint8 getCbFormat() const;
  void setCbFormat(const quint8 &value);
  quint8 getBaseType() const;
  void setBaseType(const quint8 &value);

  quint64 getStp() const;

  void setFileNodeType(const IFileNodeType &value);
  IFileNodeType *getFnt() const;
};
} // namespace MSONcommon
#endif // FILENODE_H
