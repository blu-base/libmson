#ifndef OBJECTSPACEOBJECTSTREAMOFOIDS_H
#define OBJECTSPACEOBJECTSTREAMOFOIDS_H

#include <QtCore/qglobal.h>

#include "IObjectSpaceObjectStream.h"
#include "ObjectSpaceObjectStreamHeader.h"

namespace MSONcommon {

class ObjectSpaceObjectStreamOfOIDs : public IObjectSpaceObjectStream {
public:
  ObjectSpaceObjectStreamOfOIDs();
  ObjectSpaceObjectStreamOfOIDs(
      const ObjectSpaceObjectStreamHeader::OsidStreamPresence
          &osidStreamPresence,
      const ObjectSpaceObjectStreamHeader::ExtendedStreamPresence
          &extendedStreamPresence);
  ~ObjectSpaceObjectStreamOfOIDs();
};

} // namespace MSONcommon

#endif // OBJECTSPACEOBJECTSTREAMOFOIDS_H
