#ifndef METRICTABLE_H
#define METRICTABLE_H

#include <QtCore/qglobal.h>
#include <vector>

#include "MetricBlockEntry.h"

namespace libmson::isf {

/**
 * @brief Contains the dimension information of InkWords
 *
 * The binary structure shares similarities to the Metric table as described in
 * the Ink Serialized Format (ISF) Specification
 */
class MetricTable {
public:
  MetricTable();
  MetricTable(std::vector<MetricBlockEntry> entries);

  MetricTable(QDataStream& ds);
  MetricTable(const QByteArray& ba);

  /**
   * @brief returns the number of MetricBlockEntries in this instance
   * @return number of block entries
   */
  size_t size() const;

  std::vector<MetricBlockEntry>& entries();
  std::vector<MetricBlockEntry> getEntries() const;

  void setEntries(std::vector<MetricBlockEntry> entries);

  friend QDataStream& operator<<(QDataStream& ds, const MetricTable& obj);
  friend QDataStream& operator>>(QDataStream& ds, MetricTable& obj);

private:
  std::vector<MetricBlockEntry> m_entries;

private:
  void deserialize(QDataStream& ds);
  void serialize(QDataStream& ds) const;
};

} // namespace libmson::isf

#endif // METRICTABLE_H
