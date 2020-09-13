#ifndef OBJECTINFODEPENDENCYOVERRIDEDATA_H
#define OBJECTINFODEPENDENCYOVERRIDEDATA_H

#include <QtCore/qglobal.h>

#include <QXmlStreamWriter>

#include "ObjectInfoDependencyOverride32.h"
#include "ObjectInfoDependencyOverride8.h"

#include "../IRevisionStoreFileObject.h"

namespace MSONcommon {

class ObjectInfoDependencyOverrideData : public IRevisionStoreFileObject {
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
  ObjectInfoDependencyOverrideData();

  quint32 c8BitOverrides() const;
  void setC8BitOverrides(const quint32 &c8BitOverrides);

  quint32 c32BitOverrides() const;
  void setC32BitOverrides(const quint32 &c32BitOverrides);

  quint32 crc() const;
  void setCrc(const quint32 &crc);

  std::vector<ObjectInfoDependencyOverride8> Overrides1() const;
  void
  setOverrides1(const std::vector<ObjectInfoDependencyOverride8> &Overrides1);

  std::vector<ObjectInfoDependencyOverride32> Overrides2() const;
  void
  setOverrides2(const std::vector<ObjectInfoDependencyOverride32> &Overrides2);

private:
  /**
   * @brief creates ObjectInfoDependencyOverrideData from QDataStream
   * @param ds <QDataStream> containing the deserializable
   * ObjectInfoDependencyOverrideData
   *
   * Note, that only 4GB of an ObjectInfoDependencyOverrideData can be parsed
   * because an limitation of QByteArray
   */
  virtual void deserialize(QDataStream &ds) override;
  /**
   * @brief creates byte stream from ObjectInfoDependencyOverrideData object
   * @param ds <QDataStream> is the output stream to which the serialized
   * ObjectInfoDependencyOverrideData is send
   *

   */
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  /**
   * @brief prints the ObjectInfoDependencyOverrideData to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  virtual void toDebugString(QDebug &dbg) const override;
};

} // namespace MSONcommon

#endif // OBJECTINFODEPENDENCYOVERRIDEDATA_H
