#ifndef OBJECTSPACEOBJECTSTREAMOFCONTEXTIDS_H
#define OBJECTSPACEOBJECTSTREAMOFCONTEXTIDS_H
#include <QtCore/qglobal.h>

#include "IObjectSpaceObjectStream.h"
#include "ObjectSpaceObjectStreamHeader.h"

namespace libmson{
namespace priv{

class ObjectSpaceObjectStreamOfContextIDs : public IObjectSpaceObjectStream {
public:
  ObjectSpaceObjectStreamOfContextIDs();
  ObjectSpaceObjectStreamOfContextIDs(
      const ObjectSpaceObjectStreamHeader::OsidStreamPresence
          &osidStreamPresence,
      const ObjectSpaceObjectStreamHeader::ExtendedStreamPresence
          &extendedStreamPresence);
  ~ObjectSpaceObjectStreamOfContextIDs();
};

} //namespace priv
} // namespace libmson

#endif // OBJECTSPACEOBJECTSTREAMOFCONTEXTIDS_H
