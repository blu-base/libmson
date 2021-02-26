#ifndef METRICBLOCKENTRY_H
#define METRICBLOCKENTRY_H

#include <QtCore/qglobal.h>

#include "MetricEnums.h"

namespace libmson::isf {


/**
 * @brief A MetricBlockEntry is an entry in the MetricTable class
 *
 * An implementation of the
 *
 * https://docs.microsoft.com/de-de/uwp/specifications/ink-serialized-format#metric-table
 *
 */
class MetricBlockEntry {
public:
  /**
   * @brief initialize MetricBlockEntry to 'invalid' state
   */
  MetricBlockEntry();
  /**
   * @brief Intialize MetricBlockEntry with type and default properties
   *
   * min is set to INT32_MIN.
   * max is set to INT32_MAX
   * unit is set to DEFAULT
   * resolution is set to 1000
   *
   * @param type
   */
  MetricBlockEntry(MetricBlockEntryType type);
  MetricBlockEntry(
      MetricBlockEntryType type, const qint32 min, const qint32 max,
      MetricUnit unit, float resolution);

  /**
   * @brief Initialize MetricBlockEntry from a byte array of size 32
   * @param ba should have the size of 32; following bytes will be ignored.
   */
  MetricBlockEntry(const QByteArray& ba);


  /**
   * @brief Initialite a MetricBlockEntry from a stream, reading the next 32
   * bytes
   * @param ds reads 32 bytes from the stream
   */
  MetricBlockEntry(QDataStream& ds);


  MetricBlockEntryType getType() const;
  void setType(const MetricBlockEntryType& type);

  QString getTypeString() const;

  qint32 getMin() const;
  qint32 getMax() const;

  /**
   * @brief setMinMax
   *
   *
   *
   * If the min is larger than max, min will be set to zero.
   * if max is zero, it will be set to  INT32_MAX
   *
   * @param min must be smaller than max
   * @param max must be bigger than min, and non-zero
   */
  void setMinMax(qint32 min, qint32 max);


  MetricUnit getUnit() const;
  void setUnit(const MetricUnit& unit);

  QString getUnitString() const;

  float getResolution() const;
  void setResolution(float resolution);

  friend QDataStream& operator<<(QDataStream& ds, const MetricBlockEntry& obj);

  friend QDataStream& operator>>(QDataStream& ds, MetricBlockEntry& obj);

private:
  MetricBlockEntryType m_type;

  qint32 m_min;
  qint32 m_max;
  MetricUnit m_unit;
  float m_resolution;


private:
  void deserialize(QDataStream& ds);
  void serialize(QDataStream& ds) const;
};

} // namespace libmson::isf

#endif // METRICBLOCKENTRY_H
