#ifndef IFILENODETYPE_H
#define IFILENODETYPE_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDebug>
#include <QXmlStreamWriter>

namespace MSONcommon {
/**
 * @class IFileNodeType
 * @brief The abstract class for the Data contained in FileNodes
 *
 */
class IFileNodeType {
protected:
  IFileNodeType();

public:
  //  virtual ~IFileNodeType() = 0;

  friend QDataStream &operator<<(QDataStream &ds, const IFileNodeType &obj);
  ;
  friend QDataStream &operator>>(QDataStream &ds, IFileNodeType &obj);
  ;

  friend QDebug operator<<(QDebug dbg, const IFileNodeType &obj);
  ;

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const = 0;

private:
  /**
   * @brief creates IFileNodeType from QDataStream
   * @param ds <QDataStream> containing the deserializable IFileNodeType
   */
  virtual void deserialize(QDataStream &ds) = 0;
  /**
   * @brief creates byte stream from IFileNodeType object
   * @param ds <QDataStream> is the output stream to which the serialized
   * IFileNodeType is send
   */
  virtual void serialize(QDataStream &ds) const = 0;

  /**
   * @brief prints the IFileNodeType to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  virtual void toDebugString(QDebug dbg) const = 0;
};

} // namespace MSONcommon

#endif // IFILENODETYPE_H
