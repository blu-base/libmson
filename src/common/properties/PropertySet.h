#ifndef PROPERTYSET_H
#define PROPERTYSET_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDebug>
#include <vector>

#include "PropertyID.h"
class PropertySet {
private:
  /**
   * @brief number of PropertyIDs in this Set
   */
  quint32 m_cProperties;

  /**
   * @brief vector of PropertyID objects in this Set
   */
  std::vector<PropertyID> m_rgPrids;

  /**
   * @brief ByteStream which contains the data associated to the PropertyIDs in
   * m_rgPrids
   */
  QByteArray m_rgData;

public:
  PropertySet();

  friend QDataStream &operator<<(QDataStream &ds, const PropertySet &obj);
  friend QDataStream &operator>>(QDataStream &ds, PropertySet &obj);
  friend QDebug operator<<(QDebug dbg, const PropertySet &obj);

  quint32 cProperties() const;
  void setCProperties(const quint32 &cProperties);

  std::vector<PropertyID> rgPrids() const;
  void setRgPrids(const std::vector<PropertyID> &rgPrids);

  QByteArray rgData() const;
  void setRgData(const QByteArray &rgData);

private:
  void deserialize(QDataStream &ds);
  void serialize(QDataStream &ds) const;
  void toDebugString(QDebug dbg) const;
};

#endif // PROPERTYSET_H
