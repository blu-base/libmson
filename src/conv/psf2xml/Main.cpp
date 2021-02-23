#include <iostream>

#include <QCoreApplication>
#include <QtCore/qglobal.h>

#include <QCommandLineParser>
#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QXmlStreamWriter>

#include <QDir>

#include "../../lib/priv/PackageStoreFile.h"
#include "../../lib/priv/PackageStoreFileParser.h"

#include <../FormatIdentifier.h>

#include "PSFtoXml.h"

static const QStringList onenotefileextensions{"*.one", "*.onetoc2"};

QStringList fileDirs(QDir& dir, const bool recursively);

QStringList fileDirs(QDir& dir, const bool recursively)
{
  QStringList files;
  if (dir.exists()) {
    dir.setNameFilters(onenotefileextensions);
    dir.setFilter(QDir::Files);
    for (const auto& entry : dir.entryList()) {
      files << dir.filePath(entry);
    }
    if (recursively) {
      //      dir.setNameFilters(QStringList() << "*");
      dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
      for (const auto& entry : dir.entryInfoList()) {
        QDir sdir(entry.filePath());
        sdir.setFilter(QDir::NoDotAndDotDot);
        QStringList subdir = fileDirs(sdir, recursively);
        files.append(subdir);
      }
    }
  }

  return files;
}

using namespace std;

int main(int argc, char* argv[])
{
  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName("psf2xml");
  QCoreApplication::setApplicationVersion("0.0");

  QCommandLineParser parser;
  parser.setApplicationDescription("Dev Tool. Prints PackageStoreFile "
                                   "structure of a MS OneNote file to Xml.");
  parser.addHelpOption();
  parser.addVersionOption();

  QCommandLineOption fileinput(
      QStringList() << "f"
                    << "file",
      "Parse from <inputfile>.", "inputfile");
  parser.addOption(fileinput);

  QCommandLineOption direcotryinput(
      QStringList() << "d"
                    << "dir",
      "Parse directory <dir>.", "dir");
  parser.addOption(direcotryinput);

  QCommandLineOption recursivedirecotryinput(
      QStringList() << "D"
                    << "Dirs",
      "Recursively parse directory <rdir>.", "rdir");
  parser.addOption(recursivedirecotryinput);

  //  QCommandLineOption output(
  //      QStringList() << "o"
  //                    << "output",
  //      "Write generated data into the directory <output>. "
  //      "Defaults to directory of input.",
  //      "output");
  //  parser.addOption(output);

  QCommandLineOption verbosity(
      QStringList() << "b"
                    << "verbose",
      "Sets verbosity level (0-7) of QDebug", "level");
  parser.addOption(verbosity);


  // Process the actual command line arguments given by the user
  parser.process(app);

  bool inputFileSet         = parser.isSet(fileinput);
  bool inputDirSet          = parser.isSet(direcotryinput);
  bool recursiveInputDirSet = parser.isSet(recursivedirecotryinput);
  bool verbositySet         = parser.isSet(verbosity);

  if (verbositySet) {
    qDebug().setVerbosity(parser.value(verbosity).toInt());
  }

  QTextStream out(stdout);
  if (!inputFileSet && !inputDirSet && !recursiveInputDirSet) {
    out << "\n ERROR: No input given.\n\n";
    out << parser.helpText() << "\n";
    return 1;
  }

  // collecting files to be parsed)
  QStringList files;
  if (inputFileSet) {
    QStringList rawnames = parser.values(fileinput);
    for (const auto& entry : rawnames) {
      QFile file(entry);

      if (file.exists()) {
        files << entry;
      }
    }
  }

  // collect files onlyin specified path
  if (inputDirSet) {
    QStringList rawnames = parser.values(direcotryinput);
    for (const auto& entry : rawnames) {
      QDir dir(entry);
      QStringList dirFiles = fileDirs(dir, false);
      files.append(dirFiles);
    }
  }

  // collect files from directory tree
  if (recursiveInputDirSet) {
    QStringList rawnames = parser.values(recursivedirecotryinput);
    for (const auto& entry : rawnames) {
      QDir dir(entry);
      QStringList dirFiles = fileDirs(dir, true);
      files.append(dirFiles);
    }
  }

  if (files.empty()) {
    out << "\n ERROR: Specified input not found or input didn't contain any "
           "onenote files.\n\n";
    return 1;
  }

  for (const auto& entry : files) {

    QFileInfo fileInfo(entry);

    QString baseFileName =
        fileInfo.fileName().left(fileInfo.fileName().lastIndexOf('.'));

    // parse file

    auto identifier = libmson::FormatIdentifier(entry.toStdString());
    qInfo() << "Parsing" << entry;


    QString formatInfo{"  file format: "};

    auto onestoreFormat = identifier.getFormat();

    switch (onestoreFormat) {
    case libmson::OnFormat::One03_revStore:
      formatInfo += "One03_revStore";
      break;
    case libmson::OnFormat::OneToc03_revStore:
      formatInfo += "OneToc03_revStore";
      break;
    case libmson::OnFormat::One10_revStore:
      formatInfo += "One10_revStore";
      break;
    case libmson::OnFormat::OneToc10_revStore:
      formatInfo += "OneToc10_revStore";
      break;
    case libmson::OnFormat::OnePkg:
      formatInfo += "OnePkg";
      break;
    case libmson::OnFormat::One_packStore:
      formatInfo += "One_packStore";
      break;
    case libmson::OnFormat::OneToc_packStore:
      formatInfo += "OneToc_packStore";
      break;
    case libmson::OnFormat::Unrecoqnized:
      formatInfo += "Unrecoqnized";
      break;
    }

    qInfo().noquote().nospace() << formatInfo;

    if ((onestoreFormat != libmson::OnFormat::One_packStore) &&
        (onestoreFormat != libmson::OnFormat::OneToc_packStore)) {
      qInfo() << "  Skipping since the file format is not supported." << Qt::endl;
      continue;
    }

    QFile msonFile(entry);
    bool couldopen = msonFile.open(QIODevice::ReadOnly);

    if (!couldopen) {
      qFatal("Could not open file.");
    }

    QDataStream input(&msonFile);
    auto fileParser = libmson::packStore::PackageStoreFileParser(
        input, baseFileName + ".one");
    auto packageStoreFile = fileParser.parse();
    msonFile.close();

    QFile outputFile(fileInfo.path() + "/" + baseFileName + ".xml");
    PSFtoXml::writeSequence(outputFile, packageStoreFile);
  }

  return 0;
}
