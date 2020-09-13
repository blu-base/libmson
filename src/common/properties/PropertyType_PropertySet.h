#ifndef PROPERTYTYPE_PROPERTYSET_H
#define PROPERTYTYPE_PROPERTYSET_H

#include "IPropertyType.h"
#include "PropertySet.h"
#include <QByteArray>
#include <QtCore/qglobal.h>

namespace MSONcommon {

class PropertyType_PropertySet : public IPropertyType {
private:
  PropertySet m_data;

public:
  PropertyType_PropertySet();

  PropertySet data() const;
  void setData(const PropertySet &data);

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // PROPERTYTYPE_PROPERTYSET_H
