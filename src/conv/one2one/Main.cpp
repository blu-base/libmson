#include <iostream>
#include <memory>
#include <vector>

#include <QCoreApplication>
#include <QtCore/qglobal.h>

#include <QCommandLineParser>
#include <QDataStream>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QXmlStreamWriter>

#include <QDir>

#include <QUuid>

#include "../../lib/priv/RevisionStoreFile.h"
#include "../../lib/priv/RevisionStoreFileParser.h"
#include "../../lib/priv/RevisionStoreFileWriter.h"

#include "../../lib/priv/chunkables/Chunkable.h"
#include "../../lib/priv/chunkables/FreeChunk.h"
#include "../../lib/priv/chunkables/FreeChunkListFragment.h"
#include "../../lib/priv/chunkables/RevisionStoreChunkContainer.h"
#include "../../lib/priv/chunkables/RevisionStoreFileHeader.h"

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
  QCoreApplication::setApplicationName("one2one");
  QCoreApplication::setApplicationVersion("0.0");

  QCommandLineParser parser;
  parser.setApplicationDescription("Test Parser/Builder for .one files");
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
  QCommandLineOption recursive(
      QStringList() << "r"
                    << "recursive",
      "Parse directories recursively.");
  parser.addOption(recursive);
  QCommandLineOption output(
      QStringList() << "o"
                    << "output",
      "Write generated data into the directory <output>. "
      "Defaults to directory of input.",
      "output");
  parser.addOption(output);

  QCommandLineOption verbosity(
      QStringList() << "b"
                    << "verbose",
      "Sets verbosity level (0-7) <vlevel>.", "vlevel");
  parser.addOption(verbosity);

  QCommandLineOption debugStr(
      QStringList() << "s"
                    << "string",
      "Prints parsed information.");
  parser.addOption(debugStr);

  // Process the actual command line arguments given by the user
  parser.process(app);

  bool inputFileSet = parser.isSet(fileinput);
  bool inputDirSet  = parser.isSet(direcotryinput);
  bool recursiveSet = parser.isSet(recursive);
  bool outputSet    = parser.isSet(output);
  bool verbositySet = parser.isSet(verbosity);
  bool debugStrSet  = parser.isSet(debugStr);

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
    for (const auto& entry : rawnames) {
      QFile file(entry);

      if (file.exists()) {
        files << entry;
      }
    }
  }

  if (inputDirSet) {
    QStringList rawnames = parser.values(direcotryinput);
    for (const auto& entry : rawnames) {
      QDir dir(entry);
      QStringList dirFiles = fileDirs(dir, recursiveSet);
      files.append(dirFiles);
    }
  }

  if (files.empty()) {
    out << "\n ERROR: Specified input not found or didn't contain onenote "
           "files.\n\n";
    return 1;
  }

  //  for (const auto &entry : files) {
  const auto& entry = files.at(0);

  QFileInfo file(entry);

  QString outputPath;
  QString baseFileName = file.fileName().left(file.fileName().lastIndexOf('.'));

  QFile mson_file(entry);
  bool couldopen = mson_file.open(QIODevice::ReadOnly);

  if (!couldopen) {
    qFatal("Could not open file.");
  }

  QDataStream input(&mson_file);

  auto fileParser = libmson::priv::RevisionStoreFileParser(input);

  std::shared_ptr<libmson::priv::RevisionStoreFile> mson = fileParser.parse();


  //  auto fclf = std::make_shared<libmson::FreeChunkListFragment>(4 * 16);
  //  auto rsc_fclf = std::make_shared<libmson::RevisionStoreChunk>(fclf,
  //  0x400,4*16);

  //  auto fc1 = std::make_shared<libmson::FreeChunk>(0x100);
  //  auto fc2 = std::make_shared<libmson::FreeChunk>(0x200);
  //  auto fc3 = std::make_shared<libmson::FreeChunk>(0x300);

  //  auto rsc_fc1 = std::make_shared<libmson::RevisionStoreChunk>(fc1,
  //  0x400,0x100); auto rsc_fc2 =
  //  std::make_shared<libmson::RevisionStoreChunk>(fc2, 0x500,0x200); auto
  //  rsc_fc3 = std::make_shared<libmson::RevisionStoreChunk>(fc3, 0x600,0x300);

  //  std::static_pointer_cast<libmson::FreeChunkListFragment>(
  //      rsc_fclf.get()->getChunk())
  //      ->setFcrFreeChunks({rsc_fc1, rsc_fc2, rsc_fc3});

  //  const std::vector<std::weak_ptr<libmson::RevisionStoreChunk>> fclf_chunks{
  //      rsc_fc1, rsc_fc2, rsc_fc3};

  //  fclf->setFcrFreeChunks(fclf_chunks);

  //  mson.getChunks().emplace_back(rsc_fclf);
  //  mson.getChunks().emplace_back(rsc_fc1);
  //  mson.getChunks().emplace_back(rsc_fc2);
  //  mson.getChunks().emplace_back(rsc_fc3);

  //  std::static_pointer_cast<libmson::RevisionStoreFileHeader>(
  //      mson.getChunks().begin()->get()->getChunk())
  //      ->setFcrFreeChunkList(rsc_fclf);

  // libmson::FreeChunk;

  QFile msonOut(entry + ".new");
  msonOut.open(QIODevice::WriteOnly);
  QDataStream outStream(&msonOut);
  libmson::priv::RevisionStoreFileWriter(mson).write(outStream);

  if (outputSet) {
    outputPath = parser.value(output);
  }
  else {

    if (entry.contains("/")) {
      outputPath = entry.left(entry.lastIndexOf("/"));
    }
    else {
      outputPath = ".";
    }
  }

  //  }

  return 0;
}
