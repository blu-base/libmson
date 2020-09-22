#ifndef PROPERTYSET_H
#define PROPERTYSET_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDebug>
#include <QXmlStreamWriter>
#include <vector>

#include "IPropertyType.h"
#include "PropertyID.h"
#include "../IRevisionStoreFileObject.h"


namespace MSONcommon {

class PropertySet : public IRevisionStoreFileObject {
private:
  /**
   * @brief number of PropertyIDs in this Set
   */
  quint16 m_cProperties;

  /**
   * @brief vector of PropertyID objects in this Set
   */
  std::vector<PropertyID> m_rgPrids;

  /**
   * @brief vector which contains the data associated to the PropertyIDs in
   * m_rgPrids
   */
  std::vector<std::shared_ptr<IPropertyType>> m_rgData;

public:
  PropertySet();

  quint16 cProperties() const;
  void setCProperties(const quint16 &cProperties);

  std::vector<PropertyID> rgPrids() const;
  void setRgPrids(const std::vector<PropertyID> &rgPrids);

 std::vector<std::shared_ptr<IPropertyType>> rgData() const;
  void setRgData(const std::vector<std::shared_ptr<IPropertyType>> &rgData);

  quint64 getSizeInFile() const;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;
};

} // namespace MSONcommon

#endif // PROPERTYSET_H
