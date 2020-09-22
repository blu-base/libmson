#ifndef OBJECTINFODEPENDENCYOVERRIDE32_H
#define OBJECTINFODEPENDENCYOVERRIDE32_H

#include "../commonTypes/CompactID.h"
#include <QtCore/qglobal.h>

#include "../IRevisionStoreFileObject.h"

namespace MSONcommon {

class ObjectInfoDependencyOverride32 : public IRevisionStoreFileObject {
private:
  /**
   * @brief the identity of the object with the updated reference count.
   * The object MUST already be defined in the current revision (section 2.1.8).
   */
  CompactID m_oid;

  /**
   * @brief specifies the updated reference count for an oid field
   */
  quint32 m_cRef;

public:
  ObjectInfoDependencyOverride32() = default;

  CompactID oid() const;
  void setOid(const CompactID &oid);

  quint32 cRef() const;
  void setCRef(const quint32 &cRef);

  static quint64 getSizeInFile() { return sizeInFile; }

private:
  /**
   * @brief creates ObjectInfoDependencyOverride32 from QDataStream
   * @param ds <QDataStream> containing the deserializable
   * ObjectInfoDependencyOverride32
   *
   * Note, that only 4GB of an ObjectInfoDependencyOverride32 can be parsed
   * because an limitation of QByteArray
   */
  virtual void deserialize(QDataStream &ds) override;
  /**
   * @brief creates byte stream from ObjectInfoDependencyOverride32 object
   * @param ds <QDataStream> is the output stream to which the serialized
   * ObjectInfoDependencyOverride32 is send
   *
   */
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;
  /**
   * @brief prints the ObjectInfoDependencyOverride32 to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  virtual void toDebugString(QDebug &dbg) const override;

  static const quint64 sizeInFile = CompactID::getSizeInFile() + sizeof(m_cRef);
};

} // namespace MSONcommon

#endif // OBJECTINFODEPENDENCYOVERRIDE32_H
