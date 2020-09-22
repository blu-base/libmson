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

   virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;

 static constexpr const quint64 sizeInFile = ExtendedGUID::getSizeInFile();

};

} // namespace MSONcommon

#endif // DATASIGNATUREGROUPDEFINITIONFND_H
