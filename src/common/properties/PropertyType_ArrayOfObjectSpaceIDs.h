#ifndef PROPERTYTYPE_ARRAYOFOBJECTSPACEIDS_H
#define PROPERTYTYPE_ARRAYOFOBJECTSPACEIDS_H

#include "../commonTypes/CompactID.h"
#include "IPropertyType.h"
#include <QByteArray>
#include <QtCore/qglobal.h>

namespace MSONcommon {

class PropertyType_ArrayOfObjectSpaceIDs : public IPropertyType {
private:
  quint32 m_cCIDs;
  std::vector<CompactID> m_data;

public:
  PropertyType_ArrayOfObjectSpaceIDs();

  // IPropertyType interface
  std::vector<CompactID> data() const;
  void setData(const std::vector<CompactID> &data);

  quint32 cCIDs() const;
  void setCCIDs(const quint32 &cCIDs);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // PROPERTYTYPE_ARRAYOFOBJECTSPACEIDS_H
