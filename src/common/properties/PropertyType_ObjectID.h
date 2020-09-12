#ifndef PROPERTYTYPE_OBJECTID_H
#define PROPERTYTYPE_OBJECTID_H

#include "../commonTypes/CompactID.h"
#include "IPropertyType.h"
#include <QByteArray>
#include <QtCore/qglobal.h>

namespace MSONcommon {

class PropertyType_ObjectID : public IPropertyType {
private:
  CompactID m_data;

public:
  PropertyType_ObjectID();


  CompactID data() const;
  void setData(const CompactID &data);

   virtual void generateXml(QXmlStreamWriter& xmlWriter) const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // PROPERTYTYPE_OBJECTID_H
