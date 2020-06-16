#ifndef FILENODE_H
#define FILENODE_H

#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QtCore/qglobal.h>

#include "FileNodeType.h"

#include "FileNodeTypes/IFileNodeType.h"

class FileNode {
protected:
  quint16 fileNodeID;
  quint16 fileNodeSize;

  quint8 stpFormat;
  quint8 cbFormat;

  quint8 baseType;

  quint8 reserved;

  FileNodeType *fileNodeType;

  IFileNodeType *fnt;

  /**
   * @brief maskReserved
   *
   * masks and shifts for parsing filenode
   */
  static constexpr const uint32_t maskReserved = 0x1;
  static constexpr const uint32_t maskBaseType = 0xF;
  static constexpr const uint32_t maskCbFormat = 0x3;
  static constexpr const uint32_t maskStpFormat = 0x3;
  static constexpr const uint32_t maskFileNodeSize = 0x1FFF;
  static constexpr const uint32_t maskFileNodeID = 0x3FF;

  static constexpr const uint32_t shiftReserved = 31;
  static constexpr const uint32_t shiftBaseType = 27;
  static constexpr const uint32_t shiftCbFormat = 25;
  static constexpr const uint32_t shiftStpFormat = 23;
  static constexpr const uint32_t shiftFileNodeSize = 10;
  static constexpr const uint32_t shiftFileNodeID = 0;

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

  bool isValid();
  quint16 getFileNodeID() const;
  void setFileNodeID(const quint16 &value);
  quint16 getFileNodeSize() const;
  void setFileNodeSize(const quint16 &value);
  quint8 getStpFormat() const;
  void setStpFormat(const quint8 &value);
  quint8 getCbFormat() const;
  void setCbFormat(const quint8 &value);
  quint8 getBaseType() const;
  void setBaseType(const quint8 &value);

  void setFileNodeType(const FileNodeType &value);
};

#endif // FILENODE_H
