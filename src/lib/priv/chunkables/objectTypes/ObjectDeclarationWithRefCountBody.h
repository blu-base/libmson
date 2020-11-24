#ifndef OBJECTDECLARATIONWITHREFCOUNTBODY_H
#define OBJECTDECLARATIONWITHREFCOUNTBODY_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/CompactID.h"

namespace libmson {
namespace priv {

class CompactID;

class ObjectDeclarationWithRefCountBody : public IStreamable {
private:
  /**
   * @brief specifies the identity of this object
   */
  CompactID m_oid;

  /**
   * @brief specifies the value of the JCID.indexfield of the object. MUSTbe
   * 0x01
   */
  quint8 m_jci;

  /**
   * @brief specifies whether the data contained by this object is encrypted.
   *
   * MUST be zero
   * 4bits wide
   */
  quint8 m_odcs;

  /**
   * @brief MUST be zero, and MUST be ignored
   *
   * 2bits wide
   */
  quint8 m_fReserved1;

  /**
   * @brief Specifies whether this object contains references to other objects.
   */
  bool m_fHasOidReferences;

  /**
   * @brief Specifies whether this object contains references to object
   * spaces(section 2.1.4). MUST be zero
   */
  bool m_fHasOsidReferences;

  /**
   * @brief padding, MUST be zero, and MUST be ignored.
   *
   * 30 bits wide
   */
  quint32 m_fReserved2;

public:
  ObjectDeclarationWithRefCountBody();

  CompactID getOid() const;
  void setOid(const CompactID& value);

  quint8 getJci() const;
  void setJci(const quint8& value);

  quint8 getOdc() const;
  void setOdc(const quint8& value);

  bool getFHasOidReferences() const;
  void setFHasOidReferences(bool value);

  bool getFHasOsidReferences() const;
  void setFHasOsidReferences(bool value);

  static quint64 getSizeInFile();

private:
  static const quint64 sizeInFile;
  /**
   * @brief creates ObjectDeclarationWithRefCountBody from QDataStream
   * @param ds <QDataStream> containing the deserializable
   * ObjectDeclarationWithRefCountBody
   */
  virtual void deserialize(QDataStream& ds) override;
  /**
   * @brief creates byte stream from ObjectDeclarationWithRefCountBody object
   * @param ds <QDataStream> is the output stream to which the serialized
   * ObjectDeclarationWithRefCountBody is send
   */
  virtual void serialize(QDataStream& ds) const override;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTDECLARATIONWITHREFCOUNTBODY_H
