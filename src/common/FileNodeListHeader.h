#ifndef FILENODELISTHEADER_H
#define FILENODELISTHEADER_H

#include <QDebug>
#include <QXmlStreamWriter>
#include <QtCore/qglobal.h>

#include "IRevisionStoreFileObject.h"

namespace MSONcommon {

class FileNodeListHeader : public IRevisionStoreFileObject {
private:
  static constexpr const quint64 uintMagic = 0xA4567AB1F5F7F4C4;

  quint32 m_fileNodeListID;
  quint32 m_nFragmentSequence;

public:
  FileNodeListHeader();

  bool isValid();

  static quint64 getUintMagic();

  quint32 getFileNodeListID() const;
  void setFileNodeListID(const quint32 &value);
  bool isFileNodeListIDValid() const;

  quint32 getNFragmentSequence() const;
  void setNFragmentSequence(const quint32 &value);
  bool isNFragmentSequenceValid() const;

  static quint64 getSizeInFile() { return sizeInFile; }

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;

  static const quint64 sizeInFile = 12;
};

} // namespace MSONcommon

#endif // FILENODELISTHEADER_H
