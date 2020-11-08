#ifndef OBJECTINFODEPENDENCYOVERRIDESFND_H
#define OBJECTINFODEPENDENCYOVERRIDESFND_H

#include "../../commonTypes/FileNodeChunkReference.h"
#include "../../objectTypes/ObjectInfoDependencyOverrideData.h"

#include "IFileNodeType.h"

#include <QtCore/qglobal.h>

namespace libmson{
namespace priv{

class ObjectInfoDependencyOverridesFND : public IFileNodeType {
private:
  FileNodeChunkReference m_ref;

  ObjectInfoDependencyOverrideData m_data;

public:
  ObjectInfoDependencyOverridesFND(FNCR_STP_FORMAT stpFormat,
                                   FNCR_CB_FORMAT cbFormat);
  ObjectInfoDependencyOverridesFND(quint8 stpFormat, quint8 cbFormat);
  virtual ~ObjectInfoDependencyOverridesFND() = default;

  /**
   * @brief container
   * @var data
   * the container is located somewhere in the file, specified by ref.
   * If ref is fcrNil, then data tails ref in the stream
   */

  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &value);

  ObjectInfoDependencyOverrideData getData() const;
  void setData(const ObjectInfoDependencyOverrideData &value);

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;




};

} //namespace priv
} // namespace libmson

#endif // OBJECTINFODEPENDENCYOVERRIDESFND_H
