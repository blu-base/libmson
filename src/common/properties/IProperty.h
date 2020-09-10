#ifndef IPROPERTY_H
#define IPROPERTY_H

#include <QtCore/qglobal.h>

#include <QXmlStreamWriter>

namespace MSONcommon {

class IProperty {
protected:
  IProperty();

public:
  friend QDataStream &operator<<(QDataStream &ds, const IProperty &obj);
  friend QDataStream &operator>>(QDataStream &ds, IProperty &obj);

  friend QDebug operator<<(QDebug dbg, const IProperty &obj);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const = 0;

private:
  /**
   * @brief creates IProperty from QDataStream
   * @param ds <QDataStream> containing the deserializable IProperty
   */
  virtual void deserialize(QDataStream &ds) = 0;
  /**
   * @brief creates byte stream from IProperty object
   * @param ds <QDataStream> is the output stream to which the serialized
   * IProperty is send
   */
  virtual void serialize(QDataStream &ds) const = 0;

  /**
   * @brief prints the IProperty to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  virtual void toDebugString(QDebug dbg) const = 0;
};

} // namespace MSONcommon

#endif // IPROPERTY_H
