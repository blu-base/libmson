#ifndef PROPERTYTYPE_CONTEXTID_H
#define PROPERTYTYPE_CONTEXTID_H

#include "../commonTypes/CompactID.h"
#include "IPropertyType.h"
#include <QByteArray>
#include <QtCore/qglobal.h>

namespace MSONcommon {

class PropertyType_ContextID : public IPropertyType {
private:
  CompactID m_data;

public:
  PropertyType_ContextID();

  // IPropertyType interface
  CompactID data() const;
  void setData(const CompactID &data);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // PROPERTYTYPE_CONTEXTID_H
