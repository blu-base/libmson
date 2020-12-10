#ifndef OBJECTINFODEPENDENCYOVERRIDE8_H
#define OBJECTINFODEPENDENCYOVERRIDE8_H

#include "../../commonTypes/CompactID.h"
#include <QtCore/qglobal.h>

#include "../../IStreamable.h"

namespace libmson {
namespace priv {

class ObjectInfoDependencyOverride8 : public IStreamable {
private:
  /**
   * @brief the identity of the object with the updated reference count.
   * The object MUST already be defined in the current revision (section 2.1.8).
   */
  CompactID m_oid;

  /**
   * @brief specifies the updated reference count for an oid field
   */
  quint8 m_cRef;

public:
  ObjectInfoDependencyOverride8() = default;

  CompactID getOid() const;
  void setOid(const CompactID& oid);

  quint8 getCRef() const;
  void setCRef(const quint8& cRef);

  static quint64 getSizeInFile() { return 5; }

  static const quint64 sizeInFile = 5;


private:
  /**
   * @brief creates ObjectInfoDependencyOverride8 from QDataStream
   * @param ds <QDataStream> containing the deserializable
   * ObjectInfoDependencyOverride8
   *
   * Note, that only 4GB of an ObjectInfoDependencyOverride8 can be parsed
   * because an limitation of QByteArray
   */
  virtual void deserialize(QDataStream& ds) override;
  /**
   * @brief creates byte stream from ObjectInfoDependencyOverride8 object
   * @param ds <QDataStream> is the output stream to which the serialized
   * ObjectInfoDependencyOverride8 is send
   *
   */
  virtual void serialize(QDataStream& ds) const override;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTINFODEPENDENCYOVERRIDE8_H
