#ifndef PROPERTYSET_H
#define PROPERTYSET_H

#include <QtCore/qglobal.h>

#include <vector>

#include "../IStreamable.h"
#include "IPropertyType.h"
#include "PropertyID.h"


namespace libmson {
namespace priv {

class PropertySet : public IStreamable {
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
  std::vector<IPropertyType_SPtr_t> m_rgData;

public:
  PropertySet();

  quint16 cProperties() const;
  void setCProperties(const quint16& cProperties);

  std::vector<PropertyID> rgPrids() const;
  void setRgPrids(const std::vector<PropertyID>& rgPrids);

  std::vector<IPropertyType_SPtr_t> rgData() const;
  void setRgData(const std::vector<IPropertyType_SPtr_t>& rgData);

  quint64 getSizeInFile() const;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

} // namespace priv
} // namespace libmson

#endif // PROPERTYSET_H
