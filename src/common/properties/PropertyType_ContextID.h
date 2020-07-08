#ifndef PROPERTYTYPE_CONTEXTID_H
#define PROPERTYTYPE_CONTEXTID_H

#include "../commonTypes/CompactID.h"
#include "IPropertyType.h"
#include <QByteArray>
#include <QtCore/qglobal.h>

class PropertyType_ContextID : public IPropertyType {
private:
  CompactID m_data;

public:
  PropertyType_ContextID();

  // IPropertyType interface
  CompactID data() const;
  void setData(const CompactID &data);

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // PROPERTYTYPE_CONTEXTID_H
