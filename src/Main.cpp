#include <iostream>

#include <QCoreApplication>
#include <QtCore/qglobal.h>

#include <QCommandLineParser>
#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QXmlStreamWriter>

#include <QDir>

#include <QUuid>

#include "common/DocumentManager.h"
#include "common/MSONDocument.h"

static const QStringList onenotefileextensions{"*.one", "*.onetoc2"};

QStringList fileDirs(QDir &dir, const bool recursively);

QStringList fileDirs(QDir &dir, const bool recursively) {
  QStringList files;
  if (dir.exists()) {
    dir.setNameFilters(onenotefileextensions);
    dir.setFilter(QDir::Files);
    for (const auto &entry : dir.entryList()) {
      files << entry;
    }
    if (recursively) {
      dir.setNameFilters(QStringList() << "*");
      dir.setFilter(QDir::Dirs);
      for (const auto &entry : dir.entryList()) {
        QDir sdir(entry);
        QStringList subdir = fileDirs(sdir, recursively);
        files.append(subdir);
      }
    }
  }

  return files;
}

using namespace std;

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName("one2xml");
  QCoreApplication::setApplicationVersion("0.0");

  QCommandLineParser parser;
  parser.setApplicationDescription("Converter for MS OneNote to Xml");
  parser.addHelpOption();
  parser.addVersionOption();

  QCommandLineOption fileinput(QStringList() << "f"
                                             << "file",
                               "Parse from <inputfile>.", "inputfile");
  parser.addOption(fileinput);
  QCommandLineOption direcotryinput(QStringList() << "d"
                                                  << "dir",
                                    "Parse directory <dir>.", "dir");
  parser.addOption(direcotryinput);
  QCommandLineOption recursive(QStringList() << "r"
                                             << "recursive",
                               "Parse directories recursively.");
  parser.addOption(recursive);
  QCommandLineOption output(QStringList() << "o"
                                          << "output",
                            "Write generated data into the directory <output>. "
                            "Defaults to directory of input.",
                            "output");
  parser.addOption(output);

  QCommandLineOption verbosity(QStringList() << "b"
                                             << "verbose",
                               "Sets verbosity level (0-7) <vlevel>.",
                               "vlevel");
  parser.addOption(verbosity);

  QCommandLineOption debugStr(QStringList() << "s"
                                            << "string",
                              "Prints parsed information.");
  parser.addOption(debugStr);

  // Process the actual command line arguments given by the user
  parser.process(app);

  bool inputFileSet = parser.isSet(fileinput);
  bool inputDirSet = parser.isSet(direcotryinput);
  bool outputSet = parser.isSet(output);
  bool verbositySet = parser.isSet(verbosity);
  bool debugStrSet = parser.isSet(debugStr);

  if (verbositySet) {
    qDebug().setVerbosity(parser.value(verbosity).toInt());
  }

  QTextStream out(stdout);
  if (!inputFileSet && !inputDirSet) {
    out << "\n ERROR: No input given.\n\n";
    out << parser.helpText() << "\n";
    return 1;
  }

  // collecting files to be parsed)
  QStringList files;
  if (inputFileSet) {
    QStringList rawnames = parser.values(fileinput);
    for (const auto &entry : rawnames) {
      QFile file(entry);

      if (file.exists()) {
        files << entry;
      }
    }
  }

  if (inputDirSet) {
    QStringList rawnames = parser.values(direcotryinput);
    for (const auto &entry : rawnames) {
      QDir dir(entry);
      QStringList dirFiles = fileDirs(dir, parser.isSet(recursive));
      files.append(dirFiles);
    }
  }

  if (files.empty()) {
    out << "\n ERROR: Specified input not found or didn't contain onenote "
           "files.\n\n";
    return 1;
  }

  MSONcommon::DocumentManager manager{};

  for (const auto &entry : files) {

    QUuid guid = manager.parseDocument(entry);
    manager.generateXml(guid, entry + ".xml");
    manager.removeDocument(guid);
  }


  //  qDebug() << "CWD: " << QDir::currentPath();
  //  //  QFile file("../resources/sample-single-text/Notizbuch
  //  öffnen.onetoc2");

  //  ;
  ////  file.open(QIODevice::ReadOnly);

  ////  QDataStream in(&file); // read the data serialized from the file

  //  QFile xmlFile("Section1.xml");
  ////  QFile xmlFile("Notizbuch.xml");
  //  xmlFile.open(QIODevice::WriteOnly);
  //  QXmlStreamWriter xmlWriter(&xmlFile);
  //  xmlWriter.setCodec("UTF-16");

  ////  qDebug() << "Current pos in file: " << in.device()->pos();

  //  MSONcommon::DocumentManager manager{};

  //  QUuid guid =
  //  manager.parseDocument("../resources/sample-single-text/Section 1.one");
  ////  QUuid guid =
  /// manager.parseDocument("../resources/sample-single-text/Notizbuch
  ///öffnen.onetoc2");

  //  manager.getDocument(guid)->generateXml(xmlWriter);
  //  xmlFile.close();

  //  manager.removeDocuments();

  ////  file.close();

  return 0;
}
