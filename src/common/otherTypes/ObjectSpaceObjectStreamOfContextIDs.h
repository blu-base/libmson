#ifndef OBJECTSPACEOBJECTSTREAMOFCONTEXTIDS_H
#define OBJECTSPACEOBJECTSTREAMOFCONTEXTIDS_H
#include <QtCore/qglobal.h>

#include "IObjectSpaceOpbjectStream.h"
#include "ObjectSpaceObjectStreamHeader.h"

class ObjectSpaceObjectStreamOfContextIDs : public IObjectSpaceOpbjectStream {
public:
  ObjectSpaceObjectStreamOfContextIDs();
  ObjectSpaceObjectStreamOfContextIDs(
      const ObjectSpaceObjectStreamHeader::OsidStreamPresence
          &osidStreamPresence,
      const ObjectSpaceObjectStreamHeader::ExtendedStreamPresence
          &extendedStreamPresence);
  ~ObjectSpaceObjectStreamOfContextIDs();
};

#endif // OBJECTSPACEOBJECTSTREAMOFCONTEXTIDS_H
