#ifndef PRTARRAYOFPROPERTYVALUES_H
#define PRTARRAYOFPROPERTYVALUES_H

#include "PropertyID.h"
#include <QByteArray>
#include <QDataStream>
#include <QtCore/qglobal.h>
#include <vector>

#include "IPropertyType.h"
#include "PropertySet.h"

namespace MSONcommon {

class prtArrayOfPropertyValues : public IPropertyType {
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

  std::vector<PropertySet> m_dataVector;

public:
  prtArrayOfPropertyValues() = default;
  virtual ~prtArrayOfPropertyValues() = default;

  friend QDebug operator<<(QDebug dbg, const prtArrayOfPropertyValues &obj);

  quint32 cProperties() const;
  void setCProperties(const quint32 &cProperties);

  PropertyID prid() const;
  void setPrid(const PropertyID &prid);

  std::vector<PropertySet> dataVector() const;
  void setDataVector(const std::vector<PropertySet> &dataVector);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // PRTARRAYOFPROPERTYVALUES_H
