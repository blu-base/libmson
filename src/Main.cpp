#include <iostream>



#include <QDataStream>
#include <QFile>
#include <QDebug>

#include <QDir>

#include <QUuid>


#include "common/MSONHeader.h"

using namespace std;

int main()
{
  cout << "Hello World!" << endl;

  qDebug() << "CWD: " << QDir::currentPath();

  QFile file("../resources/sample-single-text/Section 1.one");
  file.open(QIODevice::ReadOnly);
  QDataStream in(&file);    // read the data serialized from the file


  qDebug() << "Reading " << file;
  qDebug() << "ByteOrder" << in.byteOrder();

  MSONHeader header(in);

  return 0;
}
