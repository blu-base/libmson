#ifndef DATASIGNATUREGROUPDEFINITIONFND_H
#define DATASIGNATUREGROUPDEFINITIONFND_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"

class DataSignatureGroupDefinitionFND : public IFileNodeType {
public:
  DataSignatureGroupDefinitionFND();

  ExtendedGUID m_dataSignatureGroup;

  ExtendedGUID dataSignatureGroup() const;
  void setDataSignatureGroup(const ExtendedGUID &DataSignatureGroup);

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // DATASIGNATUREGROUPDEFINITIONFND_H
