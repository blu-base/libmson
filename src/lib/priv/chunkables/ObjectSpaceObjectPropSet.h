#ifndef OBJECTSPACEOBJECTPROPSET_H
#define OBJECTSPACEOBJECTPROPSET_H

#include "Chunkable.h"
#include <QtCore/qglobal.h>

#include "objectTypes/ObjectSpaceObjectStreamOfContextIDs.h"
#include "objectTypes/ObjectSpaceObjectStreamOfOIDs.h"
#include "objectTypes/ObjectSpaceObjectStreamOfOSIDs.h"

#include "../propertyTypes/PropertySet.h"


namespace libmson {
namespace priv {

class ObjectSpaceObjectPropSet : public Chunkable {
private:
  ObjectSpaceObjectStreamOfOIDs m_OIDs;
  ObjectSpaceObjectStreamOfOSIDs m_OSIDs;
  ObjectSpaceObjectStreamOfContextIDs m_ContextIDs;

  PropertySet m_body;

  quint64 m_paddingLength;

public:
  ObjectSpaceObjectPropSet();

  ObjectSpaceObjectStreamOfOIDs getOIDs() const;
  ObjectSpaceObjectStreamOfOIDs& OIDs();
  void setOIDs(const ObjectSpaceObjectStreamOfOIDs& OIDs);

  ObjectSpaceObjectStreamOfOSIDs getOSIDs() const;
  ObjectSpaceObjectStreamOfOSIDs& OSIDs();
  void setOSIDs(const ObjectSpaceObjectStreamOfOSIDs& OSIDs);

  ObjectSpaceObjectStreamOfContextIDs getContextIDs() const;
  ObjectSpaceObjectStreamOfContextIDs& contextIDs();
  void setContextIDs(const ObjectSpaceObjectStreamOfContextIDs& ContextIDs);

  PropertySet getBody() const;
  void setBody(const PropertySet& body);

  quint64 getPaddingLength() const;

  // Chunkable interface
  virtual quint64 cb() const override;
  virtual RevisionStoreChunkType getType() const override;

  friend class RevisionStoreFileWriter;
  friend class RevisionStoreFileParser;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTSPACEOBJECTPROPSET_H
