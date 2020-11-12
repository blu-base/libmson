#ifndef OBJECTSPACEOBJECTSTREAMOFOSIDS_H
#define OBJECTSPACEOBJECTSTREAMOFOSIDS_H

#include <QtCore/qglobal.h>

#include "IObjectSpaceObjectStream.h"
#include "ObjectSpaceObjectStreamHeader.h"

namespace libmson{
namespace priv{

class ObjectSpaceObjectStreamOfOSIDs : public IObjectSpaceObjectStream {
public:
  ObjectSpaceObjectStreamOfOSIDs();
  ObjectSpaceObjectStreamOfOSIDs(
      const ObjectSpaceObjectStreamHeader::OsidStreamPresence
          &osidStreamPresence,
      const ObjectSpaceObjectStreamHeader::ExtendedStreamPresence
          &extendedStreamPresence);
  ~ObjectSpaceObjectStreamOfOSIDs();
};

} //namespace priv
} // namespace libmson

#endif // OBJECTSPACEOBJECTSTREAMOFOSIDS_H
