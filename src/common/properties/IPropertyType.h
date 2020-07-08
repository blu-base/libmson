#ifndef IPROPERTYTYPE_H
#define IPROPERTYTYPE_H

#include <QtCore/qglobal.h>

class IPropertyType {
public:
  IPropertyType();

public:
  friend QDataStream &operator<<(QDataStream &ds, const IPropertyType &obj);
  friend QDataStream &operator>>(QDataStream &ds, IPropertyType &obj);

  friend QDebug operator<<(QDebug dbg, const IPropertyType &obj);

private:
  /**
   * @brief creates IPropertyType from QDataStream
   * @param ds <QDataStream> containing the deserializable IPropertyType
   */
  virtual void deserialize(QDataStream &ds) = 0;
  /**
   * @brief creates byte stream from IPropertyType object
   * @param ds <QDataStream> is the output stream to which the serialized
   * IPropertyType is send
   */
  virtual void serialize(QDataStream &ds) const = 0;

  /**
   * @brief prints the IPropertyType to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  virtual void toDebugString(QDebug dbg) const = 0;
};

#endif // IPROPERTYTYPE_H
