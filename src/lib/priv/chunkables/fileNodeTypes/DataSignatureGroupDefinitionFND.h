#ifndef DATASIGNATUREGROUPDEFINITIONFND_H
#define DATASIGNATUREGROUPDEFINITIONFND_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"

namespace libmson {
namespace priv {

class DataSignatureGroupDefinitionFND
    : public IFileNodeType
    , public IStreamable {
private:
  ExtendedGUID m_dataSignatureGroup;

public:
  DataSignatureGroupDefinitionFND(FileNode_WPtr_t parentFileNode);
  virtual ~DataSignatureGroupDefinitionFND() = default;

  ExtendedGUID dataSignatureGroup() const;
  void setDataSignatureGroup(const ExtendedGUID& DataSignatureGroup);

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;


  static constexpr const quint64 sizeInFile = ExtendedGUID::getSizeInFile();
};

} // namespace priv
} // namespace libmson

#endif // DATASIGNATUREGROUPDEFINITIONFND_H
