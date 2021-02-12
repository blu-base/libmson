#include <QtCore/qglobal.h>
#include <QDebug>
#if QT_VERSION >= 0x050000
#include <QtWidgets/QApplication>
#else
#include <QtGui/QApplication>
#endif
#include <QCommandLineParser>

#include "mainwindow.h"



int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QCommandLineParser parser;

  parser.addVersionOption();
  parser.addHelpOption();

  QCommandLineOption file(
      QStringList() << QStringLiteral("f") << QStringLiteral("file"),
      QStringLiteral("Open <file> at startup."), QStringLiteral("file"));
  parser.addOption(file);

  parser.process(a);



  MainWindow w(&parser, file);
  w.show();
  return a.exec();
}
