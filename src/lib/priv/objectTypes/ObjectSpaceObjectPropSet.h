#ifndef OBJECTSPACEOBJECTPROPSET_H
#define OBJECTSPACEOBJECTPROPSET_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDebug>

#include "ObjectSpaceObjectStreamOfContextIDs.h"
#include "ObjectSpaceObjectStreamOfOIDs.h"
#include "ObjectSpaceObjectStreamOfOSIDs.h"

#include "../IStreamable.h"
#include "../commonTypes/FileNodeChunkReference.h"
#include "../propertyTypes/PropertySet.h"

namespace libmson{
namespace priv{

/// \todo counting inside the streamheaders
class ObjectSpaceObjectPropSet : public IStreamable {
private:
  ObjectSpaceObjectStreamOfOIDs m_OIDs;
  ObjectSpaceObjectStreamOfOSIDs m_OSIDs;
  ObjectSpaceObjectStreamOfContextIDs m_ContextIDs;

  PropertySet m_body;

  quint64 m_paddingLength;

public:
  ObjectSpaceObjectPropSet();
  ObjectSpaceObjectPropSet(QDataStream &ds, const FileNodeChunkReference &ref);

  ObjectSpaceObjectStreamOfOIDs OIDs() const;
  void setOIDs(const ObjectSpaceObjectStreamOfOIDs &OIDs);

  ObjectSpaceObjectStreamOfOSIDs OSIDs() const;
  void setOSIDs(const ObjectSpaceObjectStreamOfOSIDs &OSIDs);

  ObjectSpaceObjectStreamOfContextIDs ContextIDs() const;
  void setContextIDs(const ObjectSpaceObjectStreamOfContextIDs &ContextIDs);

  PropertySet body() const;
  void setBody(const PropertySet &body);

  quint64 getSizeInFile() const;

private:
  /**
   * @brief creates ObjectSpaceObjectPropSet from QDataStream
   * @param ds <QDataStream> containing the deserializable
   * ObjectSpaceObjectPropSet
   *
   * Note, that only 4GB of an FileDataStoreObject can be parsed because an
   * limitation of QByteArray
   */
  virtual void deserialize(QDataStream &ds) override;
  /**
   * @brief creates byte stream from ObjectSpaceObjectPropSet object
   * @param ds <QDataStream> is the output stream to which the serialized
   * ObjectSpaceObjectPropSet is send
   */
  virtual void serialize(QDataStream &ds) const override;

};

} //namespace priv
} // namespace libmson

#endif // OBJECTSPACEOBJECTPROPSET_H
