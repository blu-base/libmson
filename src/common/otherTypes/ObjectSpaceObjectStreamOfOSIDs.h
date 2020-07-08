#ifndef OBJECTSPACEOBJECTSTREAMOFOSIDS_H
#define OBJECTSPACEOBJECTSTREAMOFOSIDS_H

#include <QtCore/qglobal.h>

#include "IObjectSpaceOpbjectStream.h"
#include "ObjectSpaceObjectStreamHeader.h"

class ObjectSpaceObjectStreamOfOSIDs : public IObjectSpaceOpbjectStream {
public:
  ObjectSpaceObjectStreamOfOSIDs();
  ObjectSpaceObjectStreamOfOSIDs(
      const ObjectSpaceObjectStreamHeader::OsidStreamPresence
          &osidStreamPresence,
      const ObjectSpaceObjectStreamHeader::ExtendedStreamPresence
          &extendedStreamPresence);
  ~ObjectSpaceObjectStreamOfOSIDs();
};

#endif // OBJECTSPACEOBJECTSTREAMOFOSIDS_H
