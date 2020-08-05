#ifndef FILENODELISTHEADER_H
#define FILENODELISTHEADER_H

#include <QDataStream>
#include <QXmlStreamWriter>
#include <QDebug>
#include <QtCore/qglobal.h>
namespace MSONcommon {

class FileNodeList;

class FileNodeListHeader {
private:
  static constexpr const quint64 uintMagic = 0xA4567AB1F5F7F4C4;

  quint32 m_fileNodeListID;
  quint32 m_nFragmentSequence;

  // \todo make weak pointer
  FileNodeList *m_parent;

public:
  FileNodeListHeader();
  FileNodeListHeader(const FileNodeListHeader &fnl); // copy constructor
  FileNodeListHeader(FileNodeListHeader &&fnl);      // move constructor

  FileNodeListHeader(FileNodeList *parent);

  bool isValid();

  friend QDataStream &operator<<(QDataStream &ds,
                                 const FileNodeListHeader &obj);
  friend QDataStream &operator>>(QDataStream &ds, FileNodeListHeader &obj);

  friend QDebug operator<<(QDebug dbg, const FileNodeListHeader &obj);

    void generateXml(QXmlStreamWriter &xmlWriter) const;

  FileNodeListHeader &
  operator=(const FileNodeListHeader &rhs);                // copy assignment
  FileNodeListHeader &operator=(FileNodeListHeader &&rhs); // move assignment

  static quint64 getUintMagic();
  quint32 getFileNodeListID() const;
  void setFileNodeListID(const quint32 &value);
  bool isFileNodeListIDValid() const;

  quint32 getNFragmentSequence() const;
  void setNFragmentSequence(const quint32 &value);
  bool isNFragmentSequenceValid() const;
};
} // namespace MSONcommon
#endif // FILENODELISTHEADER_H
