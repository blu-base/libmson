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

public:
  ObjectSpaceObjectPropSet(
      const quint64 initialStp = 0, const quint64 initialCb = 0);

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


  friend class RevisionStoreFileWriter;
  friend class RevisionStoreFileParser;

private:
  quint64 unPaddedCb() const;

  // Chunkable interface
  virtual quint64 cb() const override;
  virtual RevisionStoreChunkType getType() const override;
};

typedef std::shared_ptr<ObjectSpaceObjectPropSet>
    ObjectSpaceObjectPropSet_SPtr_t;
typedef std::weak_ptr<ObjectSpaceObjectPropSet> ObjectSpaceObjectPropSet_WPtr_t;

} // namespace priv
} // namespace libmson

#endif // OBJECTSPACEOBJECTPROPSET_H
