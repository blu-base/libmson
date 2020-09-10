#ifndef OBJECTSPACEOBJECTSTREAMOFCONTEXTIDS_H
#define OBJECTSPACEOBJECTSTREAMOFCONTEXTIDS_H
#include <QtCore/qglobal.h>

#include "IObjectSpaceOpbjectStream.h"
#include "ObjectSpaceObjectStreamHeader.h"

namespace MSONcommon {

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

} // namespace MSONcommon

#endif // OBJECTSPACEOBJECTSTREAMOFCONTEXTIDS_H
