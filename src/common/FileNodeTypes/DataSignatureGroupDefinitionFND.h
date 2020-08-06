#ifndef DATASIGNATUREGROUPDEFINITIONFND_H
#define DATASIGNATUREGROUPDEFINITIONFND_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"

class DataSignatureGroupDefinitionFND : public IFileNodeType {
private:
      ExtendedGUID m_dataSignatureGroup;
public:
  DataSignatureGroupDefinitionFND();



  ExtendedGUID dataSignatureGroup() const;
  void setDataSignatureGroup(const ExtendedGUID &DataSignatureGroup);

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;

  // IFileNodeType interface
public:
  virtual void generateXml(QXmlStreamWriter& xmlWriter) const override;
};

#endif // DATASIGNATUREGROUPDEFINITIONFND_H
