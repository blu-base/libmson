#ifndef OBJECTSPACEOBJECTSTREAMOFOIDS_H
#define OBJECTSPACEOBJECTSTREAMOFOIDS_H

#include <QtCore/qglobal.h>

#include "IObjectSpaceOpbjectStream.h"
#include "ObjectSpaceObjectStreamHeader.h"

class ObjectSpaceObjectStreamOfOIDs : public IObjectSpaceOpbjectStream {
public:
  ObjectSpaceObjectStreamOfOIDs();
  ObjectSpaceObjectStreamOfOIDs(
      const ObjectSpaceObjectStreamHeader::OsidStreamPresence
          &osidStreamPresence,
      const ObjectSpaceObjectStreamHeader::ExtendedStreamPresence
          &extendedStreamPresence);
  ~ObjectSpaceObjectStreamOfOIDs();
};

#endif // OBJECTSPACEOBJECTSTREAMOFOIDS_H
