#ifndef OBJECTINFODEPENDENCYOVERRIDESFND_H
#define OBJECTINFODEPENDENCYOVERRIDESFND_H

#include "../Chunkable.h"
#include "../ObjectInfoDependencyOverrideData.h"
#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {


/// \todo deal with local/remote content of ObjectInfoDependencyOverridesFND
class ObjectInfoDependencyOverridesFND : public IFileNodeType {
private:
  ObjectInfoDependencyOverrideData_WPtr_t m_ref;

  ObjectInfoDependencyOverrideData m_data;

public:
  ObjectInfoDependencyOverridesFND(FileNode_WPtr_t parentFileNode);
  virtual ~ObjectInfoDependencyOverridesFND() = default;

  /**
   * @brief container
   * @var data
   * the container is located somewhere in the file, specified by ref.
   * If ref is fcrNil, then data tails ref in the stream
   */
  ObjectInfoDependencyOverrideData_WPtr_t getRef() const;
  void setRef(const ObjectInfoDependencyOverrideData_WPtr_t value);

  ObjectInfoDependencyOverrideData getData() const;
  void setData(const ObjectInfoDependencyOverrideData& value);
  void setData(ObjectInfoDependencyOverrideData_WPtr_t remote);

  virtual quint64 getSizeInFile() const override;

  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;

  // private:
  //  virtual void deserialize(QDataStream& ds) override;
  //  virtual void serialize(QDataStream& ds) const override;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTINFODEPENDENCYOVERRIDESFND_H
