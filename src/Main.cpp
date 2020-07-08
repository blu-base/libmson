#include <iostream>

#include <QDataStream>
#include <QDebug>
#include <QFile>

#include <QDir>

#include <QUuid>

#include "common/DocumentSingleton.h"
#include "common/MSONDocument.h"

using namespace std;

int main() {

  qDebug() << "CWD: " << QDir::currentPath();
  //  QFile file("../resources/sample-single-text/Notizbuch öffnen.onetoc2");

  QFile file("../resources/sample-single-text/Section 1.one");
  file.open(QIODevice::ReadOnly);

  QDataStream in(&file); // read the data serialized from the file

  qDebug() << "Current pos in file: " << in.device()->pos();

  MSONcommon::DocumentSingleton::getInstance()->setDoc(
      new MSONcommon::MSONDocument());

  MSONcommon::MSONDocument *mdoc =
      MSONcommon::DocumentSingleton::getInstance()->getDoc();

  in >> *mdoc;

  qDebug() << *(MSONcommon::DocumentSingleton::getInstance()->getDoc());

  file.close();
  return 0;

  unsigned long temp;
}
