#ifndef OBJECTSPACEOBJECTPROPSET_H
#define OBJECTSPACEOBJECTPROPSET_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDebug>

#include "ObjectSpaceObjectStreamOfOIDs.h"
#include "ObjectSpaceObjectStreamOfOSIDs.h"
#include "ObjectSpaceObjectStreamOfContextIDs.h"

#include "../properties/PropertySet.h"



/// \todo counting inside the streamheaders
class ObjectSpaceObjectPropSet
{
private:
    ObjectSpaceObjectStreamOfOIDs m_OIDs;
    ObjectSpaceObjectStreamOfOSIDs m_OSIDs;
    ObjectSpaceObjectStreamOfContextIDs m_ContextIDs;

    PropertySet m_body;

    quint64 m_paddingLength;

public:
  ObjectSpaceObjectPropSet();


  friend QDataStream &operator<<(QDataStream &ds,
                                 const ObjectSpaceObjectPropSet &obj);
  friend QDataStream &operator>>(QDataStream &ds, ObjectSpaceObjectPropSet &obj);

  friend QDebug operator<<(QDebug dbg, const ObjectSpaceObjectPropSet &obj);



  ObjectSpaceObjectStreamOfOIDs OIDs() const;
  void setOIDs(const ObjectSpaceObjectStreamOfOIDs& OIDs);

  ObjectSpaceObjectStreamOfOSIDs OSIDs() const;
  void setOSIDs(const ObjectSpaceObjectStreamOfOSIDs& OSIDs);

  ObjectSpaceObjectStreamOfContextIDs ContextIDs() const;
  void setContextIDs(const ObjectSpaceObjectStreamOfContextIDs& ContextIDs);

  PropertySet body() const;
  void setBody(const PropertySet& body);

private:
  /**
   * @brief creates ObjectSpaceObjectPropSet from QDataStream
   * @param ds <QDataStream> containing the deserializable ObjectSpaceObjectPropSet
   *
   * Note, that only 4GB of an FileDataStoreObject can be parsed because an
   * limitation of QByteArray
   */
  void deserialize(QDataStream &ds);
  /**
   * @brief creates byte stream from ObjectSpaceObjectPropSet object
   * @param ds <QDataStream> is the output stream to which the serialized
   * ObjectSpaceObjectPropSet is send
   *

   */
  void serialize(QDataStream &ds) const;

  /**
   * @brief prints the ObjectSpaceObjectPropSet to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  void toDebugString(QDebug dbg) const;

};

#endif // OBJECTSPACEOBJECTPROPSET_H
