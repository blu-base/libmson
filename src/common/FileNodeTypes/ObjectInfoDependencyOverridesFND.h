#ifndef OBJECTINFODEPENDENCYOVERRIDESFND_H
#define OBJECTINFODEPENDENCYOVERRIDESFND_H

#include "../commonTypes/FileNodeChunkReference.h"
#include "../otherTypes/ObjectInfoDependencyOverrideData.h"

#include "IFileNodeType.h"

#include <QtCore/qglobal.h>

namespace MSONcommon {

class ObjectInfoDependencyOverridesFND : public IFileNodeType {
private:
  FileNodeChunkReference m_ref;

  ObjectInfoDependencyOverrideData m_data;

public:
  ObjectInfoDependencyOverridesFND(FNCR_STP_FORMAT stpFormat,
                                   FNCR_CB_FORMAT cbFormat);
  ObjectInfoDependencyOverridesFND(quint8 stpFormat, quint8 cbFormat);
  ~ObjectInfoDependencyOverridesFND();

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

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // OBJECTINFODEPENDENCYOVERRIDESFND_H
