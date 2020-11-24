#ifndef PROPERTYTYPE_ARRAYOFOBJECTIDS_H
#define PROPERTYTYPE_ARRAYOFOBJECTIDS_H

#include "../commonTypes/CompactID.h"
#include "IPropertyType.h"
#include <QByteArray>
#include <QtCore/qglobal.h>
#include <vector>

namespace libmson{
namespace priv{

class PropertyType_ArrayOfObjectIDs : public IPropertyType {
private:
  quint32 m_cCIDs;
  std::vector<CompactID> m_data;

public:
  PropertyType_ArrayOfObjectIDs();

  // IPropertyType interface
  std::vector<CompactID> data() const;
  void setData(const std::vector<CompactID> &data);

  quint32 cCIDs() const;
  void setCCIDs(const quint32 &cCIDs);

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;




};

} //namespace priv
} // namespace libmson

#endif // PROPERTYTYPE_ARRAYOFOBJECTIDS_H