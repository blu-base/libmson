#ifndef OBJECTDECLARATION2BODY_H
#define OBJECTDECLARATION2BODY_H

#include <QtCore/qglobal.h>

#include "../commonTypes/CompactID.h"
#include "JCID.h"

class ObjectDeclaration2Body {
public:
  ObjectDeclaration2Body();

  CompactID oid;
  JCID jcid;

  bool fHasOidReferences;
  bool fHasOsidReferences;

  quint8 fReserved2;

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

  friend QDataStream &operator<<(QDataStream &ds,
                                 const ObjectDeclaration2Body &obj);
  friend QDataStream &operator>>(QDataStream &ds, ObjectDeclaration2Body &obj);
  friend QDebug operator<<(QDebug dbg, const ObjectDeclaration2Body &obj);

private:
  /**
   * @brief creates ObjectDeclaration2Body from QDataStream
   * @param ds <QDataStream> containing the deserializable
   * ObjectDeclaration2Body
   */
  void deserialize(QDataStream &ds);
  /**
   * @brief creates byte stream from ObjectDeclaration2Body object
   * @param ds <QDataStream> is the output stream to which the serialized
   * ObjectDeclaration2Body is send
   */
  void serialize(QDataStream &ds) const;

  /**
   * @brief prints the ObjectDeclaration2Body to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  void toDebugString(QDebug dbg) const;
};

#endif // OBJECTDECLARATION2BODY_H
