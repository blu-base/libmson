#ifndef REVISIONMANIFEST_H
#define REVISIONMANIFEST_H

#include <QtCore/qglobal.h>
#include <vector>

#include "FileNode.h"
namespace MSONcommon {
class RevisionManifest {
private:
      std::vector<FileNode*> m_FileNodeSquence;
public:


  RevisionManifest();
  ~RevisionManifest();

  std::vector<FileNode *> &getFileNodeSquence();
  void setFileNodeSquence(const std::vector<FileNode *> &value);



  friend QDataStream &operator<<(QDataStream &ds, const RevisionManifest &obj);
  friend QDataStream &operator>>(QDataStream &ds, RevisionManifest &obj);
  friend QDebug operator<<(QDebug dbg, const RevisionManifest &obj);

  void generateXml(QXmlStreamWriter &xmlWriter) const;


private:
  /**
   * @brief creates RevisionManifest from QDataStream
   * @param ds <QDataStream> containing the deserializable
   * RevisionManifest
   */
  void deserialize(QDataStream &ds);
  /**
   * @brief creates byte stream from RevisionManifest object
   * @param ds <QDataStream> is the output stream to which the serialized
   * RevisionManifest is send
   */
  void serialize(QDataStream &ds) const;

  /**
   * @brief prints the RevisionManifest to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  void toDebugString(QDebug dbg) const;
};
} // namespace MSONcommon
#endif // REVISIONMANIFEST_H
