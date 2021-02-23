#ifndef METRICTABLE_H
#define METRICTABLE_H

#include <QtCore/qglobal.h>
#include <vector>

#include "MetricBlockEntry.h"

namespace libmson::isf {

class MetricTable {
public:
  MetricTable();
  MetricTable(std::vector<MetricBlockEntry> entries);

  MetricTable(QDataStream& ds);
  MetricTable(const QByteArray& ba);

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
