#ifndef PROPERTYTYPE_ARRAYOFCONTEXTIDS_H
#define PROPERTYTYPE_ARRAYOFCONTEXTIDS_H

#include "../commonTypes/CompactID.h"
#include "IPropertyType.h"
#include <QByteArray>
#include <QtCore/qglobal.h>
#include <vector>

namespace libmson{
namespace priv{

/// \todo data structure not clear yet, does it only contain CompactIDs?
class PropertyType_ArrayNumber : public IPropertyType {
private:
  quint32 m_cCIDs;

public:
  PropertyType_ArrayNumber();

  quint32 cCIDs() const;
  void setCCIDs(const quint32 &cCIDs);

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;





  static const quint64 sizeInFile = 4;
};

} //namespace priv
} // namespace libmson

#endif // PROPERTYTYPE_ARRAYOFCONTEXTIDS_H
