#ifndef OBJECTSPACEOBJECTSTREAMOFOSIDS_H
#define OBJECTSPACEOBJECTSTREAMOFOSIDS_H

#include <QtCore/qglobal.h>

#include "IObjectSpaceOpbjectStream.h"
#include "ObjectSpaceObjectStreamHeader.h"

namespace MSONcommon {

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

} // namespace MSONcommon

#endif // OBJECTSPACEOBJECTSTREAMOFOSIDS_H
