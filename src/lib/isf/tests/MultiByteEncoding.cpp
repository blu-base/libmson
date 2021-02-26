#include "MultiByteEncoding.h"

#include <MultiByteEncoding.h>
#include <QBuffer>
#include <map>

using namespace libmson::isf;

const std::map<quint64, std::pair<std::vector<quint8>, quint8>>
    MultiByteEncodingTest::unsignedTestData = {
        {0, {{0x00}, 1}},
        {1, {{0x01}, 1}},
        {0x71, {{0x71}, 1}},
        {0x82, {{0x82, 0x01}, 2}},
        {0x4003, {{0x83, 0x80, 0x01}, 3}},
        {0x200004, {{0x84, 0x80, 0x80, 0x01}, 4}},
        {0x10000005, {{0x85, 0x80, 0x80, 0x80, 0x01}, 5}},
        {0x800000006, {{0x86, 0x80, 0x80, 0x80, 0x80, 0x01}, 6}},
        {0x40000000007, {{0x87, 0x80, 0x80, 0x80, 0x80, 0x80, 0x01}, 7}},
        {0x2000000000008,
         {{0x88, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x01}, 8}},
        {0x100000000000009,
         {{0x89, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x01}, 9}},
        {0x800000000000000a,
         {{0x8a, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x01}, 10}},

        // Too large for value but valid
        {0x82, {{0x12, 0x11, 0x00}, 3}},

        // Invalid input to check fail safe
        {0, {{0x80}, 0}},
        {0,
         {{0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
          0}},
};

const std::map<qint64, std::pair<std::vector<quint8>, quint8>>
    MultiByteEncodingTest::signedTestData = {
        {0u, {{0x00}, 1}},
        {1, {{0x02}, 1}},
        {-1, {{0x03}, 1}},
        {0x20, {{0x40}, 1}},
        {-0x20, {{0x41}, 1}},
        {0x1000, {{0x80, 0x40}, 2}},
        {-0x1000, {{0x81, 0x40}, 2}},
        {0x80000, {{0x80, 0x80, 0x40}, 3}},
        {-0x80000, {{0x81, 0x80, 0x40}, 3}},
        {0x4000000, {{0x80, 0x80, 0x80, 0x40}, 4}},
        {-0x4000000, {{0x81, 0x80, 0x80, 0x40}, 4}},
        {0x200000000, {{0x80, 0x80, 0x80, 0x80, 0x40}, 5}},
        {-0x200000000, {{0x81, 0x80, 0x80, 0x80, 0x40}, 5}},
        {0x10000000000, {{0x80, 0x80, 0x80, 0x80, 0x80, 0x40}, 6}},
        {-0x10000000000, {{0x81, 0x80, 0x80, 0x80, 0x80, 0x40}, 6}},
        {0x800000000000, {{0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40}, 7}},
        {-0x800000000000, {{0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40}, 7}},
        {0x40000000000000,
         {{0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40}, 8}},
        {-0x40000000000000,
         {{0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40}, 8}},
        {0x2000000000000000,
         {{0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40}, 9}},
        {-0x2000000000000000,
         {{0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40}, 9}},
        {0x4000000000000000,
         {{0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x01}, 10}},
        {-0x4000000000000000,
         {{0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x01}, 10}},

        // Invalid

};

void MultiByteEncodingTest::decodeUIntFromByteArray()
{
  quint8 bytesread = 0;

  for (const auto& pair : unsignedTestData) {
    const auto& valuePair = pair.second;

    // prepare challenge
    const QByteArray input = QByteArray::fromRawData(
        reinterpret_cast<const char*>(valuePair.first.data()),
        valuePair.first.size());
    const quint64 expected = pair.first;

    quint64 actual = MultiByteEncoding::decodeUInt(input, &bytesread);
    QCOMPARE(actual, expected);
    QCOMPARE(bytesread, valuePair.second);
  }
}

void MultiByteEncodingTest::decodeUIntFromStream()
{
  for (const auto& pair : unsignedTestData) {
    const auto& valuePair = pair.second;

    // prepare challenge
    const QByteArray input = QByteArray::fromRawData(
        reinterpret_cast<const char*>(valuePair.first.data()),
        valuePair.first.size());
    QDataStream ds(input);

    const quint64 expected = pair.first;

    quint64 actual = MultiByteEncoding::decodeUInt(ds);
    QCOMPARE(actual, expected);
  }
}

void MultiByteEncodingTest::decodeIntFromByteArray()
{
  for (const auto& pair : signedTestData) {
    const auto& valuePair = pair.second;

    // test only the valid cases
    if (valuePair.second != 0) {
      quint8 bytesread = 0;

      // prepare challenge
      const QByteArray input = QByteArray::fromRawData(
          reinterpret_cast<const char*>(valuePair.first.data()),
          valuePair.first.size());
      const qint64 expected = pair.first;

      qint64 actual = MultiByteEncoding::decodeInt(input, &bytesread);

      QCOMPARE(actual, expected);
    }
  }
}

void MultiByteEncodingTest::decodeIntFromStream()
{
  for (const auto& pair : signedTestData) {
    const auto& valuePair = pair.second;

    // test only the valid cases
    if (valuePair.second != 0) {
      // prepare challenge
      const QByteArray input = QByteArray::fromRawData(
          reinterpret_cast<const char*>(valuePair.first.data()),
          valuePair.first.size());
      QDataStream ds(input);

      const qint64 expected = pair.first;

      qint64 actual = MultiByteEncoding::decodeInt(ds);
      QCOMPARE(actual, expected);
    }
  }
}

void MultiByteEncodingTest::encodeUIntToByteArray()
{
  for (const auto& pair : unsignedTestData) {
    const auto& valuePair = pair.second;

    // test only the valid cases
    if (valuePair.second != 0) {

      // prepare challenge
      const QByteArray expected = QByteArray::fromRawData(
          reinterpret_cast<const char*>(valuePair.first.data()),
          valuePair.first.size());
      const quint64 input = pair.first;

      const QByteArray actual = MultiByteEncoding::encodeUInt(input);

      QCOMPARE(actual, expected);
    }
  }
}

void MultiByteEncodingTest::encodeUIntToStream()
{
  for (const auto& pair : unsignedTestData) {
    const auto& valuePair = pair.second;

    // test only the valid cases
    if (valuePair.second != 0) {

      // prepare challenge
      const QByteArray expected = QByteArray::fromRawData(
          reinterpret_cast<const char*>(valuePair.first.data()),
          valuePair.first.size());
      const quint64 input = pair.first;

      QByteArray actual;
      QDataStream ds(&actual, QIODevice::WriteOnly);

      MultiByteEncoding::encodeUInt(input, ds);

      QCOMPARE(actual, expected);
    }
  }
}

void MultiByteEncodingTest::encodeIntToByteArray()
{
  for (const auto& pair : signedTestData) {
    const auto& valuePair = pair.second;


    // prepare challenge
    const QByteArray expected = QByteArray::fromRawData(
        reinterpret_cast<const char*>(valuePair.first.data()),
        valuePair.first.size());
    const qint64 input = pair.first;

    const QByteArray actual = MultiByteEncoding::encodeInt(input);

    QCOMPARE(actual, expected);
  }
}

void MultiByteEncodingTest::encodeIntToStream()
{
  for (const auto& pair : signedTestData) {
    const auto& valuePair = pair.second;

    // prepare challenge
    const QByteArray expected = QByteArray::fromRawData(
        reinterpret_cast<const char*>(valuePair.first.data()),
        valuePair.first.size());
    const qint64 input = pair.first;

    QByteArray actual;
    QDataStream ds(&actual, QIODevice::WriteOnly);

    MultiByteEncoding::encodeInt(input, ds);

    QCOMPARE(actual, expected);
  }
}

// void MultiByteEncodingTest::decodeInkPath1() {}

// void MultiByteEncodingTest::decodeInkPath2() {}

// void MultiByteEncodingTest::encodeInkPath1() {}

// void MultiByteEncodingTest::encodeInkPath2() {}

QTEST_MAIN(MultiByteEncodingTest)
//#include "MultiByteEncoding.moc"
