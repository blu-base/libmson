#include "DocumentManager.h"

MSONcommon::DocumentManager::DocumentManager() {}

MSONcommon::DocumentManager::~DocumentManager() {

  for (MSONDocument *doc : docs.values()) {
    delete doc;
  }

  docs.clear();
}

bool MSONcommon::DocumentManager::containsDocument(QDataStream &ds) {
  return docs.contains(getDocumentID(ds));
}

bool MSONcommon::DocumentManager::containsDocument(const QUuid &guidFile) {
  return docs.contains(guidFile);
}

QUuid MSONcommon::DocumentManager::parseDocument(QDataStream &ds) {
  QUuid guid;
  if (ds.device()->isReadable()) {
    MSONDocument *newDoc = new MSONDocument();

    ds >> *newDoc;

    guid = newDoc->getHeader()->getGuidFile();

    docs.insert(guid, newDoc);
  } else {
      qWarning() << "ERROR: Stream not readable" << '\n';
  }

  return guid;
}

QUuid MSONcommon::DocumentManager::parseDocument(QString fileName) {
  QFile file(fileName);

  bool couldopen = file.open(QIODevice::ReadOnly);

  QUuid newDocId;
  if (couldopen) {
    QDataStream in(&file);

    newDocId = parseDocument(in);
    file.close();
  } else {
    qWarning() << "ERROR: could not open file: " << fileName << '\n';
  }

  return newDocId;
}

void MSONcommon::DocumentManager::addDocument(MSONcommon::MSONDocument *doc) {

  docs.insert(doc->getHeader()->getGuidFile(), doc);
}

QUuid MSONcommon::DocumentManager::createDocument() {

  MSONDocument *newDoc = new MSONDocument();

  QUuid newDocId = newDoc->getHeader()->getGuidFile();

  docs.insert(newDocId, newDoc);

  return newDocId;
}

QList<QUuid>
MSONcommon::DocumentManager::parseDirectory(QDir dir,
                                            const bool parse_subdirs) {
  QList<QUuid> newDocs{};

  if (!dir.exists()) {
    qWarning("The directory does not exist");
    return newDocs;
  }

  QStringList msonFileExtensions;
  msonFileExtensions << "*.one"
                     << "*.one2toc";
  for (QString fileName : dir.entryList(msonFileExtensions, QDir::Files)) {
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);

    QUuid newDocId = parseDocument(in);
    file.close();
    newDocs.append(newDocId);
  }

  // recurse parseDirectory for subdirs
  if (parse_subdirs) {

    QStringList subdirectories = dir.entryList(QDir::Dirs);
    for (QString dirName : subdirectories) {

      QDir subdir(dirName);
      newDocs.append(parseDirectory(subdir, true));
    }
  }

  return newDocs;
}

bool MSONcommon::DocumentManager::removeDocument(const QUuid &guidFile) {

  return docs.remove(guidFile);
}

void MSONcommon::DocumentManager::removeDocuments() { docs.clear(); }

MSONcommon::MSONDocument *
MSONcommon::DocumentManager::getDocument(const QUuid &guidFile) {
  return docs.value(guidFile);
}

QUuid MSONcommon::DocumentManager::getDocumentID(QDataStream &ds) {
  quint64 currentPos = ds.device()->pos();

  ds.device()->seek(0);

  QUuid id = nullptr;
  if (ds.device()->bytesAvailable() > 16) {
    ds.skipRawData(8);
    ds >> id;
  }

  ds.device()->seek(currentPos);

  return id;
}

QList<MSONcommon::MSONDocument *> MSONcommon::DocumentManager::getDocuments() {
  return docs.values();
}

QList<QUuid> MSONcommon::DocumentManager::getDocumentIDs() {
  return docs.keys();
}

QMap<QUuid, MSONcommon::MSONDocument *>
MSONcommon::DocumentManager::getDocumentsMap() {
  return docs;
}

void MSONcommon::DocumentManager::generateXml(const QUuid &guidFile,
                                              const QString &outputfile) {
  auto it = docs.find(guidFile);

  if (it != docs.end()) {
    if (!outputfile.isEmpty()) {
      QFile xmlFile(outputfile);

      xmlFile.open(QIODevice::WriteOnly);
      QXmlStreamWriter xmlWriter(&xmlFile);

      docs[guidFile]->generateXml(xmlWriter);

      xmlFile.close();
    }
  }
}
