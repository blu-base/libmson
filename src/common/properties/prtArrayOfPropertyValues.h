#ifndef PRTARRAYOFPROPERTYVALUES_H
#define PRTARRAYOFPROPERTYVALUES_H

#include "PropertyID.h"
#include <QByteArray>
#include <QDataStream>
#include <QtCore/qglobal.h>
#include <vector>

#include "IPropertyType.h"
#include "PropertySet.h"

class prtArrayOfPropertyValues {
private:
  /**
   * @brief how many Property elements in this array
   */
  quint32 m_cProperties;

  /**
   * @brief specifies the PropertyID of all elements in this array, only
   * present if m_cProperties is not 0;
   *
   */
  PropertyID m_prid;

  QByteArray m_Data;

  std::vector<PropertySet> m_dataVector;

public:
  prtArrayOfPropertyValues();

  friend QDataStream &operator<<(QDataStream &ds,
                                 const prtArrayOfPropertyValues &obj);
  friend QDataStream &operator>>(QDataStream &ds,
                                 prtArrayOfPropertyValues &obj);

  friend QDebug operator<<(QDebug dbg, const prtArrayOfPropertyValues &obj);

  quint32 cProperties() const;
  void setCProperties(const quint32 &cProperties);

  PropertyID prid() const;
  void setPrid(const PropertyID &prid);

  QByteArray Data() const;
  void setData(const QByteArray &Data);

  std::vector<PropertySet> dataVector() const;
  void setDataVector(const std::vector<PropertySet> &dataVector);

private:
  void deserialize(QDataStream &ds);
  void serialize(QDataStream &ds) const;
  void toDebugString(QDebug dbg) const;
};

#endif // PRTARRAYOFPROPERTYVALUES_H
