#ifndef DATASIGNATUREGROUPDEFINITIONFND_H
#define DATASIGNATUREGROUPDEFINITIONFND_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"

namespace MSONcommon {

class DataSignatureGroupDefinitionFND : public IFileNodeType {
private:
  ExtendedGUID m_dataSignatureGroup;

public:
  DataSignatureGroupDefinitionFND();

  ExtendedGUID dataSignatureGroup() const;
  void setDataSignatureGroup(const ExtendedGUID &DataSignatureGroup);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // DATASIGNATUREGROUPDEFINITIONFND_H
