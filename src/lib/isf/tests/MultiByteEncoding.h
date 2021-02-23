#ifndef MULTIBYTEENCODINGTEST_H
#define MULTIBYTEENCODINGTEST_H

#include <QtCore/qglobal.h>

#include <QObject>
#include <QTest>

class MultiByteEncodingTest : public QObject {
  Q_OBJECT

private slots:

  static void decodeUIntFromByteArray();
    static void decodeUIntFromStream();

    static void decodeIntFromByteArray();
    static void decodeIntFromStream();

    static void encodeUIntToByteArray();
    static void encodeUIntToStream();

    static void encodeIntToByteArray();
    static void encodeIntToStream();

  //  static void decodeInkPath1();
  //  static void decodeInkPath2();

  //  static void encodeInkPath1();
  //  static void encodeInkPath2();

private:

  typedef std::pair<std::vector<quint8>,quint8> pair_t ;
  /**
   * @brief unsignedTestData
   *
   * key: expected value
   * value.first: test data
   * value.second: expected bytesread
   */
  static const std::map<quint64, std::pair<std::vector<quint8>,quint8>>
      unsignedTestData;
  static const std::map<qint64, std::pair<std::vector<quint8>,quint8>>
      signedTestData;
};

#endif // MULTIBYTEENCODINGTEST_H
