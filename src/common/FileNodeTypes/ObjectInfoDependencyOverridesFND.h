#ifndef OBJECTINFODEPENDENCYOVERRIDESFND_H
#define OBJECTINFODEPENDENCYOVERRIDESFND_H

#include <QtCore/qglobal.h>
#include "IFileNodeType.h"
#include "../commonTypes/FileNodeChunkReference.h"
#include "../otherTypes/ObjectInfoDependencyOverrideData.h"

class ObjectInfoDependencyOverridesFND : public IFileNodeType
{
public:
  ObjectInfoDependencyOverridesFND(FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat);
  ObjectInfoDependencyOverridesFND(quint8 stpFormat, quint8 cbFormat);
  ~ObjectInfoDependencyOverridesFND();

  FileNodeChunkReference ref;


  /**
   * @brief container
   * @var data
   * the container is located somewhere in the file, specified by ref.
   * If ref is fcrNil, then data tails ref in the stream
   */
  ObjectInfoDependencyOverrideData data;


  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference& value);

  ObjectInfoDependencyOverrideData getData() const;
  void setData(const ObjectInfoDependencyOverrideData& value);

private:
  void deserialize(QDataStream& ds) override;
  void serialize(QDataStream& ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // OBJECTINFODEPENDENCYOVERRIDESFND_H
