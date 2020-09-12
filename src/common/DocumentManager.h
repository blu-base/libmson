#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H

#include <memory>

#include <QDataStream>
#include <QDir>
#include <QFile>
#include <QMap>
#include <QUuid>
#include <QtCore/qglobal.h>

#include "MSONDocument.h"

namespace MSONcommon {

class DocumentManager {
private:
  static QMap<QUuid, std::shared_ptr<MSONDocument>> docs;

public:
  DocumentManager() = default;
  ~DocumentManager() = default;

  /** Returns true if the document exists in this Manager.
   * Will reparse the document header at the respective location of guidFile. */
  bool containsDocument(QDataStream &ds);

  /** Returns true if the document exists in this Manager */
  bool containsDocument(const QUuid &guidFile);

  /** Parse MSONDocument from QDataStream. */
  QUuid parseDocument(QDataStream &ds);

  /** Parse MSONDocument from specified File. */
  QUuid parseDocument(const QString& fileName);

  /** Adds Document to this Manager*/
  void addDocument(std::shared_ptr<MSONDocument> doc );

  /** Creates new, empty Document */
  QUuid createDocument();

//  /** Parse OneNote Files in specified directory and return their individual
//   * guidFile. @param parse_subdirs toggles if subdirectories are also parsed
//   * recursively.*/
//  QList<QUuid> parseDirectory(const QDir dir, const bool parse_subdirs = false);

  /** Will remove the document of ds from this Manager,
   * however, the document will not be saved. */
  bool removeDocument(const QUuid &guidFile);

  /** Removes all documents saved from this Manager. */
  void removeDocuments();

  /** Get pointer to MSON Document. Returns nullptr if guidFile is not in this
   * Manager */
  static std::shared_ptr<MSONDocument> getDocument(const QUuid &guidFile);

  static std::shared_ptr<MSONDocument> getDocument(QDataStream &ds);


  /** Utility function to reparse guid from the stream head. */
  static QUuid getDocumentID(QDataStream &ds);

  /** Returns all Documents governed by this Manager */
  static QList<std::shared_ptr<MSONDocument>> getDocuments();

  /** Returns all Documents' IDs governed by this Manager */
  static QList<QUuid> getDocumentIDs();

  /** Return the complete storage of this Manager */
  static QMap<QUuid, std::shared_ptr<MSONDocument>> getDocumentsMap();

  void generateXml(const QUuid &guidFile, const QString &outputfile);
};

} // namespace MSONcommon

#endif // DOCUMENTMANAGER_H
