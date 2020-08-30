#ifndef PROPERTYTYPE_ARRAYOFCONTEXTIDS_H
#define PROPERTYTYPE_ARRAYOFCONTEXTIDS_H

#include "../commonTypes/CompactID.h"
#include "IPropertyType.h"
#include <QByteArray>
#include <QtCore/qglobal.h>
#include <vector>

/// \todo data structure not clear yet, does it only contain CompactIDs?
class PropertyType_ArrayNumber : public IPropertyType {
private:
  quint32 m_cCIDs;

public:
  PropertyType_ArrayNumber();

  quint32 cCIDs() const;
  void setCCIDs(const quint32 &cCIDs);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // PROPERTYTYPE_ARRAYOFCONTEXTIDS_H
