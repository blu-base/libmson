#ifndef OBJECTINFODEPENDENCYOVERRIDEDATA_H
#define OBJECTINFODEPENDENCYOVERRIDEDATA_H

#include <QtCore/qglobal.h>

#include "Chunkable.h"

#include "objectTypes/ObjectInfoDependencyOverride32.h"
#include "objectTypes/ObjectInfoDependencyOverride8.h"

#include "../IStreamable.h"

namespace libmson {
namespace priv {

class ObjectInfoDependencyOverrideData
    : public IStreamable
    , public Chunkable {
private:
  /**
   * @brief number of elements in m_Overrides1.
   */
  quint32 m_c8BitOverrides;

  /**
   * @brief number of elements in m_Overrides2.
   */
  quint32 m_c32BitOverrides;

  /// \todo crc explain from spec
  quint32 m_crc;

  /**
   * @brief specifies the updated reference counts for objects (section 2.1.5)
   * if the updated reference count is less than or equal to 255.
   */
  std::vector<ObjectInfoDependencyOverride8> m_Overrides1;

  /**
   * @brief pecifies the updated reference counts for objects if the updated
   * reference count is greater than 255
   */
  std::vector<ObjectInfoDependencyOverride32> m_Overrides2;

public:
  ObjectInfoDependencyOverrideData(
      const quint64 initialStp = 0, const quint64 initialCb = 0);

  quint32 c8BitOverrides() const;
  void setC8BitOverrides(const quint32& c8BitOverrides);

  quint32 c32BitOverrides() const;
  void setC32BitOverrides(const quint32& c32BitOverrides);

  quint32 crc() const;
  void setCrc(const quint32& crc);

  std::vector<ObjectInfoDependencyOverride8> Overrides1() const;
  void
  setOverrides1(const std::vector<ObjectInfoDependencyOverride8>& Overrides1);

  std::vector<ObjectInfoDependencyOverride32> Overrides2() const;
  void
  setOverrides2(const std::vector<ObjectInfoDependencyOverride32>& Overrides2);

  quint64 getSizeInFile() const;

  friend class RevisionStoreFileWriter;
  friend class RevisionStoreFileParser;


private:
  // Chunkable interface
  virtual quint64 cb() const override;
  virtual RevisionStoreChunkType getType() const override;
  /**
   * @brief creates ObjectInfoDependencyOverrideData from QDataStream
   * @param ds <QDataStream> containing the deserializable
   * ObjectInfoDependencyOverrideData
   *
   * Note, that only 4GB of an ObjectInfoDependencyOverrideData can be parsed
   * because an limitation of QByteArray
   */
  virtual void deserialize(QDataStream& ds) override;
  /**
   * @brief creates byte stream from ObjectInfoDependencyOverrideData object
   * @param ds <QDataStream> is the output stream to which the serialized
   * ObjectInfoDependencyOverrideData is send
   *

   */
  virtual void serialize(QDataStream& ds) const override;


  static const quint64 sizeInFileBase;
};

typedef std::shared_ptr<ObjectInfoDependencyOverrideData>
    ObjectInfoDependencyOverrideData_SPtr_t;
typedef std::weak_ptr<ObjectInfoDependencyOverrideData>
    ObjectInfoDependencyOverrideData_WPtr_t;

} // namespace priv
} // namespace libmson

#endif // OBJECTINFODEPENDENCYOVERRIDEDATA_H
