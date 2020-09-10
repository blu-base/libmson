#include "ObjectSpaceObjectStreamOfContextIDs.h"

#include "ObjectSpaceObjectStreamHeader.h"

namespace MSONcommon {

ObjectSpaceObjectStreamOfContextIDs::ObjectSpaceObjectStreamOfContextIDs()
    : IObjectSpaceOpbjectStream() {}

ObjectSpaceObjectStreamOfContextIDs::ObjectSpaceObjectStreamOfContextIDs(
    const ObjectSpaceObjectStreamHeader::OsidStreamPresence &osidStreamPresence,
    const ObjectSpaceObjectStreamHeader::ExtendedStreamPresence
        &extendedStreamPresence)
    : IObjectSpaceOpbjectStream(osidStreamPresence, extendedStreamPresence) {}

ObjectSpaceObjectStreamOfContextIDs::~ObjectSpaceObjectStreamOfContextIDs() {}

} // namespace MSONcommon
