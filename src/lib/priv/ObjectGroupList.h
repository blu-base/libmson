//#ifndef OBJECTGROUPLIST_H
//#define OBJECTGROUPLIST_H

//#include <QtCore/qglobal.h>
//#include <vector>

//#include <QDebug>

//#include "FileNode.h"
//#include "FileNodeListFragment.h"
//#include "commonTypes/FileNodeChunkReference.h"

//#include "IRevisionStoreFileObject.h"

// class QDataStream;

// namespace MSONcommon {

// class ObjectGroupList : public IRevisionStoreFileObject {
// private:
//  FileNodeChunkReference m_ref;

//  std::vector<std::shared_ptr<FileNode>> m_fileNodeSequence;

//  std::vector<std::shared_ptr<FileNodeListFragment>> m_fileNodeListFragments;

// public:
//  ObjectGroupList(const FileNodeChunkReference &ref);
//  ~ObjectGroupList() = default;

//  std::vector<std::shared_ptr<FileNode>> getFileNodeSequence() const;
//  void setFileNodeSequence(const std::vector<std::shared_ptr<FileNode>>
//  &value);

//  std::vector<std::shared_ptr<FileNodeListFragment>>
//  getFileNodeListFragments();

//  void setFileNodeListFragments(
//      const std::vector<std::shared_ptr<FileNodeListFragment>> &value);
//  FileNodeChunkReference getRef() const;
//  void setRef(const FileNodeChunkReference &ref);

//  void generateXml(QXmlStreamWriter &xmlWriter) const;

// private:
//  virtual void deserialize(QDataStream &ds) override;
//  virtual void serialize(QDataStream &ds) const override;

//  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;
//  /**
//   * @brief prints the ObjectGroupList to a <QDebug> object
//   * @param dbg <QDebug> string builder for the debug information
//   */
//  virtual void toDebugString(QDebug &dbg) const override;
//};

//} // namespace MSONcommon

//#endif // OBJECTGROUPLIST_H
