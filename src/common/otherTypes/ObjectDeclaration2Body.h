#ifndef OBJECTDECLARATION2BODY_H
#define OBJECTDECLARATION2BODY_H

#include <QXmlStreamWriter>
#include <QtCore/qglobal.h>

#include "../commonTypes/CompactID.h"
#include "../properties/JCID.h"

#include "../IDeserializable.h"
#include "../ISerializable.h"

namespace MSONcommon {

class ObjectDeclaration2Body : public ISerializable, public IDeserializable {
private:
  CompactID m_oid;
  JCID m_jcid;

  bool m_fHasOidReferences;
  bool m_fHasOsidReferences;

  quint8 m_fReserved2;

public:
  ObjectDeclaration2Body();

  CompactID getOid() const;
  void setOid(const CompactID &value);
  JCID getJcid() const;
  void setJcid(const JCID &value);
  bool getFHasOidReferences() const;
  void setFHasOidReferences(bool value);
  bool getFHasOsidReferences() const;
  void setFHasOsidReferences(bool value);
  quint8 getFReserved2() const;
  void setFReserved2(const quint8 &value);

  friend QDebug operator<<(QDebug dbg, const ObjectDeclaration2Body &obj);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

private:
  /**
   * @brief creates ObjectDeclaration2Body from QDataStream
   * @param ds <QDataStream> containing the deserializable
   * ObjectDeclaration2Body
   */
  virtual void deserialize(QDataStream &ds) override;
  /**
   * @brief creates byte stream from ObjectDeclaration2Body object
   * @param ds <QDataStream> is the output stream to which the serialized
   * ObjectDeclaration2Body is send
   */
  virtual void serialize(QDataStream &ds) const override;

  /**
   * @brief prints the ObjectDeclaration2Body to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  void toDebugString(QDebug dbg) const;
};

} // namespace MSONcommon

#endif // OBJECTDECLARATION2BODY_H
